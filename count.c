#include "count.h"

int count_bytes (const char* file) {
    int fd = open(file, O_RDONLY, 0444);
    int pos = lseek(fd, 0, SEEK_END);
    VERIFY_LSEEK(pos);
    close(fd);
    return pos;
}

// A line is any number of characters followed by a '\n'
void* count_lines (void* data) {
    // open file and init variables
    zone_t* zone = (zone_t*)data;
    int fd = open(zone->file, O_RDONLY, 0444);
    int pos = lseek(fd, zone->start, SEEK_CUR);
    VERIFY_LSEEK(pos);
    char buf [BUFSIZE];
    int length = zone->end - zone->start;
    int count = 0;

    // count by BUFSIZE intervals
    while (length > 0) {
        int iter = BUFSIZE < length ? BUFSIZE : length;
        int err = read(fd, buf, iter);
        VERIFY_READ(err);
        for (int i = 0; i < iter; i++) {
            if (buf[i] == '\n') count++;
        }
        length -= BUFSIZE;
    }

    // terminate
    close(fd);
    zone->count = count;
    pthread_exit(NULL);
}


int is_endword (char c) {
    switch (c) {
        case ' ': case '\t': case '\n': return 1;
        default: return 0;
    }
}

// A word is any non-is_endword() followed by a is_endword()
void* count_words (void* data) {
    // open file and init variables
    zone_t* zone = (zone_t*)data;
    int fd = open(zone->file, O_RDONLY, 0444);
    int pos = lseek(fd, zone->start, SEEK_CUR);
    VERIFY_LSEEK(pos);
    char buf [BUFSIZE];
    int length = zone->end - zone->start;
    int count = 0;
    int prev_blank = 1;

    // count by BUFSIZE intervals
    while (length > 0) {
        int iter = BUFSIZE < length ? BUFSIZE : length;
        int err = read(fd, buf, iter);
        VERIFY_READ(err);
        for (int i = 0; i < iter; i++) {
            if (is_endword(buf[i])) {
                if (!prev_blank) {
                    prev_blank = 1;
                    count++;
                }
            } else {
                prev_blank = 0;
            }
        }
        length -= BUFSIZE;
    }
    if (!prev_blank) {
        // last character of the zone could be the end of a word
        char c = 0;
        read(fd, &c, 1);
        /* we don't check here because failure means end of file,
         * which is detected by (c == 0).
         */
        if (is_endword(c) || c == 0) {
            count++;
        }
    }

    // terminate
    close(fd);
    zone->count = count;
    pthread_exit(NULL);
}
