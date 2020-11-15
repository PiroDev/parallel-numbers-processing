#ifndef PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_
#define PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_

#include <pthread.h>

typedef struct {
    int *array;
    int array_size;
    int (*is_match)(int number);
    int count_matched;
} thread_routine_data_t;

#endif  // PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_