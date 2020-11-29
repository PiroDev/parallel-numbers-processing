#include "numbers_processing.h"

int predicate_number_is_negative(int number) { return number < 0; }

int count_numbers_matched(int *array, int array_size, int (*is_match)(int number)) {
    int count_matched = 0;
    for (int i = 0; i < array_size; i++) {
        if (is_match(array[i])) {
            count_matched++;
        }
    }
    return count_matched;
}