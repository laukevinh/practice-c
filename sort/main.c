#include <stdio.h>
#include "sort.h"

int main(void)
{
    test_insertion_sort();
    test_merge_sort();
}

void print_arr(int arr[], int len)
{
    for (int i=0; i<len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void test_insertion_sort(void)
{
    int arr[9] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    int len = 9;
    printf("Insertion sort\n");
    printf("Before: ");
    print_arr(arr, len);
    printf("After : ");
    insertion_sort(arr, len);
    print_arr(arr, len);
}

void test_merge_sort(void)
{
    int arr[9] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    int len = 9;
    printf("Merge sort\n");
    printf("Before: ");
    print_arr(arr, len);
    printf("After : ");
    merge_sort(arr, 0, len);
    print_arr(arr, len);
}
