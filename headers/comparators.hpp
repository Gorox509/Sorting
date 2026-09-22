#ifndef COMPARATORS_H

#define COMPARATORS_H

int comparator_strings_increase            (const void *str1_vp,  const void *str2_vp);
int comparator_strings_decrease            (const void *str1_vp,  const void *str2_vp);
int comparator_strings_rhythm              (const void *str1_vp,  const void *str2_vp);

int compare_strings_for_onegin             (const char *str1, const char *str2,
                                            ssize_t idx1, ssize_t idx2,
                                            ssize_t (*applied_func)(ssize_t));

#endif
