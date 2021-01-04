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

SRC=$(CFILES) $(HFILES)
AUX_BENCH=bench.sh benchmake.sh
DIR_BENCH=benches
AUX_TESTS=test.sh testmake.sh
DIR_TESTS=tests
DATA=alphabet chrs data empty long newline noline onew twow twowbigs
TESTS=$(addsuffix .plain, $(DATA))
DIR=Villani_Neven

tar:
	mkdir $(DIR) || rm -rf $(DIR)/*
	cp $(SRC) $(DIR)/
	cp Makefile $(DIR)/
	cp README.md $(DIR)/
	cp mwc-handout $(DIR)/
	mkdir $(DIR)/$(DIR_BENCH)
	mkdir $(DIR)/$(DIR_TESTS)
	cp $(addprefix $(DIR_TESTS)/, $(TESTS)) \
		$(DIR)/$(DIR_TESTS)/
	cp $(addprefix $(DIR_BENCH)/, $(AUX_BENCH)) \
		$(DIR)/$(DIR_BENCH)/
	cp $(addprefix $(DIR_TESTS)/, $(AUX_TESTS)) \
		$(DIR)/$(DIR_TESTS)/
	tar czf $(DIR).tar.gz $(DIR)
