#include "../headers/definitions.hpp"
#include "../headers/sorting.hpp"


struct string_ptr_array_structure merge_sort_strings(struct string_ptr_array_structure str_ptrs_arr,
                                                     size_t max_str_len, 
                                                     int (*comparator_func)(const void *a, const void *b)) {

    assert(str_ptrs_arr.array != NULL);
    assert(comparator_func != NULL);
//TODO: где ассерты лол? причем не только здесь
    if (str_ptrs_arr.len <= 1)
        return str_ptrs_arr;

    size_t left_len = str_ptrs_arr.len / 2 + str_ptrs_arr.len % 2;
    size_t right_len = str_ptrs_arr.len / 2;

    struct string_ptr_array_structure left = {.len = left_len};
    struct string_ptr_array_structure right = {.len = right_len};

    left.array  = (char**) safe_calloc(left.len, sizeof(char*)); //TODO: что если каллок не найдет места?? -- done with wrapper
    right.array = (char**) safe_calloc(right.len, sizeof(char*));

    merge_sort_strings_splitting_in_half(str_ptrs_arr, left, right);

    merge_sort_strings(left, max_str_len, comparator_func);
    merge_sort_strings(right, max_str_len, comparator_func);

    merge_sort_strings_merging(str_ptrs_arr, left, right, comparator_func);

    destruct_struct_strings_arr(left);
    destruct_struct_strings_arr(right);

    return str_ptrs_arr;
}


void merge_sort_strings_splitting_in_half(  struct string_ptr_array_structure str_ptrs_arr,
                                            struct string_ptr_array_structure left,
                                            struct string_ptr_array_structure right) {

    assert(str_ptrs_arr.array != NULL);
    assert(right.array != NULL);
    assert(left.array  != NULL);

    for (size_t i = 0; i < left.len; ++i) {
        left.array[i] = str_ptrs_arr.array[i];
    }

    for (size_t i = 0; i < right.len; ++i) {
        right.array[i] = str_ptrs_arr.array[i + left.len];
    }
}


void merge_sort_strings_merging(struct string_ptr_array_structure str_ptrs_arr,
                                struct string_ptr_array_structure left,
                                struct string_ptr_array_structure right,
                                int (*comparator_func)(const void *a, const void *b)) {

    assert(str_ptrs_arr.array != NULL);
    assert(left.array != NULL);
    assert(right.array != NULL);
    assert(comparator_func != NULL);

    size_t left_idx = 0, right_idx = 0;

    for (size_t i = 0; i < left.len + right.len; ++i) {
        bool left_is_bigger = 0;

        if (left_idx >= left.len)
            left_is_bigger = 0;

        else if (right_idx >= right.len)
            left_is_bigger = 1;

        else
            left_is_bigger = (*comparator_func)(&left.array[left_idx], &right.array[right_idx]) > 0 ? 0 : 1;

        str_ptrs_arr.array[i] = left_is_bigger ? left.array[left_idx++] : right.array[right_idx++];
    }
}
