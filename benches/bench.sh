#!/bin/bash

input='benches/rnd.1G.plain'
# execs=( 'wc' './mwc-handout' './mwc-5-1000' )
execs=( 'wc' './mwc-5-1000' './mwc-dispatch' )

hyperfine --warmup 2 "${execs[@]/%/ -w ${input}}"
# hyperfine "wc -l $f" "./target -l $f" "./mwc -l $f"
# hyperfine "wc -c $f" "./target -c $f" "./mwc -c $f"
