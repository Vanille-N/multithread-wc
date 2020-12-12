#!/bin/bash

input='benches/rnd.1G.plain'
# execs=( 'wc' './mwc-handout' './mwc-10k5' ) # measure handout vs v1.0
# execs=( 'wc' './mwc-10k5' './mwc-10k5-dispatch' ) # measure pre- vs post-dispatch
# execs=( 'wc' './mwc-10k5' './mwc-10k5-dispatch' './mwc-30k5-dispatch' ) # measure effect of BUFSIZE
execs=( 'wc' './mwc-30k3-dispatch' './mwc-30k4-dispatch' './mwc-30k5-dispatch' './mwc-30k6-dispatch' ) # measure effect of NB_THREADS

hyperfine --warmup 2 "${execs[@]/%/ -w ${input}}"
# hyperfine "wc -l $f" "./target -l $f" "./mwc -l $f"
# hyperfine "wc -c $f" "./target -c $f" "./mwc -c $f"
