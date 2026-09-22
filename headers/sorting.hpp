#ifndef SORTING_H

#define SORTING_H

struct string_ptr_array_structure merge_sort_strings(struct string_ptr_array_structure str_ptrs_arr,
                                                     size_t max_str_len,
                                                     int (*comparator_func)(const void *a, const void *b));

void merge_sort_strings_splitting_in_half(  struct string_ptr_array_structure str_ptrs_arr,
                                            struct string_ptr_array_structure left,
                                            struct string_ptr_array_structure right);

void merge_sort_strings_merging(struct string_ptr_array_structure str_ptrs_arr,
                                struct string_ptr_array_structure left,
                                struct string_ptr_array_structure right,
                                int (*comparator_func)(const void *a, const void *b));

#endif
