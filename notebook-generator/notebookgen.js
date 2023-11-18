const fs = require('fs')
const path = require('path')
const spawn = require('child_process').spawn
const through2 = require('through2')
const tmp = require('tmp')
const os = require('os')

const section = ['\\section{', '\\subsection{', '\\subsubsection{']
const extensions = {
  '.cc': 'C++',
  '.cpp': 'C++',
  '.hpp': 'C++',
  '.c': 'C',
  '.java': 'Java',
  '.py': 'Python',
  '.tex': 'Tex',
  '.go': 'Golang'
}

function walk (_path, depth) {
  let ans = ''
  depth = Math.min(depth, section.length - 1)
  fs.readdirSync(_path).forEach(function (file) {
    if (file.startsWith('.')) {
      return // hidden directory
    }
    const f = path.resolve(_path, file)
    const stat = fs.lstatSync(f)
    file = file.replaceAll('_', '\\_')
    if (stat.isDirectory()) {
      ans += '\n' + section[depth] + file + '}\n' + walk(f, depth + 1)
    } else if (path.extname(f) in extensions) {
      ans += '\n' + section[depth] + file.split('.')[0] + '}\n'
      if (path.extname(f) !== '.tex') {
        ans += `\\begin{lstlisting}[language=${extensions[path.extname(f)]}]\n` + fs.readFileSync(f, 'utf8') + '\\end{lstlisting}\n'
      } else {
        ans += fs.readFileSync(f)
      }
    }
  })
  return ans
}

/**
 * pdf must be generated twice in order to generate the table of contents.
 * According to some tests, in windows it must be generated 3 times.
 * */
function genpdf (ans, texPath, tmpobj, iter) {
  const tex = spawn('pdflatex', [
    '-interaction=nonstopmode',
    texPath
  ], {
    cwd: tmpobj.name,
    env: process.env
  })

  tex.on('error', function (err) {
    console.error(err)
  })

  tex.on('exit', function (code, signal) {
    const outputFile = texPath.split('.')[0] + '.pdf'
    fs.access(outputFile, function (err) {
      if (err) {
        return console.error('Not generated ' + code + ' : ' + signal)
      }
      if (iter === 0) {
        const s = fs.createReadStream(outputFile)
        s.pipe(ans)
        s.on('close', function () {
          tmpobj.removeCallback()
        })
      } else {
        genpdf(ans, texPath, tmpobj, iter - 1)
      }
    })
  })
}

function pdflatex (doc, tex_output) {
  const tmpobj = tmp.dirSync({ unsafeCleanup: true })
  const texPath = path.join(tmpobj.name, '_notebook.tex')

  const ans = through2()
  ans.readable = true
  const input = fs.createWriteStream(texPath)
  
  input.end(doc)
  
  input.on('close', function () {
    fs.copyFile(texPath, tex_output, ()=>{});
    const iters = process.platform === 'win32' ? 2 : 1
    genpdf(ans, texPath, tmpobj, iters)
  })

  return ans
}

function normalizeUnixStyle (currentPath) {
  if (os.type() === 'Windows_NT') {
    return currentPath.replace(/\\/g, '/')
  }
  return currentPath
}

function templateParameter (parameter) {
  return `\${${parameter}}`
}

module.exports = function (_path, options) {
  options.output = options.output || './notebook.pdf'
  options.author = options.author || ''
  options.initials = options.initials || ''
  options.title = options.title || ''

  if (!options.size.endsWith('pt')) options.size += 'pt'
  if (options.image) {
    options.image = normalizeUnixStyle(path.resolve(options.image))
    options.image = '\\begin{center}{\\includegraphics[width=5cm]{' + options.image + '}\\end{center}'
  } else {
    options.image = ''
  }

  let template = fs.readFileSync(path.join(__dirname, 'template_header.tex')).toString()
  template = template
    .replaceAll(templateParameter('author'), options.author)
    .replaceAll(templateParameter('initials'), options.initials)
    .replaceAll(templateParameter('fontSize'), options.size)
    .replaceAll(templateParameter('columns'), options.columns)
    .replaceAll(templateParameter('paper'), options.paper)
    .replaceAll(templateParameter('image'), options.image)
    .replaceAll(templateParameter('title'), options.title)
    .replaceAll(templateParameter('codes'), walk(_path, 0))
  
  let pos = options.output.lastIndexOf(".");
  tex_output = options.output.substr(0, pos < 0 ? options.output.length : pos) + ".tex";
  
  pdflatex(template, tex_output).pipe(fs.createWriteStream(options.output))
}
