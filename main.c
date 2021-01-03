#include "main.h"

void invalid (const char* msg, int retcode) {
    printf(msg);
    printf("usage: mwc [-l|-w|-c] FILE\n");
    printf("  count (l)ines, (w)ords, (c)haracters in FILE (default -w)\n");
    exit(retcode);
}

int main (int argc, char** argv) {
    if (argc == 1) invalid("Not enough arguments\n", WR_ARG);
    char* file = NULL;
    char mode = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') { // treat as an argument
            if (mode != 0) invalid("Too many optional arguments\n", WR_OPT); // already have an option
            switch (argv[i][1]) {
                case 'w': case 'c': case 'l':
                    mode = argv[i][1];
                    break;
                default: invalid("Invalid optional argument\n", WR_OPT); // unknown option: not w/l/c
            }
            if (argv[i][2] != 0) invalid("Optional argument too long\n", WR_OPT); // option is not -w/-l/-c
        } else {
            if (file != NULL) invalid("Too many positional arguments\n", WR_ARG);
            file = argv[i];
        }
    }
    if (file == NULL) invalid("Not enough positional arguments\n", WR_ARG);
    if (mode == 0) mode = 'w'; // default is -w

    if (access(file, R_OK) == 0) { // thanks to this we don't have to handle errors for open()
        switch (mode) {
            case 'c': {
                int n = count_bytes(file);
                printf("%d %s\n", n, file);
                break;
            }
            case 'w': {
                int n = dispatch(file, count_words);
                printf("%d %s\n", n, file);
                break;
            }
            case 'l': {
                int n = dispatch(file, count_lines);
                printf("%d %s\n", n, file);
                break;
            }
        }
    } else {
        invalid("File does not exist\n", WR_FILE);
    }
    return 0;
}
