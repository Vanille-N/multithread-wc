#!/bin/bash

f='benches/rnd.plain'

hyperfine --warmup 5 "wc -w $f" "./target -w $f" "./mwc -w $f"
# hyperfine "wc -l $f" "./target -l $f" "./mwc -l $f"
# hyperfine "wc -c $f" "./target -c $f" "./mwc -c $f"
