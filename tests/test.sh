#!/usr/bin/env bash

for f in tests/*.plain
do
    if [[ "$(wc -w "$f")" != "$($BIN "$f")" ]]
    then
        echo "[ERROR] ${f}: Word count mismatch"
        exit 1
    fi
    if [[ "$(wc -l "$f")" != "$($BIN -l "$f")" ]]
    then
        echo "[ERROR] ${f}: Line count mismatch"
        exit 1
    fi
    if [[ "$(wc -c "$f")" != "$($BIN -c "$f")" ]]
    then
        echo "[ERROR] ${f}: Character count mismatch"
        exit 1
    fi
done
