#ifndef COUNT_H
#define COUNT_H

#define BUFSIZE (64 * 1024)

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "dispatch.h"

int count_bytes (const char* file);

void* count_lines (void* data);

void* count_words (void* data);

#endif
