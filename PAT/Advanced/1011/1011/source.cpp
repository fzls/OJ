/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-21 14:17:37
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1011. World Cup Betting (20)
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
With the 2010 FIFA World Cup running, football fans the world over were becoming increasingly excited as the best players from the best teams doing battles for the World Cup trophy in South Africa. Similarly, football betting fans were putting their money where their mouths were, by laying all manner of World Cup bets.

Chinese Football Lottery provided a "Triple Winning" game. The rule of winning was simple: first select any three of the games. Then for each selected game, bet on one of the three possible results -- namely W for win, T for tie, and L for lose. There was an odd assigned to each result. The winner's odd would be the product of the three odds times 65%.

For example, 3 games' odds are given as the following:

W    T    L
1.1  2.5  1.7
1.2  3.0  1.6
4.1  1.2  1.1
To obtain the maximum profit, one must buy W for the 3rd game, T for the 2nd game, and T for the 1st game. If each bet takes 2 yuans, then the maximum profit would be (4.1*3.0*2.5*65%-1)*2 = 37.98 yuans (accurate up to 2 decimal places).

Input

Each input file contains one test case. Each case contains the betting information of 3 games. Each game occupies a line with three distinct odds corresponding to W, T and L.

Output

For each test case, print in one line the best bet of each game, and the maximum profit accurate up to 2 decimal places. The characters and the number must be separated by one space.

Sample Input
1.1 2.5 1.7
1.2 3.0 1.6
4.1 1.2 1.1
Sample Output
T T W 37.98
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



int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    char res[] = { 'W', 'T', 'L' };
    double product = 1;

    for (int i = 0; i < 3; ++i) {
        double maxVal = 0;
        int maxIdx = 0;
        double tmp;

        for (int j = 0; j < 3; ++j) {
            cin >> tmp;

            if(tmp > maxVal) {
                maxVal = tmp;
                maxIdx = j;
            }
        }

        cout << res[maxIdx] << " ";
        product *= maxVal;
    }

    cout << setprecision(2) << fixed << (product * 0.65 - 1.0) * 2.0 + 1e-5;
    return 0;
}
