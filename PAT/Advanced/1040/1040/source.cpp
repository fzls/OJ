/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-03-05 20:53:31
* @Description:  风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1040. Longest Symmetric String (25)
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
Given a string, you are supposed to output the length of the longest symmetric sub-string. For example, given "Is PAT&TAP symmetric?", the longest symmetric sub-string is "s PAT&TAP s", hence you must output 11.

Input Specification:

Each input file contains one test case which gives a non-empty string of length no more than 1000.

Output Specification:

For each test case, simply print the maximum length in a line.

Sample Input:
Is PAT&TAP symmetric?
Sample Output:
11
提交代码
*
+----------------------------------------------------------
*/
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:66777216")

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
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

const int INF = 0x7FFFFFFF;



int util(int i, int j, int length, const string &str) {
    int cnt = 0;

    for (int k = 0; k < length; ++k)
        if (str[i - k] == str[j + k]) {
            cnt += 2;
        } else {
            break;
        }

    return cnt;
}

int lss(const string &str) {
    int n = str.size();
    int longest = 1;

    for (int l = 1; l <= n - 1; ++l) {
        //even case
        longest = max(longest, util(l - 1, l, min(l, n - l), str));
        //odd case
        longest = max(longest, util(l - 2, l, min(l - 1, n - l), str) + 1);
    }

    return longest;
}
//?+Manacher算法
int lss2(const string &str) {
    string s;
    s.append("$");//add $ and / to two sides to avoid index out of range

    for (int i = 0; i < str.size(); ++i) {
        s.append(1, '#');
        s.append(1, str[i]);
    }

    s.append("#/");
    //now only need to consider odd case
    int longest = 0;
    int n = s.size();
    vector<int> p(n, 0);
    int mx = 0, center = 0;

    for (int i = 1; i <= n - 2; ++i) {
        p[i] = i < mx ? min(p[2 * center - i], mx - i) : 1;

        while (s[i + p[i]] == s[i - p[i]]) {
            ++p[i];
        }

        if (i + p[i] > mx) {
            mx = i + p[i];
            center = i;
        }

        longest = max(longest, p[i] - 1);
        //        longest = max(longest, util(i - 1, i + 1, min(i, n - 1 - i), s) / 2);
    }

    return longest;
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
    string str;
    getline(cin, str);
    cout << lss2(str) << endl;
    return 0;
}
