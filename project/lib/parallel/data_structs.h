#ifndef PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_
#define PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_

#include <pthread.h>

typedef struct {
    int *array;
    int array_size;
    int (*is_match)(int number);
    int count_matched;
} thread_routine_data_t;

typedef enum {
    wrong_array_size = -1,
    out_of_memory = -2,
    thread_create_error = -3
} error_code;

#endif  // PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_