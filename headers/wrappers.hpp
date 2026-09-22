#ifndef WRAPPERS_H

#define WRAPPERS_H

void *safe_calloc   (size_t _nmemb, size_t _size);
FILE *safe_fopen    (const char *_filename, const char *_mode);
void safe_stat      (const char *filename, struct stat *text_stat);

void destruct_struct_strings_arr(struct string_ptr_array_structure str_ptrs_arr);

#endif
