#!/usr/bin/python

from subprocess import run
import time as t
import matplotlib.pyplot as plt
import sys
import random as rnd

def all_identical(data):
    if data == []:
        return True
    for d in data:
        if d != data[0]:
            return False
    return True

def measure_instance(cmds, *args):
    measures = []
    outs = []
    for cmd in cmds:
        t_start = t.time()
        res = run([cmd, *args], capture_output=True)
        t_end = t.time()
        measures.append(t_end - t_start)
        outs.append(res.stdout)
    if all_identical(outs):
        return measures
    else:
        print("Not all tools agree on the output")
        for cmd, out in zip(cmds, outs):
            print("    {} [{}]".format(cmd, out))
        sys.exit(1)

allowed_ords = [ord('\n'), ord('\t'), ord(' '), *range(ord('a'), ord('z') + 1), *range(ord('A'), ord('Z') + 1)]

def random_sample(size):
    print("Measuring for size {}".format(size))
    n = len(allowed_ords) - 1
    data = [rnd.randint(0, n) for i in range(size)]
    data = [chr(allowed_ords[i]) for i in data]
    data = "".join(data)
    return data

def build_test(size):
    fname = "benches/rnd.plain"
    with open(fname, 'w') as f:
        f.write(random_sample(size))
    return fname

def measure_size(cmds, size, nb_samples, nb_reps, option):
    data = [[] for i in range(len(cmds))]
    for s in range(nb_samples):
        file = build_test(size)
        for r in range(nb_reps):
            times = measure_instance(cmds, file, option)
            for i in range(len(cmds)):
                data[i].append((size, times[i]))
    return data

def measure(cmds, sizes, nb_samples, nb_reps, option):
    data = [[] for i in range(len(cmds))]
    for size in sizes:
        times = measure_size(cmds, size, nb_samples, nb_reps, option)
        for i in range(len(cmds)):
            data[i].extend(times[i])
    return data

def unzip(x):
    a = []
    b = []
    for (ai, bi) in x:
        a.append(ai)
        b.append(bi)
    return (a, b)

def main():
    cmds = ["wc", "./target", "./mwc"]
    option = "-l"
    sizes = list(range(10, 100000, 1000))
    nb_samples = 5
    nb_reps = 5
    plt.title("Benchmarks of {} on option {}".format(", ".join(cmds), option))
    data = measure(cmds, sizes, nb_samples, nb_reps, option)
    for cmd,meas in zip(cmds, data):
        x, y = unzip(meas)
        plt.plot(x, y, 'o', label=cmd, linestyle='None')
    plt.legend()
    plt.xlabel("Size (bytes)")
    plt.ylabel("Time (s)")
    plt.show()

main()
