/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-26 19:06:27
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1029. Median (25)
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
Given an increasing sequence S of N integers, the median is the number at the middle position. For example, the median of S1={11, 12, 13, 14} is 12, and the median of S2={9, 10, 15, 16, 17} is 15. The median of two sequences is defined to be the median of the nondecreasing sequence which contains all the elements of both sequences. For example, the median of S1 and S2 is 13.

Given two increasing sequences of integers, you are asked to find their median.

Input

Each input file contains one test case. Each case occupies 2 lines, each gives the information of a sequence. For each sequence, the first positive integer N (<=1000000) is the size of that sequence. Then N integers follow, separated by a space. It is guaranteed that all the integers are in the range of long int.

Output

For each test case you should output the median of the two given sequences in a line.

Sample Input
4 11 12 13 14
5 9 10 15 16 17
Sample Output
13
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
int median, cnt = -1;
bool update_and_judge_if_done(const int &val, int &index) {
    cnt++;

    if (cnt == median) {
        cout << val << endl;
        return true;
    }

    ++index;
    return false;
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
    {
        //    int n1;
        //    cin >> n1;
        //    vector<int> first;
        //    int tmp;
        //
        //    for (int i = 0; i < n1; ++i) {
        //        cin >> tmp;
        //        first.push_back(tmp);
        //    }
        //
        //    int n2;
        //    cin >> n2;
        //    //  vector<int> second(n2);
        //
        //    for (int i = 0; i < n2; ++i) {
        //        cin >> tmp;
        //        first.push_back(tmp);
        //    }
        //
        //    int median = (n1 + n2) / 2;
        //    sort(first.begin(), first.end());
        //    cout << first[median] << endl;
    }
    int n1;
    cin >> n1;
    vector<int> first(n1);

    for (int i = 0; i < n1; ++i) {
        //        cin >> first[i];
        scanf("%d", &first[i]);
    }

    int n2;
    cin >> n2;
    vector<int> second(n2);

    for (int i = 0; i < n2; ++i) {
        //        cin >> second[i];
        scanf("%d", &second[i]);
    }

    //find median
    median = (n1 + n2 - 1) / 2;
    int i = 0, j = 0;

    while(i < n1 && j < n2) {
        if(first[i] <= second[j]) {
            if (update_and_judge_if_done(first[i], i)) {
                break;
            }
        } else {
            if (update_and_judge_if_done(second[j], j)) {
                break;
            }
        }
    }

    if(cnt != median) {
        while(i < n1) {
            if (update_and_judge_if_done(first[i], i)) {
                break;
            }
        }

        while(j < n2) {
            if (update_and_judge_if_done(second[j], j)) {
                break;
            }
        }
    }

    return 0;
}
