/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-20 10:22:55
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1007. Maximum Subsequence Sum (25)
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
Given a sequence of K integers { N1, N2, ..., NK }. A continuous subsequence is defined to be { Ni, Ni+1, ..., Nj } where 1 <= i <= j <= K. The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

Input Specification:

Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (<= 10000). The second line contains K numbers, separated by a space.

Output Specification:

For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.

Sample Input:
10
-10 1 2 3 4 -5 -23 3 7 -21
Sample Output:
10 1 4
提交代码
版权所有 (C) 2011-2016 浙江大学计算机科学与技术学院

10 -10 1 2 3 4 -5 -23 3 7 -21
CHINESE (SIMPLIFIED)
10 -10 1 2 3 4 -5 -23 3 7 -21
EXTENSION OPTIONSMORE »

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

struct SeqSum {
    int sum;
    int left;
    int right;
    SeqSum() {
        sum = 0;
        left = 0;
        right = 0;
    }
};

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
    SeqSum tmp, max;
    bool flag1 = true;//start of none negative interval
    bool flag2 = true;//all negative
    int first, last, item;

    for (int i = 0; i < n; ++i) {
        cin >> item;
        tmp.sum += item;

        if (item >= 0) {
            flag2 = false;
        }

        if (i == 0) {
            first = item;
        }

        if (i == n - 1) {
            last = item;
        }

        if (flag1 && tmp.sum >= 0) {
            flag1 = false;
            tmp.left = item;
        }

        if(tmp.sum > max.sum) {
            tmp.right = item;
            max = tmp;
        }

        if(tmp.sum < 0) {
            tmp.sum = 0;
            flag1 = true;
        }
    }

    if(flag2) {
        cout << 0 << " " << first << " " << last << endl;
    } else {
        cout << max.sum << " " << max.left << " " << max.right << endl;
    }

    return 0;
}
