#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#include "data_structs.h"
#include "hardware_info.h"
#include "numbers_processing.h"

void *thread_routine(void *args) {
    thread_routine_data_t *data = (thread_routine_data_t *)args;

    data->count_matched = count_numbers_matched(data->array, data->array_size, data->is_match);

    return (void *)data;
}

int get_filter_matched_numbers_count(int *array, int array_size, int (*is_match)(int number)) {
    if (!array || array_size <= 0) {
        return wrong_array_size;
    }

    int result = 0;

    int threads_count = get_max_threads_count();
    pthread_t *threads = (pthread_t *)calloc(threads_count, sizeof(pthread_t));
    if (!threads) {
        return out_of_memory;
    }

    size_t cache_size = get_L1_cache_size();
    /* сколько элементов массива одновременно вмещает кэш */
    size_t max_ints_count_in_cache = cache_size / sizeof(int);

    /* расчет разбиений массива для эффективной работы с кэшем процессора */
    int iters_count = array_size * sizeof(int) / cache_size;
    size_t remain_part_size = (array_size * sizeof(int)) % cache_size;
    if (remain_part_size != 0) {
        remain_part_size /= sizeof(int);
        iters_count++;
    }

    /* размер массива обрабатываемого одним потоком */
    size_t array_size_per_thread = max_ints_count_in_cache / threads_count;

    /* массив для хранения результата выполнения алгоритма для каждого потока */
    int *results = calloc(threads_count, sizeof(int));
    if (!results) {
        free(threads);
        return out_of_memory;
    }

    for (int iter = 0; iter < iters_count; iter++) {
        if (remain_part_size != 0 && iter == iters_count - 1) {
            array_size_per_thread = remain_part_size / threads_count;
        }
        for (int i = 0; i < threads_count; i++) {
            size_t shift = array_size_per_thread * i + max_ints_count_in_cache * iter;
            thread_routine_data_t *data = malloc(sizeof(thread_routine_data_t));
            if (!data) {
                free(threads);
                free(results);
                return out_of_memory;
            }
            data->is_match = is_match;
            data->array = array + shift;

            if (iter == iters_count - 1 && i == threads_count - 1 &&
                data->array + array_size_per_thread < array + array_size) {
                /* на последней итерации у последнего потока нужно скорректировать правую границу */
                data->array_size = array_size - shift;
            } else {
                data->array_size = array_size_per_thread;
            }

            int error_flag = pthread_create(threads + i, NULL, thread_routine, data);
            if (error_flag) {
                free(threads);
                free(results);
                free(data);
                for (int j = 0; j < i; j++) {
                    void *thread_data = NULL;
                    pthread_join(threads[i], &thread_data);
                    free(thread_data);
                }
                return thread_create_error;
            }
        }

        for (int i = 0; i < threads_count; i++) {
            void *data = NULL;
            pthread_join(threads[i], &data);
            results[i] += ((thread_routine_data_t *)data)->count_matched;
            free(data);
        }
    }
    free(threads);

    for (int i = 0; i < threads_count; i++) {
        result += results[i];
    }
    free(results);

    return result;
}
