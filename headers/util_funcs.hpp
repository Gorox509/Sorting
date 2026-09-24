#ifndef UTIL_FUNCS_H

#define UTIL_FUNCS_H

void remove_newline_symbol                      (char *str);
void clear_input                                ();

void print_string_array_with_message_to_file    (FILE *fp, const struct string_ptr_array_structure str_ptrs_arr, const char *msg_str);

void print_string_before_newline                (FILE *fp,     const char *str);
void print_divisor_to_file                      (FILE *fp);
unsigned long read_lines_from_file_to_buffer
                                                (FILE *fp,     char *buffer, const long block_size);

unsigned long assign_ptrs_from_buffer_to_strings_array
                                                (char **strings_ptrs_array, char *buffer, const unsigned long buf_size);

long decrement                               (long x);
long increment                               (long x);

#endif
