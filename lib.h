#ifndef LIB_H
#define LIB_H

#define NB_THREADS 5
#define BUFSIZE 10000

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>

int count_bytes (const char* file);

int count_lines (const char* file);
#endif
