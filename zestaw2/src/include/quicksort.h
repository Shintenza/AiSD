#include <iterator>

template <typename Iterator>
void quickSort( Iterator begin, Iterator end ) {
    Iterator pivot = end - 1;
    Iterator leftPointer = begin;
    Iterator rightPointer = end - 1;

    if (begin >= end)
        return;
    while (leftPointer < rightPointer) {
        while (*leftPointer <= *pivot && leftPointer < rightPointer) {
            leftPointer++;
        } 
        while (*rightPointer >= *pivot && leftPointer < rightPointer) {
            rightPointer--;
        }
        std::iter_swap(begin + std::distance(begin, leftPointer), begin + std::distance(begin, rightPointer));
    }
    std::iter_swap(begin+std::distance(begin, leftPointer), begin + std::distance(begin,pivot));

    quickSort(begin, leftPointer);
    quickSort(leftPointer + 1, end);
}
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
