/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-13 21:14:49
* @Description:  1007. 素数对猜想 (20)



时间限制

400 ms



内存限制

65536 kB



代码长度限制

8000 B



判题程序

Standard

作者

CHEN, Yue



让我们定义 dn 为：dn = pn+1 - pn，其中 pi 是第i个素数。显然有 d1=1 且对于n>1有 dn 是偶数。“素数对猜想”认为“存在无穷多对相邻且差为2的素数”。

现给定任意正整数N (< 105)，请计算不超过N的满足猜想的素数对的个数。

输入格式：每个测试输入包含1个测试用例，给出正整数N。

输出格式：每个测试用例的输出占一行，不超过N的满足猜想的素数对的个数。
输入样例：20

输出样例：4


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



int numberOfTwinPrime(int n) {
    vector<bool> isPrime = vector<bool>(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    int sqrt_n = static_cast<int>(sqrt(n));

    for (int i = 2; i <= sqrt_n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    /* cout << "DEBUG" << endl;
     int cnt = 0;

     for (int i = 0; i <= n; ++i) {
         if (isPrime[i]) {
             cout << i << " ";
             ++cnt;

             if (cnt % 5 == 0 || i == n) {
                 cout << endl;
             }
         }
     }*/
    int pre = 2, count = 0;

    for (int i = 3; i <= n; ++i) {
        if (isPrime[i]) {
            if (i - pre == 2) {
                ++count;
            }

            pre = i;
        }
    }

    return count;
}
#pragma warning(disable:4996)
int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    int n;
    cin >> n;
    cout << numberOfTwinPrime(n);
    return 0;
}
