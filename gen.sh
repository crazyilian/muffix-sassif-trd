#!/usr/bin/sh

notebook-generator/notebook-generator ./codes \
    --title "\\bf{Muffix Sassif -- TRD}" \
    --author "Andrianov, Lepeshov, Shulyatev" \
    --initials "NRU HSE (Andrianov, Lepeshov, Shulyatev)" \
    --output ./teambook.pdf \
    --image ./notebook-generator/picture.jpg \
    --assets `pwd`/assets

