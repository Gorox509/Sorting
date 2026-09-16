#include "../headers/definitions.h"
#include "../headers/comparators.h"
#include "../headers/sorting.h"
#include "../headers/util_funcs.h"

#include "util_funcs.cpp"
#include "sorting.cpp"
#include "comparators.cpp"


int main() {
    size_t strings_count = 0;

    FILE *fp = fopen("original.txt", "r");

    char **array = (char**) calloc(MAX_BUF_SIZE, sizeof(char*));

    char *buffer = (char*)  calloc(MAX_STR_LEN * MAX_BUF_SIZE, sizeof(char));

    ssize_t buffer_len = read_file_to_buffer(fp, buffer);

    fclose(fp);

    strings_count = read_buffer_to_array(array, buffer, buffer_len);

    free(buffer);

    char **array_old = (char**) calloc(strings_count, sizeof(char*));
    memcpy(array_old, array, strings_count * sizeof(char*));

    FILE *fp_out = fopen("output.txt", "w");

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void*, void*))compare_strings_increasingly);
    print_string_array_with_message_to_file(fp, array, strings_count, NULL);
    print_divisor_to_file(fp);

    merge_sort_strings(array, strings_count, MAX_STR_LEN * sizeof(char), (ssize_t (*)(void*, void*))compare_strings_from_end); // TODO: to qsort
    print_string_array_with_message_to_file(fp, array, strings_count, NULL);
    print_divisor_to_file(fp);

    print_string_array_with_message_to_file(fp, array_old, strings_count, NULL);

    fclose(fp_out);


    destruct_array_of_strings(array, strings_count);

    free(array_old);

    return 0;
}