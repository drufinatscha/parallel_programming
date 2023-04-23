#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<string.h>

void merge(int *a, int length, int *temp){
    // i = start of left array, j = start of right array
    int i = 0;
    int j = length / 2;
    int temp_index = 0;

    // check if element from left array is smaller than element from right array
    while(i < length / 2 && j < length){
        if(a[i] < a[j]){
            temp[temp_index] = a[i];
            i++;
        }
        else{
            temp[temp_index] = a[j];
            j++;
        }
        temp_index++;
    }

    // copy remaining elements
    while(i < length / 2){
        temp[temp_index] = a[i];
        i++;
        temp_index++;
    }
    while(j < length){
        temp[temp_index] = a[j];
        j++;
        temp_index++;
    }

    // copy elements from temp array to original array
    memcpy(a, temp, length * sizeof(int));

}

void merge_sort(int *a, int length, int *temp){
    if(length == 1){
        return;
    }
        merge_sort(a, length / 2, temp);
        merge_sort(a + length / 2, length - length / 2, temp + length / 2);
        merge(a, length, temp);
}


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    int length = atoi(argv[1]);

    int *a = (int *)malloc(length * sizeof(int));
    int *temp = (int *)malloc(length * sizeof(int));

    for(int i = 0; i < length; i++){
        a[i] = rand() % 100;
    }

    double start_time = omp_get_wtime();
    merge_sort(a, length, temp);
    double end_time = omp_get_wtime();
    printf("Time: %f\n", end_time - start_time);

    free(a);
    free(temp);

    return EXIT_SUCCESS;

}