#!/usr/bin/sh

notebook-generator/notebook-generator ./codes \
    --title "\\bf{Muffix Sassif -- TRD}" \
    --author "Andrianov, Lepeshov, Shulyatev" \
    --initials "Nizhny Novgorod Branch of HSE University (Andrianov, Lepeshov, Shulyatev)" \
    --output ./teambook.pdf \
    --image ./notebook-generator/picture.jpg \
    --assets `pwd`/assets \
    --columns 3 \
    --size 9

