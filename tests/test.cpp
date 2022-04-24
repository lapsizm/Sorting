#include <gtest/gtest.h>
#include "sorting.hpp"
#include <random>
#include <list>

class SortTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto gen = [this]() {
            return number_distance(mercenne_engine);
        };
        arr_10.resize(10);
        arr_100.resize(100);
        arr_1000.resize(1000);
        arr_10000.resize(10000);
        arr_100000.resize(100000);
        arr_250000.resize(250000);
        std::generate(arr_10.begin(), arr_10.end(), gen);
        std::generate(arr_100.begin(), arr_100.end(), gen);
        std::generate(arr_1000.begin(), arr_1000.end(), gen);
        std::generate(arr_10000.begin(), arr_10000.end(), gen);
        std::generate(arr_100000.begin(), arr_100000.end(), gen);
        std::generate(arr_250000.begin(), arr_250000.end(), gen);
    }
    void TearDown() override {
        arr_10.clear();
        arr_100.clear();
        arr_1000.clear();
        arr_10000.clear();
        arr_100000.clear();
        arr_250000.clear();
    }
public:
    std::vector<int> arr_10;
    std::vector<int> arr_100;
    std::vector<int> arr_1000;
    std::vector<int> arr_10000;
    std::vector<int> arr_100000;
    std::vector<int> arr_250000;
    std::vector<void *> arrays{&arr_10, &arr_100, &arr_1000, &arr_10000, &arr_100000, &arr_250000};
// std::vector<std::array>
private:
    std::random_device rnd_device;
    std::mt19937 mercenne_engine{rnd_device()};
    std::uniform_int_distribution<int> number_distance{1, 1000000};
};

TEST_F(SortTest, SortingTime){
    std::string ins = "InsertSort";
    std::string bubb = "BubbleSort";
    std::string merg = "MergeSort";
    std::string quick = "QuickSort";
    std::string lib_sort = "std_sort";
    std::vector<std::string> str_vec{ins, bubb, merg,quick, lib_sort};
    std::ofstream fout("../sort.txt");

    for(int i = 0; i < str_vec.size(); ++i){
        fout << "time for " << str_vec[i] << ":" << std::endl;
        SortTest::SetUp();
        Timer<int> t(str_vec[i], fout);
        for(int j = 0; j < arrays.size(); ++j){
            std::vector<int> vec = *static_cast<std::vector<int>*>(arrays[j]);
            t.Start(*static_cast<std::vector<int>*>(arrays[j]));
            std::sort(vec.begin(), vec.end());
            ASSERT_EQ(vec, *static_cast<std::vector<int>*>(arrays[j]));
        }
        fout << std::endl;
    }
}


TEST(InsertSort, sorting){
    std::vector<int> vec{2,3,1,54,31,46};
    std::vector<int> vec2{1,2,3,31,46,54};
    InsertSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::vector<char> vec3{'c','4','a','2','1','3'};
    std::vector<char> vec4{'1','2','3','4','a','c'};
    InsertSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}

TEST(BubbleSort, sorting){
    std::vector<int> vec{2,3,1,54,31,46};
    std::vector<int> vec2{1,2,3,31,46,54};
    BubbleSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::vector<char> vec3{'c','4','a','2','1','3'};
    std::vector<char> vec4{'1','2','3','4','a','c'};
    BubbleSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}
TEST(MergeSort, sorting){
    std::vector<int> vec{2,3,1,54,31,46};
    std::vector<int> vec2{1,2,3,31,46,54};
    MergeSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::vector<char> vec3{'c','4','a','2','1','3'};
    std::vector<char> vec4{'1','2','3','4','a','c'};
    MergeSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}
TEST(QuickSort, sorting){
    std::vector<int> vec{2,3,1,54,31,46};
    std::vector<int> vec2{1,2,3,31,46,54};
    QuickSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::vector<char> vec3{'c','4','a','2','1','3'};
    std::vector<char> vec4{'1','2','3','4','a','c'};
    QuickSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}
<<<<<<< HEAD

TEST(TestsForLists, InsertSort){
    std::list<int> vec{2,3,1,54,31,46};
    std::list<int> vec2{1,2,3,31,46,54};
    InsertSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::list<char> vec3{'c','4','a','2','1','3'};
    std::list<char> vec4{'1','2','3','4','a','c'};
    InsertSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}

TEST(TestsForLists, BubbleSort){
    std::list<int> vec{2,3,1,54,31,46};
    std::list<int> vec2{1,2,3,31,46,54};
    BubbleSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::list<char> vec3{'c','4','a','2','1','3'};
    std::list<char> vec4{'1','2','3','4','a','c'};
    BubbleSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}
TEST(TestsForLists, MergeSort){
    std::list<int> vec{2,3,1,54,31,46};
    std::list<int> vec2{1,2,3,31,46,54};
    MergeSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::list<char> vec3{'c','4','a','2','1','3'};
    std::list<char> vec4{'1','2','3','4','a','c'};
    MergeSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}
TEST(TestsForLists, QuickSort){
    std::list<int> vec{2,3,1,54,31,46};
    std::list<int> vec2{1,2,3,31,46,54};
    QuickSort(vec.begin(), vec.end());
    ASSERT_EQ(vec,vec2);

    std::list<char> vec3{'c','4','a','2','1','3'};
    std::list<char> vec4{'1','2','3','4','a','c'};
    QuickSort(vec3.begin(), vec3.end());
    ASSERT_EQ(vec3,vec4);
}

