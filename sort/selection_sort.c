#include <stdio.h>

int main(void) {
    int a[] = {1, 5, 3, 12, 66, 4, -1, 12, 0, -2, 1, 59, 0, 2, -44, -17};
    int a_size = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < a_size; i++) {
        int min_index = i;
        for (int j = i; j < a_size; j++) {
            if (a[j] < a[min_index])
                min_index = j;
        }
        if (min_index != i) {
            int tmp = a[i];
            a[i] = a[min_index];
            a[min_index] = tmp;
        }
    }

    for (int i = 0; i < a_size; i++) {
        printf("%i ", a[i]); 
        if (i == a_size - 1)
            printf("\n");
    }
}

