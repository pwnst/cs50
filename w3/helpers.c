/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
#include <cs50.h>

#include "helpers.h"

bool b_search(int, int[], int, int);

/**
 * Returns true if value is in valuesrray of n values, else false.
 */
bool search(int value, int values[], int n) {
    return b_search(value, values, 0, n);
}

bool b_search(int value, int values[], int min, int max) {
    if (min == max) {
        return false;  
    }

    int mid = ((max - min) / 2) + min;

    if (values[mid] < value) {
        return b_search(value, values, mid + 1, max);
    } else if (values[mid] > value) {
        return b_search(value, values, min, mid);
    } else {
        return true;
    }
}

/**
 * Sorts valuesrray of n values.
 */
void sort(int values[], int n) {
    for (int i = 1; i < n; i++) {
        int idx = i; 
        int swapped = 1;
        while (swapped) {
            swapped = 0;
            if (idx > 0 && values[idx] < values[idx - 1]) {
                int tmp = values[idx];
                values[idx] = values[idx - 1];
                values[idx - 1] = tmp;
                swapped = 1;    
                idx--;
            }
        }
    }
    return;
}

