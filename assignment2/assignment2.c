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

void* parallel_quicksort(void* arg) {

    ThreadArgs* data = (ThreadArgs*)arg; //unpack struct
    int *arr = data->arr;
    int low = data->low;
    int high = data->high;

    if (low < high) {

        int pi = partition(arr, low, high);

        
         pthread_t thread;
            
        ThreadArgs* left_args = malloc(sizeof(ThreadArgs)); //arguments for smaller array
        left_args->arr = arr;
        left_args->low = low;
        left_args->high = pi - 1;

    
        pthread_create(&thread, NULL, parallel_quicksort, left_args); // start threading left


        ThreadArgs right_args = {arr, pi + 1, high}; // bigger array side args
        parallel_quicksort(&right_args); // parent process 

    
        pthread_join(thread, NULL); // join both threads
        free(left_args); // free memory we allocated
        
    }
    return NULL;
}

