#ifndef PROJECT_INCLUDE_NUMBERS_PROCESSING_H_
#define PROJECT_INCLUDE_NUMBERS_PROCESSING_H_

int predicate_number_is_negative(int number);
int count_numbers_matched(int *array, int array_size, int (*is_match)(int number));
int get_filter_matched_numbers_count(int *array, int array_size, int (*is_match)(int number));

#endif  // PROJECT_INCLUDE_NUMBERS_PROCESSING_H_
