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
// //二，Manacher 算法复杂度分析
// 下面简单分析下为何Manacher 算法是线性时间的。
// 设字符串长度为n。
// 结合上面的分析以及关键部分代码来看，重点当j回文串不包含在id回文串内部时，当前迭代的运算次数不固定，对应代码的第46、47行。
// 此时，只要46、47行代码执行超过一次，求得的i回文串的右边界将大于id回文串的右边界，id和mi 将更新为更大的值；mi 最多通过n 次更新达到最大值n-1，自此以后，每轮迭代都只有常数次运算。
// 简单来说，46、47行代码运行的总次数不会超过最终mi 的值，即n-1，所以该算法的时间复杂度为：
// O(n) + O(n) = O(n)
//

//DP1
int lss_dp(string s) {
    int n = s.size();
    vector<vector<bool>> p(n, vector<bool>(n, false));
    //deal with base case (length of 1 and 2)
    int length = 0;

    for (int i = 0; i < n; ++i) {
        p[i][i] = true;
        length = 1;
    }

    for (int i = 0; i < n - 1; ++i) {
        if(s[i] == s[i + 1]) {
            p[i][i + 1] = true;
            length = 2;
        }
    }

    //other case
    for (int l = 3; l <= n; ++l)
        for (int i = 0, j = l - 1; j < n; ++i, ++j) {
            if(s[i] == s[j] && p[i + 1][j - 1]) {
                p[i][j] = true;
                length = l;
            }
        }

    return length;
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
    cout << lss_dp(str) << endl;
    return 0;
}
