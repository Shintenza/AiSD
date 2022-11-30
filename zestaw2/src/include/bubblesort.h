#include <iterator>

template <typename Iterator>
void bubbleSort(Iterator begin, Iterator end) {
    int distance = std::distance(begin, end);
    for (int i = 0; i < distance - 1; i++) {
        for (int j = 0; j < distance - i - 1; j++)  {
            if (*(begin+j)>*(begin+j+1))
                std::iter_swap(begin+j, begin+j+1);
        }

    }
}

template <typename T>
void bubbleSort(T *nums, int left, int right) {
    for (int i = left; i < right; i ++) {
        for (int j = left; j < right - i; j++) {
            if (nums[j] > nums[j+1]) {
                int temp = nums[j+1];
                nums[j+1] = nums[j];
                nums[j] = temp;
            }
        }
    }
}
