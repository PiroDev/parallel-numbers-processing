#include <dlfcn.h>
#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
#include "numbers_processing.h"
}

unsigned int rand_seed = 123456;

TEST(compare_serial_and_parallel_results_get_negative_numbers_count, 1mb) {
    void *library_ptr = dlopen("libparallel.so", RTLD_LAZY);
    ASSERT_FALSE(library_ptr == NULL);
    int (*parallel_get_filter_matched_numbers_count)(int *, int, int (*)(int));
    parallel_get_filter_matched_numbers_count =
        (int (*)(int *, int, int (*)(int)))dlsym(library_ptr, "get_filter_matched_numbers_count");

    int array_size = 262144;
    int *array = (int *)calloc(array_size, sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = rand_r(&rand_seed) - RAND_MAX / 2;
    }

    int serial_result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);
    int parallel_result =
        parallel_get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    dlclose(library_ptr);
    ASSERT_EQ(serial_result, parallel_result);
}

TEST(compare_serial_and_parallel_results_get_negative_numbers_count, 10mb) {
    void *library_ptr = dlopen("libparallel.so", RTLD_LAZY);

    int (*parallel_get_filter_matched_numbers_count)(int *, int, int (*)(int));
    parallel_get_filter_matched_numbers_count =
        (int (*)(int *, int, int (*)(int)))dlsym(library_ptr, "get_filter_matched_numbers_count");

    int array_size = 2621440;
    int *array = (int *)calloc(array_size, sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = rand_r(&rand_seed) - RAND_MAX / 2;
    }

    int serial_result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);
    int parallel_result =
        parallel_get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    dlclose(library_ptr);
    ASSERT_EQ(serial_result, parallel_result);
}

TEST(compare_serial_and_parallel_results_get_negative_numbers_count, 100mb) {
    void *library_ptr = dlopen("libparallel.so", RTLD_LAZY);

    int (*parallel_get_filter_matched_numbers_count)(int *, int, int (*)(int));
    parallel_get_filter_matched_numbers_count =
        (int (*)(int *, int, int (*)(int)))dlsym(library_ptr, "get_filter_matched_numbers_count");

    int array_size = 26214400;
    int *array = (int *)calloc(array_size, sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = rand_r(&rand_seed) - RAND_MAX / 2;
    }

    int serial_result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);
    int parallel_result =
        parallel_get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    dlclose(library_ptr);
    ASSERT_EQ(serial_result, parallel_result);
}

TEST(compare_serial_and_parallel_results_get_negative_numbers_count, 1gb) {
    void *library_ptr = dlopen("libparallel.so", RTLD_LAZY);

    int (*parallel_get_filter_matched_numbers_count)(int *, int, int (*)(int));
    parallel_get_filter_matched_numbers_count =
        (int (*)(int *, int, int (*)(int)))dlsym(library_ptr, "get_filter_matched_numbers_count");

    int array_size = 268435456;
    int *array = (int *)calloc(array_size, sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = rand_r(&rand_seed) - RAND_MAX / 2;
    }

    int serial_result = get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);
    int parallel_result =
        parallel_get_filter_matched_numbers_count(array, array_size, predicate_number_is_negative);

    dlclose(library_ptr);
    ASSERT_EQ(serial_result, parallel_result);
}
