/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:      v1.0
* @Time:         2016-02-17 15:50:19
* @Description:  1037. 在霍格沃茨找零钱（20）
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
如果你是哈利·波特迷，你会知道魔法世界有它自己的货币系统 —— 就如海格告诉哈利的：“十七个银西可(Sickle)兑一个加隆(Galleon)，二十九个纳特(Knut)兑一个西可，很容易。”现在，给定哈利应付的价钱P和他实付的钱A，你的任务是写一个程序来计算他应该被找的零钱。

输入格式：

输入在1行中分别给出P和A，格式为“Galleon.Sickle.Knut”，其间用1个空格分隔。这里Galleon是[0, 107]区间内的整数，Sickle是[0, 17)区间内的整数，Knut是[0, 29)区间内的整数。

输出格式：

在一行中用与输入同样的格式输出哈利应该被找的零钱。如果他没带够钱，那么输出的应该是负数。

输入样例1：
10.16.27 14.1.28
输出样例1：
3.2.1
输入样例2：
14.1.28 10.16.27
输出样例2：
-3.2.1
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
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif



void getGSK(string p, long long &p_g, long long &p_s, long long &p_k) {
    auto point_pos1 = p.find('.');
    string g, s, k;
    g = p.substr(0, point_pos1);
    p_g = atoll(g.c_str());
    auto point_pos2 = p.find_first_of('.', point_pos1 + 1);
    s = p.substr(point_pos1 + 1, point_pos2 - point_pos1 - 1);
    p_s = atoll(s.c_str());
    k = p.substr(point_pos2 + 1);
    p_k = atoll(k.c_str());
}

void getChange(string p, string a) {
    bool isMinus = false;
    long long p_g, p_s, p_k;
    long long a_g, a_s, a_k;
    getGSK(p, p_g, p_s, p_k);
    getGSK(a, a_g, a_s, a_k);
    long long result = (p_g - a_g) * 17 * 29 + (p_s - a_s) * 29 + (p_k - a_k);
    result = -result;

    if (result < 0) {
        isMinus = true;
        result = -result;
    }

    long long g, s, k;
    g = result / (17 * 29);
    s = result % (17 * 29) / 29;
    k = result % 29;

    if (isMinus) {
        cout << "-";
    }

    cout << g << "." << s << "." << k << endl;
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
    string p, a;
    cin >> p >> a;
    getChange(p, a);
    return 0;
}
