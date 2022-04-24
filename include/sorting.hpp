#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

template<typename It>
void InsertSort(It first, It last) {
    for (auto i = first; i != last; ++i) {
        auto j = i;
        ++j;
        if (j != last) {
            while (j != first && *(std::prev(j)) > *(j)) {
                std::swap(*std::prev(j), *(j));
                --j;
            }
        }
    }
}

template<typename It>
void BubbleSort(It first, It last) {
    for (auto i = first; i != last; ++i) {
        for (auto j = first; j != last; ++j) {
            auto temp_end = last;
            --temp_end;
            if (j != temp_end) {
                auto temp = j;
                ++temp;
                if (*j > *(temp)) {
                    std::swap(*(j), *(temp));
                }
            }
        }
    }
}

template<typename It>
void MergeSort(It first, It last) {
    if (std::distance(first, last) < 2) {
        return;
    }
    if (std::distance(first, last) == 2) {
        if (*first > *(std::next(first))) {
            std::swap(*first, *(std::next(first)));
        }
        return;
    }

    It temp_it = first;
    std::advance(temp_it, std::distance(first, last) / 2);
    MergeSort(first, temp_it);
    MergeSort(temp_it, last);
    std::vector<typename It::value_type> vec_new;
    It b1 = first;
    It e1 = first;
    std::advance(e1, (std::distance(first, last)) / 2);
    It b2 = e1;
    while (vec_new.size() < std::distance(first, last)) {
        if (b1 == e1 || std::distance(b2, last) > 0 && *b2 < *b1) {
            vec_new.push_back(*b2);
            ++b2;
        } else {
            vec_new.push_back(*b1);
            ++b1;
        }
    }
    int count = 0;
    for (It i = first;  i != last; ++i, ++count) {
        *i = vec_new[count];
    }
}


template<typename It>
void QuickSort(It first, It last) {
    if (std::distance(first, last) > 1) {
        auto pivot = std::prev(last);
        auto i = first;
        for (auto j = first; j != pivot; ++j) {
            if (*pivot > *j) {
                std::swap(*i, *j);
                ++i;
            }
        }
        std::swap(*i, *pivot);
        It bound = i;
        QuickSort(first, bound);
        QuickSort(std::next(bound), last);
    }
}

template<typename T>
class Timer {
public:
    Timer(const std::string &name, std::ostream &stream) : name_(name), stream_(stream) {}

    Timer(const std::string &name) : name_(name) {}

    void Start(std::vector<T> &vec) {
        std::chrono::time_point<std::chrono::high_resolution_clock> t;
        if (name_ == "InsertSort") {
            time_ = std::chrono::high_resolution_clock::now();
            InsertSort(vec.begin(), vec.end());
            t = std::chrono::high_resolution_clock::now();

        }
        if (name_ == "BubbleSort") {
            time_ = std::chrono::high_resolution_clock::now();
            BubbleSort(vec.begin(), vec.end());
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
        } else {
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
