/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-20 15:42:57
* @Description:  风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1010. Radix (25)
时间限制
400 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
CHEN, Yue
Given a pair of positive integers, for example, 6 and 110, can this equation 6 = 110 be true? The answer is "yes", if 6 is a decimal number and 110 is a binary number.

Now for any pair of positive integers N1 and N2, your task is to find the radix of one number while that of the other is given.

Input Specification:

Each input file contains one test case. Each case occupies a line which contains 4 positive integers:
N1 N2 tag radix
Here N1 and N2 each has no more than 10 digits. A digit is less than its radix and is chosen from the set {0-9, a-z} where 0-9 represent the decimal numbers 0-9, and a-z represent the decimal numbers 10-35. The last number "radix" is the radix of N1 if "tag" is 1, or of N2 if "tag" is 2.

Output Specification:

For each test case, print in one line the radix of the other number so that the equation N1 = N2 is true. If the equation is impossible, print "Impossible". If the solution is not unique, output the smallest possible radix.

Sample Input 1:
6 110 1 10
Sample Output 1:
2
Sample Input 2:
1 ab 1 2
Sample Output 2:
Impossible
提交代码
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
#pragma region DebugSetting
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif
#pragma endregion

map<char, long long> table;
void setTable() {
    for (long long i = 0; i < 10; ++i) {
        table[i + '0'] = i;
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        table[ch] = ch - 'a' + 10;
    }
}
long long getDecimal(string num, long long radix) {
    long long res = 0, tmp;

    for (long long i = 0; i < num.size(); ++i) {
        tmp = table[num[i]];

        if (tmp >= radix) {
            res = -1;
            break;
        }

        res = res * radix + tmp;
    }

    return res;
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
    setTable();
    string first, second;
    long long tag, radix;
    //radix is represented by 2~36
    cin >> first >> second >> tag >> radix;

    if (tag == 2) {
        swap(first, second);
    }

    //radix of first is known
    long long first_in_decimal = getDecimal(first, radix);
    long long radix_second = 2;
    long long upperBound = first_in_decimal >= 36 ? first_in_decimal : 36;

    for (; radix_second <= upperBound && getDecimal(second, radix_second) != first_in_decimal; ++radix_second)
        ;

    if (radix_second > upperBound) {
        cout << "Impossible" << endl;
    } else {
        cout << radix_second << endl;
    }

    return 0;
}