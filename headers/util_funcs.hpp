#ifndef UTIL_FUNCS_H

#define UTIL_FUNCS_H

void remove_newline_symbol                      (char *str);
void clear_input                                ();

void print_string_array_with_message_to_file    (FILE *fp, struct string_ptr_array_structure str_ptrs_arr, const char *msg_str);

void print_string_before_newline                (FILE *fp,     const char *str);
void print_divisor_to_file                      (FILE *fp);
size_t read_lines_from_file_to_buffer           (FILE *fp,     char *buffer, __blksize_t bulk_size);

size_t assign_ptrs_from_buffer_to_strings_array (char **strings_ptrs_array, char *buffer, size_t buf_size);

ssize_t decrement                               (ssize_t x);
ssize_t increment                               (ssize_t x);

#endif
