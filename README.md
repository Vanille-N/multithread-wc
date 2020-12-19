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
