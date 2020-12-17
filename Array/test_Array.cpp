/*
 * @Author: your name
 * @Date: 2020-12-15 01:07:24
 * @LastEditTime: 2020-12-15 19:09:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \code\cpp_code\Array\test_Array.cpp
 */
#include <iostream>
#include <array>
#include "Array.h"
using std::array;
using std::cin;
using std::cout;
using std::endl;
using namespace sx;

#define print_array(arr)        \
do                              \
{                               \
    for(auto x : arr)           \
        cout << x << " ";       \
    cout << endl;               \
} while (false);


int main()
{
    Array<int, 10> arr;
    // at() 访问写入
    for (int i = 0; i < arr.size(); ++i)
        arr.at(i) = i;
    // 打印输出
    print_array(arr);
    // 正向迭代器访问
    for (auto it = arr.begin(); it != arr.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // 反向迭代器访问
    for (auto it = arr.rbegin(); it != arr.rend(); ++it)
        cout << *it << " ";
    cout << endl;

    array<int, 10> arr0;
    arr0.fill(10);
    print_array(arr0);

    decltype(arr) arr1 = arr0;
    print_array(arr1);

    cin.get();
    return 0;
}
