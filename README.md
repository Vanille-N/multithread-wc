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

### `dispatch.c`

```c
#define NB_THREADS 5

typedef struct {
    const char* file;
    int start;
    int end;
    int count;
} zone_t;

int dispatch (const char* file, void* counter (void*));
```

`NB_THREADS` may safely be set to any reasonable strictly positive value to adjust to the number of cores available.

A `zone_t` describes the work each thread has to do : `file` is the name of the file they have to open, `start` and `end` delimit the area of the file they have to consider, `count` serves as a return value.

Threads have no obligation to check that the file exists or to ensure their zone is valid (`0 <= start <= end <= size(file)`), it is `dispatch`'s role to ensure they are.
