#include "../headers/definitions.h"
#include "../headers/sorting.h"


char** merge_sort_strings(char **array, size_t arr_len, size_t max_str_len, ssize_t (*comparator_func)(void *a, void *b)) {

    assert(array != NULL);
    assert(comparator_func != NULL);
//TODO: где ассерты лол? причем не только здесь
    if (arr_len <= 1)
        return array;

    size_t left_len = arr_len / 2 + arr_len % 2;
    size_t right_len = arr_len / 2;

    char **left  = (char**) safe_calloc(left_len, sizeof(char*)); //TODO: что если каллок не найдет места?? -- done with wrapper
    char **right = (char**) safe_calloc(right_len, sizeof(char*));

    merge_sort_strings_splitting_in_half(array, left, right, left_len, right_len);

    merge_sort_strings(left, left_len, max_str_len, comparator_func);
    merge_sort_strings(right, right_len, max_str_len, comparator_func);

    merge_sort_strings_merging(array, left, right, left_len, right_len, comparator_func);

    free(left);
    free(right);

    return array;
}


void merge_sort_strings_splitting_in_half(char **array, char **left, char **right, size_t left_len, size_t right_len) {

    assert(array != NULL);
    assert(right != NULL);
    assert(left  != NULL);

    for (size_t i = 0; i < left_len; ++i) {
        left[i] = array[i];
    }

    for (size_t i = 0; i < right_len; ++i) {
        right[i] = array[i + left_len];
    }
}


void merge_sort_strings_merging(char **array, char **left, char **right, size_t left_len, size_t right_len, ssize_t (*comparator_func)(void *a, void *b)) {

    assert(array != NULL);
    assert(left != NULL);
    assert(right != NULL);
    assert(comparator_func != NULL);

    size_t left_idx = 0, right_idx = 0;

    for (size_t i = 0; i < left_len + right_len; ++i) {
        bool left_is_bigger = 0;

        if (left_idx >= left_len)
            left_is_bigger = 0;

        else if (right_idx >= right_len)
            left_is_bigger = 1;

        else
            left_is_bigger = (*comparator_func)(left[left_idx], right[right_idx]) > 0 ? 0 : 1;

        array[i] = left_is_bigger ? left[left_idx++] : right[right_idx++];
    }
}
