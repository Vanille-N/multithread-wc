#ifndef DISPATCH_H
#define DISPATCH_H

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>

#define NB_THREADS 4

// tells a thread what he should do
typedef struct {
    const char* file; // what file to read
    int start; // where to start reading
    int end; // where to end
    int count; // return value
} zone_t;

int dispatch (const char* file, void* counter (void*));

#endif
