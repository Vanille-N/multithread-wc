#!/usr/bin/env bash

verify() {
    f="$1"
    wit="$($WITNESS -w "$f")"
    bin="$($BIN -w "$f")"
    if [[ "$wit" != "$bin" ]]; then
        echo -e "\t\x1b[31m[KO]\x1b[0m ${f}: Word count mismatch"
        echo -e "\t\tWitness: <<$wit>>"
        echo -e "\t\tBin: <<$bin>>"
        exit 1
    fi
    wit="$($WITNESS -l "$f")"
    bin="$($BIN -l "$f")"
    if [[ "$wit" != "$bin" ]]; then
        echo -e "\t\x1b[31m[KO]\x1b[0m ${f}: Line count mismatch"
        echo -e "\t\tWitness: <<$wit>>"
        echo -e "\t\tBin: <<$bin>>"
        exit 1
    fi
    wit="$($WITNESS -c "$f")"
    bin="$($BIN -c "$f")"
    if [[ "$wit" != "$bin" ]]; then
        echo -e "\t\x1b[31m[KO]\x1b[0m ${f}: Character count mismatch"
        echo -e "\t\tWitness: <<$wit>>"
        echo -e "\t\tBin: <<$bin>>"
        exit 1
    fi
    echo -e "\t\x1b[32m[OK]\x1b[0m Passed test $f"
}

echo "Fixed tests"
for f in tests/*.plain; do
    verify "$f"
done
echo -e "All fixed tests passed\n"

echo "Random tests"
for size in {0..100000..5000}; do
    f="tests/rnd.$size.plain"
    < /dev/urandom tr -dc '\n\t [:alnum:]' | head -c$size > "$f"
    verify "$f"
    rm "$f"
done
echo -e "All random tests passed\n"
