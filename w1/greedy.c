#include <stdio.h>
#include <cs50.h>

int consumer(int);

int main(void) {
    int bag;

    do {
         float input = get_float("O hai! How much change is owed?: \n");
         bag = ((int) (input * 10000)) / 100;
    } while (bag < 1);

    int count = 0;

    while (bag != 0) {
        count++;
        bag = consumer(bag);
    }

    printf("%d\n", count);
}

int consumer(int v) {
        if (v >= 25) {
            return v -= 25;
        }  else if (v >= 10) {
            return v -= 10; 
        } else if (v >= 5) {
            return v -= 5; 
        } else if (v >= 1) {
            return v -= 1;
        } else {
            return 0;
        }
}
