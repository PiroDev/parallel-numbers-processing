#include "hardware_info.h"

#include <sys/sysinfo.h>

int get_max_threads_count(void) { return get_nprocs(); }

#if defined(__APPLE__)

#include <sys/sysctl.h>
size_t get_L1_cache_size(void) {
    size_t cache_size = 0;
    size_t size_of_cache_size = sizeof(cache_size);
    sysctlbyname("hw.l1dcachesize", &cache_size, &size_of_cache_size, 0, 0);
    return cache_size;
}

#elif defined(_WIN32)

#include <stdlib.h>
#include <windows.h>

size_t get_L1_cache_size(void) {
    size_t cache_size = 0;
    DWORD buffer_size = 0;
    DWORD i = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer = 0;

    GetLogicalProcessorInformation(0, &buffer_size);
    buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
        if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
            cache_size = buffer[i].Cache.Size;
            break;
        }
    }

    free(buffer);
    return cache_size;
}

#elif defined(__linux__)

#include <unistd.h>

size_t get_L1_cache_size(void) { return sysconf(_SC_LEVEL1_DCACHE_SIZE); }

#else
#error Unknown system
#endif