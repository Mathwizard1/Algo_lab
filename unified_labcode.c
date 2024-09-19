#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct testcase
{
    int n;
    int* num_arr;
}testcase;

void display_arr(int arr[], int n)
{
    printf("\n(");
    for(int i = 0; i < n; i++)
    {
        printf(" %d,", arr[i]);
    }
    printf(")\n");
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int b, int e)
{
    int left, right, pivot;
    left = b + 1;
    right = e;

    pivot = arr[b];
    while (left <= right)
    {
        while (arr[left] < pivot)
        {
            left++;
        }
        while (pivot < arr[right])
        {
            right--;
        }
        
        if(left < right)
        {
            swap(&arr[left], &arr[right]);
        }
    }
    swap(&arr[b], &arr[right]);
    return right;
}

void quicksort(int arr[], int b, int e)
{
    if(b < e)
    {
        int partion_index = partition(arr, b, e);
        quicksort(arr, b, partion_index - 1);
        quicksort(arr, partion_index + 1, e);
    }
}

void process_testcases(testcase testcases[], int numcases)
{
    for(int n = 0; n < numcases; n++)
    {
        testcase currentcase = testcases[n];
        display_arr(currentcase.num_arr, currentcase.n);
        //insertionSort(currentcase.num_arr, currentcase.n);
        quicksort(currentcase.num_arr, 0, currentcase.n - 1);
        display_arr(currentcase.num_arr, currentcase.n);

        free(currentcase.num_arr);
    }
}

int main()
{
    int numcases;
    printf("Enter the number of testcases: ");
    scanf("%d", &numcases);

    testcase* testcases = (testcase *)malloc(sizeof(testcase) * numcases);
    for(int n1 = 0; n1 < numcases; n1++)
    {
        int inputval;
        printf("Enter the value of n%d: ",(n1+1));
        scanf("%d", &inputval);
        
        {
        testcases[n1].n = inputval;
        testcases[n1].num_arr = (int *)malloc(sizeof(int) * inputval);
        }

        for(int n2 = 0; n2 < inputval; n2++)
        {
            int input_arr;
            printf("Enter the elements: ");
            scanf("%d", &input_arr);
            testcases[n1].num_arr[n2] = input_arr;
        }
    }

    process_testcases(testcases, numcases);

    free(testcases);
    return 0;
}