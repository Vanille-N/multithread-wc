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

int is_endword (char c) {
    switch (c) {
        case ' ': case '\t': case '\n': case EOF: case 0: return 1;
        default: return 0;
    }
}

// A word is any non-is_endword() followed by a is_endword()
void* words_in_zone (void* data) {
    // open file and init variables
    zone_t* zone = (zone_t*)data;
    int fd = open(zone->file, O_RDONLY, 0444);
    lseek(fd, zone->start, SEEK_CUR);
    char buf [BUFSIZE];
    int length = zone->end - zone->start;
    zone->count = 0;
    int prev_blank = 1;

    // count by BUFSIZE intervals
    while (length > 0) {
        int iter = BUFSIZE < length ? BUFSIZE : length;
        read(fd, buf, iter);
        // printf("<<%s>>", buf);
        for (int i = 0; i < iter; i++) {
            // printf("At %d-%d: reading '%c' <%d>\n", zone->start, zone->end, buf[i], buf[i]);
            if (is_endword(buf[i])) {
                if (!prev_blank) {
                    prev_blank = 1;
                    zone->count++;
                    // printf("At %d-%d: counted word\n", zone->start, zone->end);
                    // printf("'%c' (%d) at %d is the end of a word\n", buf[i-1], buf[i-1], zone->end - length);
                }
            } else {
                prev_blank = 0;
            }
        }
        length -= BUFSIZE;
    }
    if (!prev_blank) {
        // last character of the zone could be the end of a word
        char c;
        read(fd, &c, 1);
        // printf("At %d-%d: check first char of next zone\n", zone->start, zone->end);
        if (is_endword(c)) {
            // printf("At %d-%d: yup, '%c' (%d) is the end of a word\n", zone->start, zone->end, c, c);
            zone->count++;
        }
    }

    // terminate
    close(fd);
    pthread_exit(NULL);
}

