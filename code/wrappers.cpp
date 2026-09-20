#include "../headers/definitions.hpp"
#include "../headers/wrappers.hpp"

void *safe_calloc(size_t _nmemb, size_t _size) {
    void *ptr = calloc(_nmemb, _size);

    if (ptr == NULL) {
        fprintf(stderr, "Error while allocating");
        abort();
    }
    return ptr;
}


FILE *safe_fopen(const char *_filename, const char *_mode) {
    FILE *fp = fopen(_filename, _mode);

    if (fp == NULL) {
        fprintf(stderr, "Error while opening file");
        abort();
    }
    return fp;
}


void safe_stat(const char *filename, struct stat *text_stat) {
    if (stat(filename, text_stat) == -1) {
        fprintf(stderr, "Error while reading file stats");
        abort();
    }
}
