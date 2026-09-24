#ifndef COMPARATORS_H

#define COMPARATORS_H

int comparator_strings_increase            (const void *str1_vp,  const void *str2_vp);
int comparator_strings_decrease            (const void *str1_vp,  const void *str2_vp);
int comparator_strings_rhythm              (const void *str1_vp,  const void *str2_vp);

int compare_strings_for_onegin             (const char *str1, const char *str2,
                                            long idx1, long idx2,
                                            long (*const applied_func)(long));

int compare_letters_or_skip_character(const char ch1, const char ch2,
                                      long *idx1, long *idx2,
                                      long (*const applied_func)(long));

#endif
