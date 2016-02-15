/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-15 16:09:24
* @Description:  1017. A除以B (20)
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
本题要求计算A/B，其中A是不超过1000位的正整数，B是1位正整数。你需要输出商数Q和余数R，使得A = B * Q + R成立。

输入格式：

输入在1行中依次给出A和B，中间以1空格分隔。

输出格式：

在1行中依次输出Q和R，中间以1空格分隔。

输入样例：
123456789050987654321 7
输出样例：
17636684150141093474 3
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



int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    string dividend, quotient;
    int divisor, remainder = 0, div;
    cin >> dividend >> divisor;

    for (char d : dividend) {
        div = d - '0' + 10 * remainder;
        quotient.append(1, div / divisor + '0');
        remainder = div % divisor;
    }

    //if the prefix is 0
    int index = 0;

    for (; index < quotient.size() && quotient[index] == '0'; ++index)
        ;

    quotient.erase(0, index);

    if (quotient.empty()) {
        cout << "0";
    } else {
        cout << quotient;
    }

    cout << " " << remainder;
    return 0;
}
