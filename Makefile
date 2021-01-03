.PHONY: bin tests clean

bin: mwc

%.c: %.h

NAMES=main count dispatch
CFILES=$(addsuffix .c, $(NAMES))
HFILES=$(addsuffix .h, $(NAMES))


mwc: $(CFILES) $(HFILES)
	gcc -O3 -o mwc -pthread $(CFILES) -Wall -Werror -Wpedantic

tests: mwc
	BIN=./mwc WITNESS=./mwc-handout tests/test.sh

bench:
	./benches/bench.sh
