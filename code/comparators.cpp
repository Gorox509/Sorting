#include "../headers/definitions.hpp"
#include "../headers/comparators.hpp"


int comparator_strings_increase(const void *const str1_vp, const void *const str2_vp) { //TODO: это тоже можно 1 функцией сделать - done

    assert(str1_vp != NULL);
    assert(str2_vp != NULL);

    const char *const str1 = *((const char *const *) str1_vp);
    const char *const str2 = *((const char *const *) str2_vp);

    size_t idx1 = 0, idx2 = 0;

    return compare_strings_for_onegin(str1, str2, (ssize_t) idx1, (ssize_t) idx2, increment);
}


int comparator_strings_decrease(const void *const str1_vp, const void *const str2_vp) {

    assert(str1_vp != NULL);
    assert(str2_vp != NULL);

    return -1 * comparator_strings_increase(str1_vp, str2_vp);
}


int comparator_strings_rhythm(const void *const str1_vp, const void *const str2_vp) {

    assert(str1_vp != NULL);
    assert(str2_vp != NULL);

    const char *const str1 = *((char *const *) str1_vp);
    const char *const str2 = *((char *const *) str2_vp);

    ssize_t idx1 = 0, idx2 = 0;

    while (str1[idx1] != '\n' && str1[idx1] != '\0') ++idx1;
    while (str2[idx2] != '\n' && str2[idx2] != '\0') ++idx2;

    --idx1;
    --idx2;

    return compare_strings_for_onegin(str1, str2, idx1, idx2, decrement);
}


int compare_strings_for_onegin(const char *const str1, const char *const str2, ssize_t idx1, ssize_t idx2, ssize_t (*const applied_func)(ssize_t)) {

    assert(str1 != NULL);
    assert(str2 != NULL);
    assert(applied_func != NULL);

    while (str1[idx1] != '\n' && str2[idx2] != '\n'
        && str1[idx1] != '\0' && str2[idx2] != '\0'
        && idx1 >= 0 && idx2 >= 0)
    {
        if (compare_letters_or_skip_character(str1[idx1], str2[idx2], &idx1, &idx2, applied_func) == 1)
            break;
    }
    return tolower(str1[idx1]) - tolower(str2[idx2]);
}


int compare_letters_or_skip_character(const char ch1, const char ch2, ssize_t *const idx1, ssize_t *const idx2, ssize_t (*const applied_func)(ssize_t)) {
    bool wrong_symbol_1 = 0;
    bool wrong_symbol_2 = 0;

    if (!isalpha(ch1))
        wrong_symbol_1 = 1;
    if (!isalpha(ch2))
        wrong_symbol_2 = 1;

    if (wrong_symbol_1)
        *idx1 = (*applied_func)(*idx1);
    if (wrong_symbol_2)
        *idx2 = (*applied_func)(*idx2);
    if (wrong_symbol_1 || wrong_symbol_2)
        return 0;

    if (tolower(ch1) != tolower(ch2))
        return 1;

    *idx1 = (*applied_func)(*idx1);
    *idx2 = (*applied_func)(*idx2);

    return 0;
}
