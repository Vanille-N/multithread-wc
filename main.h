/*  Main function, argument parsing.
    also verifies that the file exists, and calls dispatch.
    Exit codes are WR_* depending on what is wrong with the
    command line arguments.
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "count.h"
#include "dispatch.h"

#define WR_OPT 1
#define WR_ARG 2
#define WR_FILE 3

#endif
