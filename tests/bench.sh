#!/bin/bash

rm garbage.plain
for i in {0..100}; do
    < /dev/urandom tr -dc '\n\t [:alnum:]' | head -c1000000 >> garbage.plain
done
ls -l garbage.plain

hyperfine 'bash -c "wc -l garbage.plain"'
hyperfine 'bash -c "./target -l garbage.plain"'
hyperfine 'bash -c "./mwc -l garbage.plain"'

hyperfine 'bash -c "wc -c garbage.plain"'
hyperfine 'bash -c "./target -c garbage.plain"'
hyperfine 'bash -c "./mwc -c garbage.plain"'

hyperfine 'bash -c "wc -w garbage.plain"'
hyperfine 'bash -c "./target -w garbage.plain"'
hyperfine 'bash -c "./mwc -w garbage.plain"'
