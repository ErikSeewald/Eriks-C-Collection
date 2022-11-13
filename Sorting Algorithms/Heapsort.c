#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(int arr[], int length, int i)
{
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < length && arr[left] > arr[largest])
    {largest = left;}

    if (right < length && arr[right] > arr[largest])
    {largest = right;}

    // if we need to swap since i is not the largest, heapify one row below (index largest)
    // to make sure the value at index i we just swapped in complies with max heap rules
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, length, largest);
    }
}

void heapSort(int arr[], int length)
{
    // Build max heap
    //length / 2 -1 points to the rightmost node in the second lowest row in a binary tree
    for (int i = length / 2 - 1; i >= 0; i--)
    {heapify(arr, length, i);}

    // Heap sort
    for (int i = length - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);

        // Heapify root element to get highest element at root again, numbers we already sorted
        // to the back are not affected as we only give in the length equal to current i
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int length)
{
    for (int i = 0; i < length; ++i)
    {printf("%d, ", arr[i]);}
}

int main()
{
    int arr[] = {1, 2, 31, 94, 17, 120, 141, 5, 44, 10};
    int length = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, length);

    printf("Sorted array is \n");
    printArray(arr, length);
}