.PHONY: bin tests clean

bin: mwc

%.c: %.h

mwc: main.c lib.c main.h lib.h
	gcc -O3 -o $@ -pthread $^ -Wall -Werror -Wpedantic

tests: mwc
	BIN=./$< tests/test.sh

clean:
	rm mwc

bench: mwc
	BIN=./$< benches/bench.py
