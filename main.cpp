#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


const int MAX_STR_LEN = 100;


void remove_newline_symbol                      (char *str);
void clear_input                                ();
void print_string_array                         (char **array, size_t arr_len);

char** merge_sort_strings                       (char **array, size_t arr_len,  size_t max_str_len, 
                                                    ssize_t (*comparator_func)(void *a, void *b));

void merge_sort_strings_splitting_in_half       (char **array, char **left, char **right, size_t left_len, size_t right_len);

void merge_sort_strings_merging                 (char **array, char **left, char **right, size_t left_len, size_t right_len, 
                                                    ssize_t (*comparator_func)(void *a, void *b));

ssize_t compare_strings_increasingly            (char *str1,   char *str2);
ssize_t compare_strings_decreasingly            (char *str1,   char *str2);
ssize_t compare_strings_by_length_increasingly  (char *str1,   char *str2);
ssize_t compare_strings_strcmp                  (char *str1,   char *str2);



int main() {
    size_t strings_count = 0;

    printf("Enter amount of strings to sort: ");

    scanf("%zu", &strings_count);
    clear_input();

    char **array = (char**) calloc(strings_count, sizeof(char*));

    for (size_t i = 0; i < strings_count; ++i) {
        array[i] = (char*) calloc(MAX_STR_LEN, sizeof(char));

        fgets(array[i], MAX_STR_LEN, stdin);
        remove_newline_symbol(array[i]);
    }

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void *, void*))compare_strings_strcmp);
    printf("Strcmp:             ");
    print_string_array(array, strings_count);

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void *, void*))compare_strings_increasingly);
    printf("Increasing order:   ");
    print_string_array(array, strings_count);

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void *, void*))compare_strings_decreasingly);
    printf("Reverse order:      ");
    print_string_array(array, strings_count);

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void *, void*))compare_strings_by_length_increasingly);
    printf("By length:          ");
    print_string_array(array, strings_count);


    for (size_t i = 0; i < strings_count; ++i)
        free(array[i]);
    free(array);

    return 0;
}


char** merge_sort_strings(char **array, size_t arr_len, size_t max_str_len, ssize_t (*comparator_func)(void *a, void *b)) {

    if (arr_len == 1)
        return array;

    size_t left_len = arr_len / 2 + arr_len % 2;
    size_t right_len = arr_len / 2;

    char **left  = (char**) calloc(left_len, sizeof(char*));
    char **right = (char**) calloc(right_len, sizeof(char*));

    merge_sort_strings_splitting_in_half(array, left, right, left_len, right_len);
    
    merge_sort_strings(left, left_len, max_str_len, comparator_func);
    merge_sort_strings(right, right_len, max_str_len, comparator_func);

    merge_sort_strings_merging(array, left, right, left_len, right_len, comparator_func);

    free(left);
    free(right);

    return array;
}


void remove_newline_symbol(char *str) {
    size_t iter = 0;
    
    while (str[iter] != '\0') {
        if (str[iter] == '\n') {
            str[iter] = '\0';
            return;
        }
        iter++;
    }
}


void clear_input() {
    char ch = 0;

    while (!isspace(ch))
        ch = (char) getchar();
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


ssize_t compare_strings_increasingly(char *str1, char *str2) {
    size_t idx = 0;

    while (str1[idx] == str2[idx] && str1[idx] != '\0' && str2[idx] != '\0')
        ++idx;

    return (ssize_t) str1[idx] - str2[idx];
}


ssize_t compare_strings_decreasingly(char *str1, char *str2) {
    size_t idx = 0;

    while (str1[idx] == str2[idx] && str1[idx] != '\0' && str2[idx] != '\0')
        ++idx;

    return (ssize_t) str2[idx] - str1[idx];
}


ssize_t compare_strings_by_length_increasingly(char *str1, char *str2) {
    return strlen(str1) - strlen(str2);
}


void print_string_array(char **array, size_t arr_len) {
    for (size_t i = 0; i < arr_len; ++i) {
        printf("[%s] ", array[i]);
    }

    printf("\n");
}


ssize_t compare_strings_strcmp(char *str1, char *str2) {
    return (ssize_t) strcmp(str1, str2);
}