#ifndef DEFINITIONS_H

#define DEFINITIONS_H

//#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

const unsigned long MAX_STR_LEN = 100;

struct string_ptr_array_structure {
    char **array = NULL;
    unsigned long len = 0;
};

#endif
