# Multithreaded Word Count
Neven Villani, ENS Paris-Saclay

```
$ mwc [-w|-l|-c] FILE
```

Count (w)ords, (l)ines or (c)hars in FILE.

![](benchmarks.png)

## Structure

```
──┐
  ├── main.c              argument parsing, calls dispatch
  ├── dispatch.c          thread management, calls lib
  ├── lib.c               counters
  ├── *.h
  ├── Makefile
  ├── tests               correction
  │     ├── test.sh         check ./mwc against ./mwc-handout
  │     └── *.plain         tricky tests
  └── benches             performance
        ├── bench.sh        measure with hyperfine
        ├── testmake.sh     
        └── *.plain         massive tests (not included)
````

## Contents

### `main.c`

Error codes:
```c
#define WR_OPT 1
#define WR_ARG 2
#define WR_FILE 3
```

Argument rules:
- at most one of `-w`, `-c`, `-l` (otherwise `WR_OPT`)
- if no option is provided then `-w` is assumed
- no other argument may start with `'-'` (otherwise `WR_OPT`)
- exactly one file name (otherwise `WR_ARG`)
- file must exist and have read permissions (otherwise `WR_FILE`)
- arguments may be in any order
