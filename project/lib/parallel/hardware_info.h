#ifndef PROJECT_LIB_PARALLEL_HARDWARE_INFO_H_
#define PROJECT_LIB_PARALLEL_HARDWARE_INFO_H_

#include <stddef.h>

int get_max_threads_count(void);
size_t get_L1_cache_size(void);

#endif  // PROJECT_LIB_PARALLEL_HARDWARE_INFO_H_