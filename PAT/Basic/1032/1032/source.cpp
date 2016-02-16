/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:
* @Time:         2016-02-16 21:41:37
* @Description:  1032. 挖掘机技术哪家强(20)
时间限制
200 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
为了用事实说明挖掘机技术到底哪家强，PAT组织了一场挖掘机技能大赛。现请你根据比赛结果统计出技术最强的那个学校。

输入格式：

输入在第1行给出不超过105的正整数N，即参赛人数。随后N行，每行给出一位参赛者的信息和成绩，包括其所代表的学校的编号（从1开始连续编号）、及其比赛成绩（百分制），中间以空格分隔。

输出格式：

在一行中给出总得分最高的学校的编号、及其总分，中间以空格分隔。题目保证答案唯一，没有并列。

输入样例：
6
3 65
2 80
1 100
2 70
3 40
3 0
输出样例：
2 150
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
#include <unordered_map>
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
    int n;
    cin >> n;
    int maxIndex = 1;
    int id, score;
    // version 1 use fixed array
    // auto schools = vector<int>(100001, 0);
    // while(n--) {
    //     cin >> id >> score;
    //     schools[id] += score;
    // }
    // for (int i = 1; i <= 100000; ++i)
    //     if (schools[i] > schools[maxIndex]) {
    //         maxIndex = i;
    //     }
    //version 2
    unordered_map<int, int> schools;

    while(n--) {
        cin >> id >> score;

        if(schools.find(id) == schools.end()) {
            schools[id] = score;
        } else {
            schools[id] += score;
        }
    }

    for(auto school : schools) {
        if (school.second > schools[maxIndex]) {
            maxIndex = school.first;
        }
    }

    cout << maxIndex << " " << schools[maxIndex];
    return 0;
}
