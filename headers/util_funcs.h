#ifndef UTIL_FUNCS_H

#define UTIL_FUNCS_H

void destruct_array_of_strings                  (char **array, size_t strings_count);
void remove_newline_symbol                      (char *str);
void clear_input                                ();

                                                                                                     //TODO: зачем 3 одинаковых функции печати? - сделал
void print_string_array_with_message_to_file    (FILE *fp,                                           // можно сделать 3 функцию (если вместо строки NULL -- no_msg) // стандартный вывод это тоже типа файл, у него есть дискриптор
                                                 char **array, size_t arr_len, const char *msg_str);

void print_divisor_to_file                      (FILE *fp);
size_t assign_ptrs_from_buffer_to_strings_array (char **strings_ptrs_array, char *buffer, size_t buf_size);
size_t read_lines_from_file_to_buffer           (FILE *fp,     char *buffer, __blksize_t bulk_size);
void print_string_before_newline                (FILE *fp,     char *str);

#endif
