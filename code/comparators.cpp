#include "../headers/definitions.h"
#include "../headers/comparators.h"

ssize_t compare_strings_increasingly(char *str1, char *str2) { //TODO: это тоже можно 1 функцией сделать - done

    assert(str1 != NULL);
    assert(str2 != NULL);

    size_t idx1 = 0, idx2 = 0;

    while (str1[idx1] != '\0' && str2[idx2] != '\0' && str1[idx1] != '\n' && str2[idx2] != '\n') {
        bool wrong_symbol_1 = 0;
        bool wrong_symbol_2 = 0;

        if (!isalpha(str1[idx1]) && str1[idx1] != ' ')
            wrong_symbol_1 = 1;
        if (!isalpha(str2[idx2]) && str2[idx2] != ' ')
            wrong_symbol_2 = 1;

        if (wrong_symbol_1)
            ++idx1;
        if (wrong_symbol_2)
            ++idx2;
        if (wrong_symbol_1 || wrong_symbol_2)
            continue;

        if (str1[idx1] != str2[idx2])
            break;

        ++idx1;
        ++idx2;
    }
    return (ssize_t) str1[idx1] - str2[idx2];
}


ssize_t compare_strings_decreasingly(char *str1, char *str2) {

    assert(str1 != NULL);
    assert(str2 != NULL);

    return -1 * compare_strings_increasingly(str1, str2);
}


ssize_t compare_strings_from_end(char *str1, char *str2) {

    assert(str1 != NULL);
    assert(str2 != NULL);

    ssize_t idx1 = 0, idx2 = 0;

    while (str1[idx1] != '\n' && str1[idx1] != '\0') ++idx1;
    while (str2[idx2] != '\n' && str2[idx2] != '\0') ++idx2;

    --idx1;
    --idx2;

    while (str1[idx1] != '\n' && str2[idx2] != '\n'
        && str1[idx1] != '\0' && str2[idx2] != '\0'
        && idx1 >= 0 && idx2 >= 0)
    {

        bool wrong_symbol_1 = 0;
        bool wrong_symbol_2 = 0;

        if (!isalpha(str1[idx1]) && str1[idx1])
            wrong_symbol_1 = 1;
        if (!isalpha(str2[idx2]) && str2[idx2])
            wrong_symbol_2 = 1;

        if (wrong_symbol_1)
            --idx1;
        if (wrong_symbol_2)
            --idx2;
        if (wrong_symbol_1 || wrong_symbol_2)
            continue;

        if (str1[idx1--] != str2[idx2--])
            break;
    }

    return (ssize_t) str1[idx1 + 1] - (ssize_t) str2[idx2 + 1];
}
