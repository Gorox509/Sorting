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
        fprintf(fp, "[%s]\n", array[i]);
    }

    fprintf(fp, "\n");
}


void print_divisor_to_file(FILE *fp) {

    assert(fp != NULL);

    fprintf(fp, "\n==========================================\n\n");
}


ssize_t read_file_to_buffer(FILE *fp, char *buffer) {

    assert(fp != NULL);
    assert(buffer != NULL);

    char *buffer_for_buffer = (char*) calloc(MAX_STR_LEN, sizeof(char));

    if (buffer_for_buffer == NULL)
        return -1;

    size_t n_read = 0;
    bool previous_is_space = 0;

    while (!feof(fp)) {

        size_t idx1 = 0, idx2 = 0;

        size_t n_fread = fread(buffer_for_buffer, sizeof(char), MAX_STR_LEN, fp);

        char ch = 0;

        while (ch != EOF && idx1 < n_fread) {
            ch = buffer_for_buffer[idx1++];

            if (isalpha(ch) || (ch == '-' && !previous_is_space)) {
                previous_is_space = 0;
                buffer[n_read + idx2++] = (char) tolower(ch);
            }

            if (isspace(ch) && !previous_is_space) {
                previous_is_space = 1;
                buffer[n_read + idx2++] = '\0';
            } //TODO: ты считывешь из файла fgetc? это же вечность!! посмотри фукнцию fread - дело сделано
        }
        n_read += idx2;
    }
    buffer[++n_read] = '\0';
    free(buffer_for_buffer);

    return (ssize_t) n_read + 1;
}


size_t read_buffer_to_array(char **array, char *buffer, size_t buf_len) {

    assert(array != NULL);
    assert(buffer != NULL);

    size_t arr_idx = 0;

    for (size_t i = 0; i < buf_len; ) {
        array[arr_idx] = (char*) calloc(MAX_STR_LEN, sizeof(char));

        size_t j = 0;
        while (buffer[i] != '\0') {

            array[arr_idx][j] = buffer[i];
            ++i;
            ++j;
        }

        array[arr_idx++][j] = buffer[i++];
    }
    return arr_idx - 1;
}


void destruct_array_of_strings(char **array, size_t strings_count) {

    assert(array != NULL);

    for (size_t i = 0; i < strings_count; ++i)
        free(array[i]);

    free(array);
}
