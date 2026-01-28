#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>


void swap (int* a, int* b){

    int temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct {
    int *arr;
    int low;
    int high;
} ThreadArgs;


int partition(int *arr, int low, int high) {
    int pivot = arr[high]; // Pivot is the last element
    int i = low - 1;       // i tracks the boundary of the smaller zone

    for (int j = low; j < high; j++) {// If element is smaller than pivot then i is incremented and then two values are swapped
        if (arr[j] < pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move the pivot to the correct spot (right after the smaller zone)
    swap(&arr[i + 1], &arr[high]);
    
    // Return the index where the pivot now sits
    return (i + 1);
}
