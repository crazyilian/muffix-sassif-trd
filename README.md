# Muffix Sassif - Team Reference Document

## Code rules
* _**Do not use dollars**_. Consider using `'#'` or use `$\dollar$` instead of `$`.
* You can use Latex inside code (comments). `$a_1, ..., a_n$` will be displayed as $a_1, ..., a_n$.
* To include image in `.tex` files add it to `/assets/*` and use this code:
```tex
\begin{center}
    \includegraphics[width=5cm]{${assets}/image.png} \\
    Caption here
\end{center}
```

## Generate pdf
To generate new `.pdf` and `.tex` files run
```sh
sh gen.sh
```

### Troubleshooting
* If you're on Arch, you'll probably want to install the following packages:
```sh
sudo pacman -Sy texlive-bin texlive-basic texlive-langcyrillic texlive-fontsrecommended texlive-latex texlive-latexrecommended texlive-latexextra
```
* I'm not sure how to properly install required npm packages, I press random buttons each time and sometimes it works.
