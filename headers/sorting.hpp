#ifndef SORTING_H

#define SORTING_H

char **merge_sort_strings(struct string_ptr_array_structure *str_ptrs_arr,
                                                     const unsigned long max_str_len,
                                                     int (*const comparator_func)(const void *a, const void *b));

void merge_sort_strings_splitting_in_half(const struct string_ptr_array_structure *str_ptrs_arr,
                                                struct string_ptr_array_structure *left,
                                                struct string_ptr_array_structure *right);

void merge_sort_strings_merging(struct string_ptr_array_structure *str_ptrs_arr,
                                struct string_ptr_array_structure *left,
                                struct string_ptr_array_structure *right,
                                int (*const comparator_func)(const void *a, const void *b));

#endif
