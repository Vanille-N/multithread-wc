#!/bin/bash

cd benches # This may fail.
# We don't care, we just want to be in benches/.
# -> Assume that failure means we already are.

for size in 1k 10k 100k 1M 10M 100M 1G; do
    echo "Generating file of size $size..."
    < /dev/urandom tr -dc '\n\t [:alnum:]' | head -c$size > rnd.$size.plain
done
