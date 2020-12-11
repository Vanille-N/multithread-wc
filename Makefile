.PHONY: bin
bin: mwc

%.c: %.h

mwc: main.c
	gcc -O3 -o $@ -pthread $^

.PHONY: tests
tests: mwc
	BIN=./$< tests/test.sh
