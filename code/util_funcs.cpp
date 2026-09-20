#include "../headers/definitions.h"
#include "../headers/util_funcs.h"



void remove_newline_symbol(char *str) {

    assert(str != NULL);

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


void print_string_array_with_message_to_file(FILE *fp, char **array, size_t arr_len, const char *msg_str) {

    assert(fp != NULL);
    assert(array != NULL);

    if (msg_str != NULL)
        fprintf(fp, "%s\n", msg_str);

    for (size_t i = 0; i < arr_len; ++i) {
        print_string_before_newline(fp, array[i]);
    }

    fprintf(fp, "\n");
}


void print_string_before_newline(FILE *fp, char *str) {
    size_t idx = 0;

    while (str[idx] != '\n' && str[idx] != '\0')
        ++idx;

    fwrite(str, sizeof(char), idx, fp);
}


void print_divisor_to_file(FILE *fp) {

    assert(fp != NULL);

    fprintf(fp, "\n==========================================\n\n");
}


size_t read_lines_from_file_to_buffer(FILE *fp, char *buffer, __blksize_t bulk_size) {

    assert(fp != NULL);
    assert(buffer != NULL);
    assert(bulk_size != 0);

    size_t n_read = 0;
    size_t n_lines = 0;

    while (!feof(fp)) {
        size_t n_fread = fread(buffer + n_read, sizeof(char), (size_t) bulk_size, fp);

        for (size_t i = 0; i < n_fread; ++i) {
            if (buffer[n_read + i] == '\n' || buffer[n_read + i] == '\0') {
                ++n_lines;
            }
        }

        n_read += n_fread;
    }
    buffer[++n_read] = '\0';

    return n_lines;
}


size_t assign_ptrs_from_buffer_to_strings_array(char **strings_ptrs_array, char *buffer, size_t buf_size) {

    assert(strings_ptrs_array != NULL);
    assert(buffer != NULL);

    size_t idx_array = 0;

    for (size_t i = 0; i < buf_size - 1; ++i) {
        if (buffer[i] == '\n' || buffer[i] == '\0') {
            strings_ptrs_array[idx_array++] = buffer + i + 1;
        }
    }

    return idx_array;
}

void destruct_array_of_strings(char **array, size_t strings_count) {

    assert(array != NULL);

    for (size_t i = 0; i < strings_count; ++i)
        free(array[i]);

    free(array);
}
