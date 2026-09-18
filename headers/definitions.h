#ifndef DEFINITIONS_H

#define DEFINITIONS_H

//#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

const int MAX_STR_LEN = 100;
const int MAX_BUF_SIZE = 100000;

struct string_ptr_array_structure {
    char **array = NULL;
    size_t len = 0;
};

#endif
