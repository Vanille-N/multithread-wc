from subprocess import run
import time as t


def all_identical(data):
    if data == []:
        return True
    for d in data:
        if d != data[0]:
            return False
    return True

def measure_instance(cmds, input):
    measures = []
    outs = []
    for cmd in cmds:
        t_start = t.clock()
        res = run(cmd, [cmd, input], capture_output=True)
        t_end = t.clock()
        measures.append(t_end - t_start)
        outs.append(res.stdout)
    if all_identical(outs):
        return measures
    else:
        print("Not all tools agree on the output")
        for cmd, out in zip(cmds, outs):
            print("    {} [{}]".format(cmd, out))
        return []

def build_test(size):
    for i in range(size / 1000):
        os.system("< /dev/urandom tr -dc '\n\t [:alnum:]' | head -c1000 >> benches/rnd.plain")
    return "benches/rnd.plain"

def measure_size(cmds, size, nb_samples, nb_reps):
    data = [0] * len(cmds)
    for s in range(nb_samples):
        file = build_test(size)
        for r in range(nb_reps):
            times = measure_instance(cmds, file)
