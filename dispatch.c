#include "dispatch.h"

zone_t zones [NB_THREADS];

pthread_t counters [NB_THREADS];

int dispatch (const char* file, void* counter (void*)) {
    // open to determine length -> distribution of ranges
    int fd = open(file, O_RDONLY, 0444);
    int length = lseek(fd, 0, SEEK_END);
    close(fd);

    // launch threads
    for (int i = 0; i < NB_THREADS; i++) {
        zones[i].file = file;
        zones[i].start = (i * length) / NB_THREADS;
        zones[i].end = ((i+1) * length) / NB_THREADS;
        pthread_create(&counters[i], NULL, counter, (void*)&zones[i]);
    }

    // terminate threads and calculate sum
    int sum = 0;
    for (int i = 0; i < NB_THREADS; i++) pthread_join(counters[i], NULL);
    for (int i = 0; i < NB_THREADS; i++) sum += zones[i].count;
    return sum;
}
