#include "../headers/definitions.hpp"
#include "../headers/util_funcs.hpp"


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


void print_string_before_newline(FILE *fp, const char *str) {
    size_t idx = 0;
    bool only_spaces = 1;

    while (str[idx] != '\n' && str[idx] != '\0') {
        if (only_spaces && !isspace(str[idx]))
            only_spaces = 0;
        ++idx;
    }

    if (!only_spaces)
        fwrite(str, sizeof(char), idx, fp);
}


void print_divisor_to_file(FILE *fp) {

    assert(fp != NULL);

    fprintf(fp, "\n==========================================\n\n");
}


size_t read_lines_from_file_to_buffer(FILE *fp, char *buffer, __blksize_t block_size) {

    assert(fp != NULL);
    assert(buffer != NULL);
    assert(block_size != 0);

    size_t n_read = 0;
    size_t n_lines = 0;

    while (!feof(fp)) {
        size_t n_fread = fread(buffer + n_read, sizeof(char), (size_t) block_size, fp);

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


ssize_t decrement(ssize_t x) {
    return --x;
}


ssize_t increment(ssize_t x) {
    return ++x;
}
