#include "../headers/definitions.hpp"
#include "../headers/comparators.hpp"
#include "../headers/sorting.hpp"
#include "../headers/util_funcs.hpp"
#include "../headers/wrappers.hpp"

#include "util_funcs.cpp"
#include "sorting.cpp"
#include "comparators.cpp"
#include "wrappers.cpp"




int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Error: wrong arguments");
        return -1;
    }

    size_t strings_count = 0;
    char *filename = argv[1];
    char *filename_out = argv[2];

    struct stat text_stat = {};
    safe_stat(filename, &text_stat); //TODO: function - done
    __off_t file_size = text_stat.st_size;
    __blksize_t optimal_block_size = text_stat.st_blksize;

    char *buffer = (char*) safe_calloc((size_t) file_size + 2, sizeof(char)); // +2 for \0 at the start and the end
    buffer[0] = '\0';

    FILE *fp = safe_fopen(filename, "rb"); //TODO: check null - done
    strings_count = read_lines_from_file_to_buffer(fp, buffer + 1, optimal_block_size); //TODO: temp buf?? - done
    fclose(fp);

    struct string_ptr_array_structure str_ptrs_arr = {.len = strings_count};
    str_ptrs_arr.array = (char**) safe_calloc(strings_count, sizeof(char*));
    assign_ptrs_from_buffer_to_strings_array(str_ptrs_arr.array, buffer, (size_t) file_size + 2);

    FILE *fp_out = safe_fopen(filename_out, "wb");

    merge_sort_strings(str_ptrs_arr, MAX_STR_LEN, comparator_strings_increase);
    print_string_array_with_message_to_file(fp_out, str_ptrs_arr, NULL);
    print_divisor_to_file(fp_out);

    qsort(str_ptrs_arr.array, str_ptrs_arr.len, sizeof(char *), comparator_strings_rhythm);
    print_string_array_with_message_to_file(fp_out, str_ptrs_arr, NULL);
    print_divisor_to_file(fp_out);

    fprintf(fp_out, "%s", buffer + 1);

    fclose(fp_out);

    free(buffer);
    destruct_struct_strings_arr(str_ptrs_arr);

    return 0;
}
