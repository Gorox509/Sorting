#ifndef SORTING_H

#define SORTING_H

char** merge_sort_strings                       (char **array, size_t arr_len,  size_t max_str_len, 
                                                    ssize_t (*comparator_func)(void *a, void *b));

void merge_sort_strings_splitting_in_half       (char **array, char **left, char **right, size_t left_len, size_t right_len); //TODO: сделай стуктуру {массив, размер} -- сразу меньше аргументов 

void merge_sort_strings_merging                 (char **array, char **left, char **right, size_t left_len, size_t right_len, 
                                                    ssize_t (*comparator_func)(void *a, void *b));

#endif