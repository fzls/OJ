/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-14 22:46:19
* @Description:  1013. 数素数 (20)
时间限制
100 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
令Pi表示第i个素数。现任给两个正整数M <= N <= 104，请输出PM到PN的所有素数。

输入格式：

输入在一行中给出M和N，其间以空格分隔。

输出格式：

输出从PM到PN的所有素数，每10个数字占1行，其间以空格分隔，但行末不得有多余空格。

输入样例：
5 27
输出样例：
11 13 17 19 23 29 31 37 41 43
47 53 59 61 67 71 73 79 83 89
97 101 103
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

using namespace std;


#pragma warning(disable:4996)
bool is_prime(int n) {
    //case 2
    if (n == 2) {
        return true;
    }

    //case even but not 2
    if (n % 2 == 0) {
        return false;
    }

    //odd that is larger than 1
    int sqrt_n = (int)sqrt(n);

    for (int i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
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
    int lower, upper;
    cin >> lower >> upper;
    int i, cnt;
    bool isFirstItem = true;

    //find the lower th prime
    for ( i = 2, cnt = 0; cnt != upper; ++i) {
        if (is_prime(i)) {
            ++cnt;

            if (cnt >= lower) {
                if (!isFirstItem) {
                    cout << " ";
                } else {
                    isFirstItem = false;
                }

                cout << i;

                if (cnt - lower + 1 % 10 == 0) {
                    isFirstItem = true;
                    cout << endl;
                }
            }
        }
    }

    return 0;
}
