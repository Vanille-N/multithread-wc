#include "lib.h"

int count_bytes (const char* file) {
    int fd = open(file, O_RDONLY, 0444);
    return lseek(fd, 0, SEEK_END);
}
