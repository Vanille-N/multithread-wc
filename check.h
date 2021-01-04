#ifndef CHECK_H
#define CHECK_H

#include <stdlib.h>

// exit codes :: arguments
#define WR_OPT 1 // invalid option
#define WR_ARG 2 // badly formatted argument
#define WR_FILE 3 // file does not exist

// exit codes :: syscalls
#define ERR_RD 101 // read failed
#define ERR_OP 102 // open failed
#define ERR_SK 103 // lseek failed

// error handlers
#define VERIFY_READ(X) { \
    if ((X) == -1) { \
        perror("Failed to read. "); \
        exit(ERR_RD); \
    } \
}

#define VERIFY_OPEN(X) { \
    if ((X) == -1) { \
        perror("Failed to open. "); \
        exit(ERR_OP); \
    } \
}

#define VERIFY_LSEEK(X) { \
    if ((X) == -1) { \
        perror("Failed to seek. "); \
        exit(ERR_SK); \
    } \
}

#endif
