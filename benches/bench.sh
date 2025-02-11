#!/bin/bash

size="100M"
input="benches/rnd.$size.plain"

# execs=( './mwc-handout' './mwc') # measure handout vs v1.0
execs=( './mwc-handout' './mwc-mcc' ) # measure handout vs home-compiled
# execs=( 'wc' './mwc-10k5' './mwc-10k5-dispatch' ) # measure pre- vs post-dispatch
# execs=( 'wc' './mwc-10k5' './mwc-10k5-dispatch' './mwc-30k5-dispatch' ) # measure effect of BUFSIZE
# execs=( './mwc-60k1' './mwc-60k2' './mwc-60k3' './mwc-60k4' './mwc-60k5' './mwc-60k6' './mwc-60k7' './mwc-60k8' ) # measure effect of NB_THREADS
# execs=( 'wc' './mwc-30k5-dispatch' './mwc-30k5-inc' ) # measure effect of fewer deref increments
#execs=( 'wc' './mwc-read-then-check' './mwc' ) # measure effect of less overlap
#execs=( './mwc-30k5' './mwc-60k5' ) # adjust buffer size

for arg in w l c; do
    echo "#### MEASURE $arg ####"
    hyperfine --warmup 2 "${execs[@]/%/ -$arg $input}"
    echo "######################"
    echo ""
done
