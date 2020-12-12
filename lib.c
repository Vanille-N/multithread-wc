#include "lib.h"

int count_bytes (const char* file) {
    int fd = open(file, O_RDONLY, 0444);
    int pos = lseek(fd, 0, SEEK_END);
    close(fd);
    return pos;
}

// tells a thread what he should do
typedef struct {
    const char* file; // what file to read
    int start; // where to start reading
    int end; // where to end
    int count; // return value = count
} zone_t;

zone_t zones [NB_THREADS];
pthread_t counters [NB_THREADS];

// A line is any number of characters followed by a '\n'
void* lines_in_zone (void* data) {
    // open file and init variables
    zone_t* zone = (zone_t*)data;
    int fd = open(zone->file, O_RDONLY, 0444);
    lseek(fd, zone->start, SEEK_CUR);
    char buf [BUFSIZE];
    int length = zone->end - zone->start;
    zone->count = 0;

    // count by BUFSIZE intervals
    while (length > 0) {
        read(fd, buf, BUFSIZE);
        // printf("<<%s>>", buf);
        int iter = BUFSIZE < length ? BUFSIZE : length;
        for (int i = 0; i < iter; i++) {
            if (buf[i] == '\n') zone->count++;
        }
        length -= BUFSIZE;
    }

    // terminate
    close(fd);
    pthread_exit(NULL);
}

