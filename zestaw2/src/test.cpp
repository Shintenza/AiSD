#include <array>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#include "include/bubblesort.h"
#include "include/quicksort.h"

template <typename Iter>
void printArray(Iter start, Iter end) {
    while (start!=end) {
        std::cout<<*start<<" ";
        start++;
    }
    std::cout<<std::endl;
}

void test() {
    int nums[] = {10, 12, 1, 4, 7, 100, 2, 45, 69, 7, 3, 2, 5, 17};
    std::array<int,7> nums2 = {21, 37, 15, 1, 33, 17, 420};
    std::vector<float> nums3 = {12.5, -1.9, -4.5, 7.1, 8, 21, 0.61};
   
    std::cout<<"Przed sortowaniem:"<<std::endl;
    printArray(std::begin(nums), std::end(nums));
    printArray(nums2.begin(), nums2.end());
    printArray(nums3.begin(), nums3.end());

    // quickSort(std::begin(nums), std::end(nums));
    quickSort(nums2.begin(), nums2.end());
    quickSort(nums3.begin(), nums3.end());
    quickSort(nums, 0, sizeof nums / sizeof(int) - 1);

    // bubbleSort(std::begin(nums), std::end(nums));
    // bubbleSort(nums2.begin(), nums2.end());
    // bubbleSort(nums3.begin(), nums3.end());

    assert( std::is_sorted(std::begin(nums), std::end(nums)));   
    assert( std::is_sorted(nums2.begin(), nums2.end()));  
    assert( std::is_sorted(nums3.begin(), nums3.end()));   
   
    std::cout<<"Po sortowaniu:"<<std::endl;
    printArray(std::begin(nums), std::end(nums));
    printArray(nums2.begin(), nums2.end());
    printArray(nums3.begin(), nums3.end());
}
