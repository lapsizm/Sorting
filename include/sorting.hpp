#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

template<typename T>
void InsertSort(std::vector<T> &vec) {
    for (size_t i = 1; i < vec.size(); ++i){
        size_t j = i;
        while(j > 0 && vec[j - 1] > vec[j]){
            std::swap(vec[j - 1], vec[j]);
            --j;
        }
    }
}

template<typename T>
void BubbleSort(std::vector<T> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

template<typename It>
void MergeSort(It first, It last) {
    if (last - first < 2) {
        return;
    }
    if (last - first == 2) {
        if (*first > *(first + 1)) {
            std::swap(*first, *(first + 1));
        }
        return;
    }

    MergeSort(first, first + (last - first) / 2);
    MergeSort( first + (last - first) / 2, last);
    std::vector<typename It::value_type> vec_new;
    It b1 = first;
    It e1 = first + (last - first) / 2;
    It b2 = e1;
    while (vec_new.size() < last - first) {
        if (b1 - e1 >= 0 || (last - b2 > 0 && *b2 < *b1)) {
            vec_new.push_back(*b2);
            ++b2;
        } else {
            vec_new.push_back(*b1);
            ++b1;
        }
    }
    for (auto i = first, j = 0; i != last; ++i, ++j) {
        *i = vec_new[j];
    }
}


template<typename It>
void QuickSort(It first, It last) {
    if (last - first > 1) {
        auto pivot = last - 1;
        auto i = first;
        for (auto j = first; j != pivot; ++j) {
            // bool format
            if (*pivot > *j) {
                std::swap(*i++, *j);
            }
        }
        std::swap(*i, *pivot);
        It bound = i;
        QuickSort(first, bound);
        QuickSort(bound + 1, last);
    }
}

template<typename T>
class Timer {
public:
    Timer(const std::string &name, std::ostream &stream) : name_(name), stream_(stream) {}
    Timer(const std::string &name) : name_(name) {}
    void Start(std::vector<T>& vec){
        std::chrono::time_point<std::chrono::high_resolution_clock> t;
        if (name_ == "InsertSort") {
            time_ = std::chrono::high_resolution_clock::now();
            InsertSort(vec);
            t = std::chrono::high_resolution_clock::now();

        }
        if (name_ == "BubbleSort") {
            time_ = std::chrono::high_resolution_clock::now();
            BubbleSort(vec);
            t = std::chrono::high_resolution_clock::now();
        }
        if (name_ == "MergeSort") {
            time_ = std::chrono::high_resolution_clock::now();
            MergeSort(vec.begin(), vec.end());
            t = std::chrono::high_resolution_clock::now();
        }
        if (name_ == "QuickSort") {
            time_ = std::chrono::high_resolution_clock::now();
            QuickSort(vec.begin(), vec.end());
            t = std::chrono::high_resolution_clock::now();
        }
        if(name_ == "std_sort"){
            time_ = std::chrono::high_resolution_clock::now();
            std::sort(vec.begin(), vec.end());
            t = std::chrono::high_resolution_clock::now();
        }
        if (vec.size() < 10000) {
            stream_ << "size: " << vec.size() << ", time: "
                    << std::chrono::duration_cast<std::chrono::nanoseconds>(t - time_).count() << " ns" << std::endl;
        }
        else{
            stream_ << "size: " << vec.size() << ", time: "
                    << std::chrono::duration_cast<std::chrono::milliseconds>(t - time_).count() << " ms" << std::endl;
        }
    }


    ~Timer() = default;

private:
    std::string name_;
    std::chrono::high_resolution_clock::time_point time_;
    std::ostream &stream_ = std::cout;
};
