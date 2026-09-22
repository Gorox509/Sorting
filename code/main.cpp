#include "../headers/definitions.hpp"
#include "../headers/comparators.hpp"
#include "../headers/sorting.hpp"
#include "../headers/util_funcs.hpp"
#include "../headers/wrappers.hpp"

#include "util_funcs.cpp"
#include "sorting.cpp"
#include "comparators.cpp"
#include "wrappers.cpp"
#include <cstdlib>



int main() {
    size_t strings_count = 0;
    char filename[] = "onegin.txt";

    struct stat text_stat = {};
    safe_stat(filename, &text_stat); //TODO: function - done
    __off_t file_size = text_stat.st_size;
    __blksize_t optimal_block_size = text_stat.st_blksize;

    char *buffer = (char*) safe_calloc((size_t) file_size + 1, sizeof(char)); // +1 for \0 at the end

    FILE *fp = safe_fopen(filename, "rb"); //TODO: check null - done
    strings_count = read_lines_from_file_to_buffer(fp, buffer, optimal_block_size); //TODO: temp buf?? - done
    fclose(fp);

    char **strings_ptrs_array = (char**) safe_calloc(strings_count, sizeof(char*));
    assign_ptrs_from_buffer_to_strings_array(strings_ptrs_array, buffer, (size_t) file_size + 1);

    FILE *fp_out = safe_fopen("output.txt", "wb");

    merge_sort_strings(strings_ptrs_array, strings_count, MAX_STR_LEN, comparator_strings_increase);
    print_string_array_with_message_to_file(fp_out, strings_ptrs_array, strings_count, NULL);
    print_divisor_to_file(fp_out);

    qsort(strings_ptrs_array, strings_count, sizeof(char *), comparator_strings_rhythm); // TODO: to qsort
    print_string_array_with_message_to_file(fp_out, strings_ptrs_array, strings_count, NULL);
    print_divisor_to_file(fp_out);

    fprintf(fp_out, "%s", buffer);

    fclose(fp_out);

    free(buffer);
    free(strings_ptrs_array);

    return 0;
}
