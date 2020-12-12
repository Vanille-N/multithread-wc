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

int count_lines (const char* file) {
    // open to determine length -> distribution of ranges
    int fd = open(file, O_RDONLY, 0444);
    int length = lseek(fd, 0, SEEK_END);
    close(fd);

    // launch threads
    for (int i = 0; i < NB_THREADS; i++) {
        zones[i].file = file;
        zones[i].start = (i * length) / NB_THREADS;
        zones[i].end = ((i+1) * length) / NB_THREADS;
        pthread_create(&counters[i], NULL, lines_in_zone, (void*)&zones[i]);
    }

    // terminate threads and calculate sum
    int sum = 0;
    for (int i = 0; i < NB_THREADS; i++) pthread_join(counters[i], NULL);
    for (int i = 0; i < NB_THREADS; i++) sum += zones[i].count;
    return sum;
}
