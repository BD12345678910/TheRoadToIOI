#!/bin/sh

for f in test.*.in; do
    ./flower < "$f" > tmp.out
    diff -w tmp.out "${f%.in}.out" >/dev/null &&
        echo "$f: AC" || echo "$f: WA"
done

rm -f tmp.out