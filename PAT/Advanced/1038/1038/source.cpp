/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-28 21:46:04
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1038. Recover the Smallest Number (30)
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
Given a collection of number segments, you are supposed to recover the smallest number from them. For example, given {32, 321, 3214, 0229, 87}, we can recover many numbers such like 32-321-3214-0229-87 or 0229-32-87-321-3214 with respect to different orders of combinations of these segments, and the smallest number is 0229-321-3214-32-87.

Input Specification:

Each input file contains one test case. Each case gives a positive integer N (<=10000) followed by N number segments. Each segment contains a non-negative integer of no more than 8 digits. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the smallest number in one line. Do not output leading zeros.

Sample Input:
5 32 321 3214 0229 87
Sample Output:
22932132143287
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

bool prefix(string lhs, string rhs) {
    if (lhs.size() == rhs.size()) {
        return false;
    }

    if (lhs.size() > rhs.size()) {
        swap(lhs, rhs);
    }

    //lhs is shorter than rhs
    return rhs.substr(0, lhs.size()) == lhs;
}
//?this version is a little complicate but more efficient
bool cmp(const string &lhs, const string &rhs) {
    if(!prefix(lhs, rhs)) {
        return lhs < rhs;
    } else {
        if(lhs.length() < rhs.length()) {
            //lhs is prefix of rhs
            string postfix = rhs.substr(lhs.length());
            return cmp(lhs, postfix);
        } else {
            string postfix = lhs.substr(rhs.length());
            return cmp(postfix, rhs);
        }
    }
}
//?this version is eaiser but more costly
bool cmp_v2(const string &lhs, const string &rhs) {
    return lhs + rhs < rhs + lhs;
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
    int n;
    cin >> n;
    vector<string> str(n);

    for (int i = 0; i < n; ++i) {
        cin >> str[i];
    }

    sort(str.begin(), str.end(), cmp);
    //    sort(str.begin(), str.end(), cmp_v2);
    string result;

    for (int i = 0; i < n; ++i) {
        result.append(str[i]);
    }

    int pos = 0;

    while (pos < result.size() && result[pos] == '0') {
        ++pos;
    }

    if (pos == result.size()) {
        cout << "0" << endl;
    } else {
        cout << result.substr(pos) << endl;
    }

    return 0;
}
