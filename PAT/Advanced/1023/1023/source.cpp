/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-25 11:38:55
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1023. Have Fun with Numbers (20)
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
Notice that the number 123456789 is a 9-digit number consisting exactly the numbers from 1 to 9, with no duplication. Double it we will obtain 246913578, which happens to be another 9-digit number consisting exactly the numbers from 1 to 9, only in a different permutation. Check to see the result if we double it again!

Now you are suppose to check if there are more numbers with this property. That is, double a given number with k digits, you are to tell if the resulting number consists of only a permutation of the digits in the original number.

Input Specification:

Each input file contains one test case. Each case contains one positive integer with no more than 20 digits.

Output Specification:

For each test case, first print in a line "Yes" if doubling the input number gives a number that consists of only a permutation of the digits in the original number, or "No" if not. Then in the next line, print the doubled number.

Sample Input:
1234567899
Sample Output:
Yes
2469135798
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

vector<int> num(21, -1);
vector<int> dou(21, -1);
int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    string n;
    cin >> n;

    for (int i = 20, j = n.size() - 1; j >= 0; --i, --j) {
        num[i] = n[j] - '0';
    }

    //get double
    int addend = 0, tmp = 0, i;

    for (i = 20; num[i] != -1; --i) {
        tmp = num[i] * 2 + addend;
        dou[i] = tmp % 10;
        addend = tmp / 10;
    }

    if (addend != 0) {
        dou[i] = addend;
    }

    //judge permutation
    vector<int> digit(11, 0);

    for (int j = 0; j <= 20; ++j) {
        digit[(num[j] + 11) % 11]++;
    }

    for (int j = 0; j <= 20; ++j) {
        digit[(dou[j] + 11) % 11]--;
    }

    bool isPer = true;

    for (int j = 0; j < 11; ++j)
        if(digit[j] != 0) {
            isPer = false;
            break;
        }

    //output
    if (isPer) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    for (i = 0; dou[i] == -1; ++i)
        ;

    for (; i <= 20; ++i) {
        cout << dou[i];
    }

    cout << endl;
    return 0;
}
