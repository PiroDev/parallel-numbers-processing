#include "numbers_processing.h"

int get_filter_matched_numbers_count(int *array, int array_size, int (*is_match)(int number)) {
    return count_numbers_matched(array, array_size, is_match);
}