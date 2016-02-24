/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-24 16:34:40
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1017. Queueing at Bank (25)
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
Suppose a bank has K windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. All the customers have to wait in line behind the yellow line, until it is his/her turn to be served and there is a window available. It is assumed that no window can be occupied by a single customer for more than 1 hour.

Now given the arriving time T and the processing time P of each customer, you are supposed to tell the average waiting time of all the customers.

Input Specification:

Each input file contains one test case. For each case, the first line contains 2 numbers: N (<=10000) - the total number of customers, and K (<=100) - the number of windows. Then N lines follow, each contains 2 times: HH:MM:SS - the arriving time, and P - the processing time in minutes of a customer. Here HH is in the range [00, 23], MM and SS are both in [00, 59]. It is assumed that no two customers arrives at the same time.

Notice that the bank opens from 08:00 to 17:00. Anyone arrives early will have to wait in line till 08:00, and anyone comes too late (at or after 17:00:01) will not be served nor counted into the average.

Output Specification:

For each test case, print in one line the average waiting time of all the customers, in minutes and accurate up to 1 decimal place.

Sample Input:
7 3
07:55:00 16
17:00:01 2
07:59:59 15
08:01:00 60
08:00:00 30
08:00:02 2
08:03:00 10
Sample Output:
8.2
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
#include <queue>
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

int waitTime = 0;
int validCustomer = 0;
const int IDLE = -1;
const int START_OF_DAY = 0;
const int OPEN_TIME = 8 * 60 * 60;
const int CLOSE_TIME = 17 * 60 * 60;

struct Customer {
    string arriveTime;
    int arriveTimeSer;
    void serilizeTime();
    int serverTime;//+InMinute
};

void Customer::serilizeTime() {
    int hour, minute, second;
    hour = atoi(arriveTime.substr(0, 2).data());
    minute = atoi(arriveTime.substr(3, 2).data());
    second = atoi(arriveTime.substr(6, 2).data());
    arriveTimeSer = hour * 60 * 60 + minute * 60 + second;
}

void startQueuing(vector<Customer> &customers, int counter_n) {
    vector<int> counters(counter_n, IDLE);
    queue<int> que;
    int currTime = START_OF_DAY;
    int cnt = 0;
    int counterInService = 0;

    for (; currTime <= CLOSE_TIME; ++currTime) {
        //serve
        for (int i = 0; i < counter_n; ++i) {
            int id = counters[i];

            if(id != IDLE) {
                customers[id].serverTime--;

                if (customers[id].serverTime == 0) {
                    counters[i] = IDLE;
                    counterInService--;
                }
            }
        }

        //enque
        while(cnt < customers.size() && customers[cnt].arriveTimeSer == currTime) {
            que.push(cnt);
            cnt++;
            validCustomer++;
        }

        //if there is any counter is IDLE
        if(currTime >= OPEN_TIME && counterInService < counter_n && !que.empty() ) {
            for (int i = 0; i < counter_n; ++i) {
                if(counters[i] == IDLE && !que.empty()) {
                    counters[i] = que.front(); que.pop();
                    counterInService++;
                }
            }
        }

        //add wait time
        waitTime += que.size();
    }

    while(!que.empty()) {
        //serve
        for (int i = 0; i < counter_n; ++i) {
            int id = counters[i];

            if (id != IDLE) {
                customers[id].serverTime--;

                if (customers[id].serverTime == 0) {
                    counters[i] = IDLE;
                    counterInService--;
                }
            }
        }

        //if there is any counter is IDLE
        if (currTime >= OPEN_TIME && counterInService < counter_n && !que.empty()) {
            for (int i = 0; i < counter_n; ++i) {
                if (counters[i] == IDLE && !que.empty()) {
                    counters[i] = que.front(); que.pop();
                    counterInService++;
                }
            }
        }

        //add wait time
        waitTime += que.size();
    }
}

bool cmp_arrive_time(const Customer &lhs, const Customer &rhs) {
    return lhs.arriveTime < rhs.arriveTime;
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
    int totalCustomer, counter_n;
    cin >> totalCustomer >> counter_n;
    vector<Customer> customers;
    Customer tmp;

    for (int t = 0; t < totalCustomer; ++t) {
        cin >> tmp.arriveTime >> tmp.serverTime;
        tmp.serverTime *= 60;
        tmp.serilizeTime();
        customers.push_back(tmp);
    }

    sort(customers.begin(), customers.end(), cmp_arrive_time);
    startQueuing(customers, counter_n);
    cout << setprecision(1) << fixed << 1.0 * waitTime / validCustomer / 60 << endl;
    return 0;
}
