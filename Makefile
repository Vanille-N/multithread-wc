.PHONY: bin tests clean

bin: mwc

NAMES=main count dispatch
CFILES=$(addsuffix .c, $(NAMES))
HFILES=$(addsuffix .h, $(NAMES) check)

%.c: %.h check.h

mwc: $(CFILES) $(HFILES)
	gcc -O3 -o mwc -pthread $(CFILES) -Wall -Werror -Wpedantic

tests: mwc
	cd tests; \
		BIN=../mwc WITNESS=../mwc-handout ./test.sh

bench:
	./benches/bench.sh
