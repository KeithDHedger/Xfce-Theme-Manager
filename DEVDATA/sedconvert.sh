#!/bin/sed -rf

#replace double nl with single break
:a;N;$!ba;s/\n\n/\n.br\n/g

s/\[TITLE\]/\.TH/
s/\[SECTION\]/\.SH/g
s/\[BOLD\]/\.B/g

