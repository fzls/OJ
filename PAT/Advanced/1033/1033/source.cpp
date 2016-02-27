/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-27 14:44:46
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1033. To Fill or Not to Fill (25)
时间限制
10 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
ZHANG, Guochuan
With highways available, driving a car from Hangzhou to any other city is easy. But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. Different gas station may give different price. You are asked to carefully design the cheapest route to go.

Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive numbers: Cmax (<= 100), the maximum capacity of the tank; D (<=30000), the distance between Hangzhou and the destination city; Davg (<=20), the average distance per unit gas that the car can run; and N (<= 500), the total number of gas stations. Then N lines follow, each contains a pair of non-negative numbers: Pi, the unit gas price, and Di (<=D), the distance between this station and Hangzhou, for i=1,...N. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print the cheapest price in a line, accurate up to 2 decimal places. It is assumed that the tank is empty at the beginning. If it is impossible to reach the destination, print "The maximum travel distance = X" where X is the maximum possible distance the car can run, accurate up to 2 decimal places.

Sample Input 1:
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
Sample Output 1:
749.17
Sample Input 2:
50 1300 12 2
7.10 0
7.00 600
Sample Output 2:
The maximum travel distance = 1200.00
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
int cmax;


struct GasStation {
    double price;
    int position;
    GasStation(double p = 0.0, int po = -1)
        : price{p},
          position{po} {
    }
};

bool cmp_pos(const GasStation &lhs, const GasStation &rhs) {
    return lhs.position < rhs.position;
}

int max_distance(vector<GasStation> &stations, int distance, int dpu) {
    if (stations[0].position != 0) {
        return 0;
    }

    int longest_run_without_recharge = dpu * cmax;

    for (int i = 1; i < stations.size(); ++i) {
        if (stations[i].position - stations[i - 1].position > longest_run_without_recharge) {
            return stations[i - 1].position + longest_run_without_recharge;
        }
    }

    return distance;
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
    int destination, dpu, n;
    cin >> cmax >> destination >> dpu >> n;
    vector<GasStation> stations;

    for (int i = 0; i < n; ++i) {
        GasStation tmp;
        cin >> tmp.price >> tmp.position;
        stations.push_back(move(tmp));
    }

    //add destination to the list as sentinel
    stations.push_back(move(GasStation(0.0, destination)));
    sort(stations.begin(), stations.end(), cmp_pos);
    #pragma region DEBUG_CODE
    {
        #ifdef DEBUG

        for (auto s : stations) {
            cout << setprecision(2) << fixed << s.price << " " << s.position << endl;
        }

        #endif
    }
    #pragma endregion
    int max_d = max_distance(stations, destination, dpu);
    double remain = 0.0, gasToNext = 0.0, buy, cost = 0.0;

    if (max_d == destination) {
        //if we can get there, then find cheapest
        //solution: buy only necessary gas
        // case 1: if it is cheapest , than buy as many as possible
        // case 2: if there is someone later cheaper than this, and the distance is d
        //         , so the gas need to drive to there is g, then we buy enough gas,
        //          which is the min of the g-r and cmax-r
        //?to avoid this discussion, we can set the destination as sentinel, whose price is zero, so there will be at least one(des) cheaper than any other
        for (int i = 0; i < stations.size() - 1; ++i) { //ignore the sentinel
            //find next station with lower price
            int nextLow = i + 1;

            for (; !(stations[nextLow].price < stations[i].price); ++nextLow)
                ;

            //decide how much to buy
            //the gas need to drive to the next station with lower price(which is always exist with the help of sentinel)
            buy = (stations[nextLow].position - stations[i].position) * 1.0 / dpu - remain;
            //can not buy more than the tank can contain
            buy = min(cmax - remain, buy);
            //and buy should not be negative
            buy = max(0.0, buy);
            //update tank and cost
            remain += buy;
            cost += buy * stations[i].price;
            //run to next station
            remain -= 1.0 * (stations[i + 1].position - stations[i].position) / dpu;
        }

        cout << setprecision(2) << fixed << cost << endl;
    } else {
        //find out max distance
        cout << "The maximum travel distance = " << setprecision(2) << fixed << max_d * 1.0 << endl;
    }

    return 0;
}
