#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
#include "numbers_processing.h"
}

TEST(get_negative_numbers_count, all_negative_numbers) {
    int array_size = 5;
    int array[] = { -1, -2, -3, -4, -5 };
    int expected_result = 5;

    int result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    ASSERT_EQ(result, expected_result);
}

TEST(get_negative_numbers_count, all_positive_numbers) {
    int array_size = 5;
    int array[] = { 1, 2, 3, 4, 5 };
    int expected_result = 0;

    int result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    ASSERT_EQ(result, expected_result);
}

TEST(get_negative_numbers_count, positive_and_negative_numbers) {
    int array_size = 5;
    int array[] = { -1, 2, -3, 4, -5 };
    int expected_result = 3;

    int result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    ASSERT_EQ(result, expected_result);
}

TEST(get_negative_numbers_count, contains_zero) {
    int array_size = 5;
    int array[] = { -1, 0, -3, 4, -5 };
    int expected_result = 3;

    int result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    ASSERT_EQ(result, expected_result);
}
