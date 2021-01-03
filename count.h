/*  Counters: take information on the target file
    and the zone they have to handle, and yield the count
    of various elements within that area.
    BUFSIZE determines the length of the static buffers
    used to read the file.
 */

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
