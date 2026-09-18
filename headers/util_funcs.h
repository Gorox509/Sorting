#ifndef UTIL_FUNCS_H

#define UTIL_FUNCS_H

void destruct_array_of_strings                  (char **array, size_t strings_count);
void remove_newline_symbol                      (char *str);
void clear_input                                ();

                                                                                                     //TODO: зачем 3 одинаковых функции печати? - сделал
void print_string_array_with_message_to_file    (FILE *fp,                                           // можно сделать 3 функцию (если вместо строки NULL -- no_msg) // стандартный вывод это тоже типа файл, у него есть дискриптор
                                                 char **array, size_t arr_len, const char *msg_str);

void print_divisor_to_file                      (FILE *fp);

ssize_t read_file_to_buffer                     (FILE *fp,     char *buffer);
size_t read_buffer_to_array                     (char **array, char *buffer, size_t buf_len);
ssize_t read_file_to_buffer_lines               (FILE *fp,     char *buffer);

#endif
