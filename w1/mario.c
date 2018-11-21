#include <stdio.h>
#include <cs50.h>

int main(void) {
    int h;

    do {
        h = get_int("Height: ");
    } while (h > 23 || h < 1);

    for (int i = 0; i < h; i++) {
        for (int j = h + 1; j > 0; j--) {
            if (j - i > 2) {
                printf(" ");
            } else {
                printf("%c", '#');
            }
        }
        printf("\n");
    }
}	
