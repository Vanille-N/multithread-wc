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
  ├── dispatch.c          thread management, calls count
  ├── count.c             counters
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

More precisely, `dispatch` :
- determines the length of the file
- divides it evenly between the wanted number of threads
- sets up each `zone_t`
- launches one instance of the counter given as second argument per zone
- waits for thread termination
- sums up all results

### `lib.c`

```c
#define BUFSIZE (16 * 1024)

int count_bytes (const char* file);

void* count_lines (void* data);

void* count_words (void* data);
```
Lowering `BUFSIZE` too much may decrease performance because of too many system calls and bounds checks.
Conversely, raising it may increase memory consumption.

`count_bytes` opens the file and returns its length (uses `lseek`, very fast).

```
fun count_bytes(file)
    open f as fd
    go to end of fd
    return position of cursor in fd
```

`count_lines` interpretes its argument as a `zone_t*` and counts the number of `'\n'` in the zone it was assigned.

```
fun count_lines(file, start, end)
    open file as fd
    jump to start in fd
    n <- 0
    for char c until end in fd
        if c == '\n'
            incr n
    return n
```

`count_words` splits on `' '`, `'\t'`, `'\n'`. It may read a single char outside of its zone to check if the last letters of its zone constitute a word.

## Utils

### `test.sh`
### `bench.sh`
### `testmake.sh`
