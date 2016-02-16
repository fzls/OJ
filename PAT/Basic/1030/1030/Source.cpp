/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-16 19:59:49
* @Description:  1030. 完美数列(25)
时间限制
300 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CAO, Peng
给定一个正整数数列，和正整数p，设这个数列中的最大值是M，最小值是m，如果M <= m * p，则称这个数列是完美数列。

现在给定参数p和一些正整数，请你从中选择尽可能多的数构成一个完美数列。

输入格式：

输入第一行给出两个正整数N和p，其中N（<= 105）是输入的正整数的个数，p（<= 109）是给定的参数。第二行给出N个正整数，每个数不超过109。

输出格式：

在一行中输出最多可以选择多少个数可以用它们组成一个完美数列。

输入样例：
10 8
2 3 20 4 5 1 6 7 8 9
输出样例：
8
*
+----------------------------------------------------------
*/
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:66777216")

#include <algorithm>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;



int find_max_m_by_binary_search(int m, vector<unsigned long long> &numbers, unsigned long long p) {
    //find the M that the max item that is <= key
    unsigned long long key = numbers[m] * p;
    int middle, left, right;

    for (left = m, right = numbers.size() - 1; left < right;) {
        middle = (left + right) / 2;

        if(numbers[middle] > key) {
            right = middle - 1;
        } else {
            left = middle;

            if(left == right - 1) {
                if (numbers[right] <= key) {
                    left = right;
                } else {
                    right = left;
                }
            }
        }
    }

    return left;
}

int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    unsigned long long n, p;
    cin >> n >> p;
    auto numbers = vector<unsigned long long>(n);

    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    sort(numbers.begin(),  numbers.end());
    int max = 0;

    for (int i = 0; i < n; ++i) {
        //use binay serach in enhance the effciency to NlogN,rather than n^2
        int j = find_max_m_by_binary_search(i, numbers, p);
        max = std::max(j - i + 1, max);
    }

    cout << max;
    return 0;
}
