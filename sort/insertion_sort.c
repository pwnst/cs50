#include <stdio.h>

int main(void) {
    int a[] = {1, 5, 3, 12, 66, 4, -1, 12, 0, -2, 1, 59, 0, 2, -44, -17};
    int a_size = sizeof(a) / sizeof(a[0]);

    for (int i = 1; i < a_size; i++) {
        int idx = i - 1;
        if (a[idx] > a[i]) {
            int tmp = a[i];
            while (a[idx] > tmp && idx >= 0) {
                a[idx + 1] = a[idx];
                idx--;
            }
            a[idx + 1] = tmp;
        }
    }

    for (int i = 0; i < a_size; i++) {
        printf("%i ", a[i]); 
        if (i == a_size - 1)
            printf("\n");
    }
}

