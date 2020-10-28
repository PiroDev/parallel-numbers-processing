#include <stdlib.h>
#include <stdio.h>

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
    printf("%d\n", res);

    free(array);

    return 0;
}
