#include "sorting.hpp"



int main() {
    std::vector<int> vec{3, 2, 15, 16, 844, 52, 1, 0};
    QuickSort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
}