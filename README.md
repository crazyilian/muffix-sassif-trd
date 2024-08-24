# Muffix Sassif - Team Reference Document

## Code rules
* _**Do not use dollars**_. Consider using `'#'` or use `$\dollar$` instead of `$`.
* You can use Latex inside code (comments). `$a_1, ..., a_n$` will be displayed as $a_1, ..., a_n$.
* To include image in `.tex` files add it to `/assets` and use this code:
```tex
\begin{center}
    \includegraphics[width=5cm]{${assets}/image.png} \\
    \caption{Aboba}
\end{center}
```

## Generate pdf
To generate new `.pdf` and `.tex` files run
```sh
sh gen.sh
```
