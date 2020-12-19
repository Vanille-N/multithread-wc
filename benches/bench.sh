#!/bin/bash

input='benches/rnd.1G.plain'
# execs=( 'wc' './mwc-handout' './mwc' ) # measure handout vs v1.0
# execs=( 'wc' './mwc-10k5' './mwc-10k5-dispatch' ) # measure pre- vs post-dispatch
# execs=( 'wc' './mwc-10k5' './mwc-10k5-dispatch' './mwc-30k5-dispatch' ) # measure effect of BUFSIZE
# execs=( 'wc' './mwc-30k3-dispatch' './mwc-30k4-dispatch' './mwc-30k5-dispatch' './mwc-30k6-dispatch' ) # measure effect of NB_THREADS
# execs=( 'wc' './mwc-30k5-dispatch' './mwc-30k5-inc' ) # measure effect of fewer deref increments
execs=( 'wc' './mwc-read-then-check' './mwc' ) # measure effect of less overlap

hyperfine --warmup 2 "${execs[@]/%/ -w ${input}}"
# hyperfine --warmup 2 "${execs[@]/%/ -l ${input}}"
# hyperfine --warmup 2 "${execs[@]/%/ -c ${input}}"
