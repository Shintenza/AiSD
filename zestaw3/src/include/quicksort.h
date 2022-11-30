#include <iterator>

#ifndef QUICKSORT_H 
#define QUICKSORT_H 
template <typename T>
void quickSort (T* arr, int left, int right) {
    if (left >= right) 
        return;

    T pivot = arr[right];
    int leftPointer = left;
    int rightPointer = right;


    while (leftPointer < rightPointer) {
        while(arr[leftPointer] <= pivot && leftPointer < rightPointer)
            leftPointer++;
        while(arr[rightPointer] >= pivot && leftPointer < rightPointer)
            rightPointer--;

        T temp = arr[leftPointer];
        arr[leftPointer] = arr[rightPointer];
        arr[rightPointer] = temp;
    }
    T temp = arr[leftPointer];
    arr[leftPointer] = arr[right];
    arr[right] = temp;

    quickSort(arr, left, leftPointer - 1);
    quickSort(arr, leftPointer + 1, right);
}
#endif
