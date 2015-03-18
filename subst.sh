#/bin/bash

while read line; do
    echo "$line"
    tr 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' \
       'v.ebiwafdcsymlnuj.o.t.gprh' <<< "$line"
done
