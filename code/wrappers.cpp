#include "../headers/definitions.hpp"
#include "../headers/wrappers.hpp"

void *safe_calloc(const size_t _nmemb, const size_t _size) {
    void *ptr = calloc(_nmemb, _size);

    if (ptr == NULL) {
        fprintf(stderr, "Error while allocating");
        exit(1);
    }
    return ptr;
}


FILE *safe_fopen(const char *_filename, const char *_mode) {
    FILE *fp = fopen(_filename, _mode);

    if (fp == NULL) {
        fprintf(stderr, "Error while opening file");
        return NULL;
    }
    return fp;
}


int safe_stat(const char *filename, struct stat *text_stat) {
    if (stat(filename, text_stat) == -1) {
        fprintf(stderr, "Error while reading file stats");
        return -1;
    }
    return 0;
}


void destruct_struct_strings_arr(struct string_ptr_array_structure str_ptrs_arr) {
    free(str_ptrs_arr.array);
}
