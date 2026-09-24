#ifndef WRAPPERS_H

#define WRAPPERS_H

void *safe_calloc   (const unsigned long _nmemb, const unsigned long _size);
FILE *safe_fopen    (const char *_filename, const char *_mode);
int   safe_stat     (const char *filename, struct stat *text_stat);

void destruct_struct_strings_arr(struct string_ptr_array_structure str_ptrs_arr);

#endif
