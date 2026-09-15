#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


const int MAX_STR_LEN = 100;
const int MAX_BUF_SIZE = 10000;


void remove_newline_symbol                      (char *str);
void clear_input                                ();
void print_string_array_with_message            (char **array, size_t arr_len, const char *msg_str);
void print_string_array_with_message_to_file    (FILE *fp, 
                                                 char **array, size_t arr_len, const char *msg_str);
void print_string_array_no_message_to_file      (FILE *fp, 
                                                 char **array, size_t arr_len);

void print_divisor_to_file                      (FILE *fp);

char** merge_sort_strings                       (char **array, size_t arr_len,  size_t max_str_len, 
                                                    ssize_t (*comparator_func)(void *a, void *b));

void merge_sort_strings_splitting_in_half       (char **array, char **left, char **right, size_t left_len, size_t right_len);

void merge_sort_strings_merging                 (char **array, char **left, char **right, size_t left_len, size_t right_len, 
                                                    ssize_t (*comparator_func)(void *a, void *b));

ssize_t compare_strings_increasingly            (char *str1,   char *str2);
ssize_t compare_strings_decreasingly            (char *str1,   char *str2);
ssize_t compare_strings_by_length_increasingly  (char *str1,   char *str2);
ssize_t compare_strings_strcmp                  (char *str1,   char *str2);
ssize_t compare_strings_from_end                (char *str1,   char *str2);

size_t read_string_from_file_to_buffer          (FILE *fp,     char *buffer, char **buffer_ptr);
size_t read_file_to_buffer                      (FILE *fp,     char *buffer);
size_t read_buffer_to_array                     (char **array, char *buffer, size_t buf_len);



int main() {
    size_t strings_count = 0;
    /*
    printf("Enter amount of strings to sort: ");

    scanf("%zu", &strings_count);
    clear_input();

    char **array = (char**) calloc(strings_count, sizeof(char*));

    for (size_t i = 0; i < strings_count; ++i) {
        array[i] = (char*) calloc(MAX_STR_LEN, sizeof(char));

        fgets(array[i], MAX_STR_LEN, stdin);
        remove_newline_symbol(array[i]);
    }
    */
    
    FILE *fp = fopen("original.txt", "r");

    char **array = (char**) calloc(MAX_BUF_SIZE, sizeof(char*));

    char *buffer = (char *) calloc(MAX_STR_LEN * MAX_BUF_SIZE, sizeof(char));
    char **buffer_start = &buffer;

    size_t buffer_len = read_file_to_buffer(fp, buffer);

    fclose(fp);

    buffer = *buffer_start;

    strings_count = read_buffer_to_array(array, buffer, buffer_len);

    char **array_old = (char**) calloc(strings_count, sizeof(char*));
    memcpy(array_old, array, strings_count * sizeof(char*));

    FILE *fp_out = fopen("output.txt", "w");

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void*, void*))compare_strings_increasingly);
    print_string_array_no_message_to_file(fp, array, strings_count);
    print_divisor_to_file(fp);

    merge_sort_strings(array, strings_count, MAX_STR_LEN * sizeof(char), (ssize_t (*)(void*, void*))compare_strings_from_end); // TODO: to qsort
    print_string_array_no_message_to_file(fp, array, strings_count);
    print_divisor_to_file(fp);

    /*
    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void*, void*))compare_strings_increasingly);
    print_string_array_with_message(array, strings_count, "Alphabetic order:");

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void*, void*))compare_strings_decreasingly);
    print_string_array_with_message(array, strings_count, "Reverse alphabetic order:");

    merge_sort_strings(array, strings_count, MAX_STR_LEN, (ssize_t (*)(void*, void*))compare_strings_by_length_increasingly);
    print_string_array_with_message(array, strings_count, "By length:");
    */
    print_string_array_no_message_to_file(fp, array_old, strings_count);

    fclose(fp_out);


    for (size_t i = 0; i < strings_count; ++i)
        free(array[i]);
    free(array);

    free(array_old);

    return 0;
}


char** merge_sort_strings(char **array, size_t arr_len, size_t max_str_len, ssize_t (*comparator_func)(void *a, void *b)) {

    if (arr_len <= 1)
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
    return (ssize_t) strlen(str1) - (ssize_t) strlen(str2);
}


void print_string_array_with_message(char **array, size_t arr_len, const char *msg_str) {
    print_string_array_with_message_to_file(stdout, array, arr_len, msg_str);
}


ssize_t compare_strings_strcmp(char *str1, char *str2) { // for testing custom comparator
    return (ssize_t) strcmp(str1, str2);
}


void print_string_array_with_message_to_file(FILE *fp, char **array, size_t arr_len, const char *msg_str) {
    fprintf(fp, "%s\n", msg_str);

    print_string_array_no_message_to_file(fp, array, arr_len);
}


void print_string_array_no_message_to_file(FILE *fp, char **array, size_t arr_len) {
    for (size_t i = 0; i < arr_len; ++i) {
        fprintf(fp, "[%s]\n", array[i]);
    }

    fprintf(fp, "\n");
}


void print_divisor_to_file(FILE *fp) {
    fprintf(fp, "\n==========================================\n\n");
}


ssize_t compare_strings_from_end(char *str1, char *str2) {
    ssize_t idx1 = 0, idx2 = 0;

    while (str1[idx1++] != '\0');
    while (str2[idx2++] != '\0');

    idx1 -= 2;
    idx2 -= 2;

    while (idx1 >= 0 && idx2 >= 0 && str1[idx1--] == str2[idx2--]);

    return (ssize_t) str1[idx1 + 1] - (ssize_t) str2[idx2 + 1];
}

size_t read_file_to_buffer(FILE *fp, char *buffer) {
    size_t n_read = 0;
    char **buffer_ptr = &buffer;

    while (!feof(fp)) {
        n_read += read_string_from_file_to_buffer(fp, buffer, buffer_ptr);
    }
    return n_read;
}


size_t read_string_from_file_to_buffer(FILE *fp, char *buffer, char **buffer_ptr) {
    char ch = 1;

    size_t idx1 = 0, idx2 = 0;

    while (isspace(ch)) {
        ch = (char) fgetc(fp);
        ++idx1;
    }

    while (!isspace(ch) && ch != '\0' && ch != EOF) {
        ch = (char) fgetc(fp);

        if (isalpha(ch)) {
            buffer[idx2] = (char) tolower(ch);
            ++idx2;
        }
        ++idx1;
    }

    buffer[idx2++] = '\0';



    *buffer_ptr += idx2;
    fp = (FILE*) ((char*)fp + idx1 + 1);
    return idx2;
}


size_t read_buffer_to_array(char **array, char *buffer, size_t buf_len) {
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