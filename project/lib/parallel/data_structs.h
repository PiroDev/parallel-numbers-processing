#ifndef PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_
#define PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_

#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    int value;
} shared_data_t;

typedef struct {
    int *array_left_border;
    int *array_right_border;
    int (*is_match)(int number);
} thread_routine_data_t;

#endif  // PROJECT_LIB_PARALLEL_DATA_STRUCTS_H_