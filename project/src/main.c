#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "numbers_processing.h"

#define ARRAY_SIZE 1000000

int x_is_less_than_157(int x) { return x < 157; }

/* пример работы программы на массиве из 1000000 чисел (x < 157) */
int main(void) {
    int *array = calloc(ARRAY_SIZE, sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    int res = get_filter_matched_numbers_count(array, ARRAY_SIZE, x_is_less_than_157);
    printf("Serial lib result: %d\n", res);

    void *library_ptr = dlopen("libparallel.so", RTLD_LAZY);
    if (library_ptr) {
        int (*parallel_get_filter_matched_numbers_count)(int *, int, int (*)(int)) =
            (int (*)(int *, int, int (*)(int)))dlsym(library_ptr, "get_filter_matched_numbers_count");

        res = parallel_get_filter_matched_numbers_count(array, ARRAY_SIZE, x_is_less_than_157);
        printf("Parallel lib result: %d\n", res);

        dlclose(library_ptr);
    } else {
        printf("Can't open libparallel.so\n");
    }
    free(array);

    return 0;
}
