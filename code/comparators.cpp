#include "../headers/definitions.h"
#include "../headers/comparators.h"

ssize_t compare_strings_increasingly(char *str1, char *str2) { //TODO: это тоже можно 1 функцией сделать -- не понял что требуется

    assert(str1 != NULL);
    assert(str2 != NULL);

    size_t idx = 0;

    while (str1[idx] == str2[idx] && str1[idx] != '\0' && str2[idx] != '\0')
        ++idx;

    return (ssize_t) str1[idx] - str2[idx];
}


ssize_t compare_strings_decreasingly(char *str1, char *str2) {

    assert(str1 != NULL);
    assert(str2 != NULL);

    size_t idx = 0;

    while (str1[idx] == str2[idx] && str1[idx] != '\0' && str2[idx] != '\0')
        ++idx;

    return (ssize_t) str2[idx] - str1[idx];
}


ssize_t compare_strings_by_length_increasingly(char *str1, char *str2) {

    assert(str1 != NULL);
    assert(str2 != NULL);

    return (ssize_t) strlen(str1) - (ssize_t) strlen(str2);
}


ssize_t compare_strings_strcmp(char *str1, char *str2) { // for testing custom comparatorg

    assert(str1 != NULL);
    assert(str2 != NULL);

    return (ssize_t) strcmp(str1, str2);
}


ssize_t compare_strings_from_end(char *str1, char *str2) {

    assert(str1 != NULL);
    assert(str2 != NULL);

    ssize_t idx1 = 0, idx2 = 0;

    while (str1[idx1++] != '\0');
    while (str2[idx2++] != '\0');

    idx1 -= 2;
    idx2 -= 2;

    while (idx1 >= 0 && idx2 >= 0 && str1[idx1--] == str2[idx2--]);

    return (ssize_t) str1[idx1 + 1] - (ssize_t) str2[idx2 + 1];
}
