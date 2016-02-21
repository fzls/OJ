/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:      v1.0
* @Time:         2016-02-21 18:42:27
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1014. Waiting in Line (30)
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
Suppose a bank has N windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. The rules for the customers to wait in line are:

The space inside the yellow line in front of each window is enough to contain a line with M customers. Hence when all the N lines are full, all the customers after (and including) the (NM+1)st one will have to wait in a line behind the yellow line.
Each customer will choose the shortest line to wait in when crossing the yellow line. If there are two or more lines with the same length, the customer will always choose the window with the smallest number.
Customer[i] will take T[i] minutes to have his/her transaction processed.
The first N customers are assumed to be served at 8:00am.
Now given the processing time of each customer, you are supposed to tell the exact time at which a customer has his/her business done.

For example, suppose that a bank has 2 windows and each window may have 2 custmers waiting inside the yellow line. There are 5 customers waiting with transactions taking 1, 2, 6, 4 and 3 minutes, respectively. At 08:00 in the morning, customer1 is served at window1 while customer2 is served at window2. Customer3 will wait in front of window1 and customer4 will wait in front of window2. Customer5 will wait behind the yellow line.

At 08:01, customer1 is done and customer5 enters the line in front of window1 since that line seems shorter now. Customer2 will leave at 08:02, customer4 at 08:06, customer3 at 08:07, and finally customer5 at 08:10.

Input

Each input file contains one test case. Each case starts with a line containing 4 positive integers: N (<=20, number of windows), M (<=10, the maximum capacity of each line inside the yellow line), K (<=1000, number of customers), and Q (<=1000, number of customer queries).

The next line contains K positive integers, which are the processing time of the K customers.

The last line contains Q positive integers, which represent the customers who are asking about the time they can have their transactions done. The customers are numbered from 1 to K.

Output

For each of the Q customers, print in one line the time at which his/her transaction is finished, in the format HH:MM where HH is in [08, 17] and MM is in [00, 59]. Note that since the bank is closed everyday after 17:00, for those customers who cannot be served before 17:00, you must output "Sorry" instead.

Sample Input
2 2 7 5
1 2 6 4 3 534 2
3 4 5 6 7
Sample Output
08:07
08:06
08:10
17:00
Sorry
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
#include <queue>

using namespace std;
#pragma region DebugSetting
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif
#pragma endregion

const int OPEN_TIME = 8 * 60;
const int CLOSED_TIME = 17 * 60;
const int NOT_SERVERED = 0x7FFFFFFF;
void print(int time, int server_time) {
    if(time >= CLOSED_TIME + server_time) {
        cout << "Sorry" << endl;
    } else {
        int hour = time / 60;
        int minute = time % 60;
        cout << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << endl;
    }
}

void compute_exit_time(vector<int> &exit_time, int n, int m, vector<int> time) {
    vector <queue<int>> counters(n + 1);
    int total_customer = exit_time.size() - 1;
    //把前m*n个客户依次排入队中，if any
    int cnt = 0;

    for (int i = 0; i < m; ++i)
        for (int j = 1; j <= n; ++j) {
            if(cnt >= total_customer) {
                break;
            }

            counters[j].push(++cnt);
        }

    //if one finished, server next, and enque new person if any
    int current_time = OPEN_TIME;
    int step = 1;

    do {
        //查找最快完成业务的客户所需时间
        step = 0x7FFFFFFF;

        for (int i = 1; i <= n; ++i) {
            if(!counters[i].empty()) {
                if (time[counters[i].front()] < step) {
                    step = time[counters[i].front()];
                }
            }
        }

        current_time += step;

        for (int i = 1; i <= n; ++i) {
            if(!counters[i].empty()) {
                int customer = counters[i].front();
                time[customer] -= step;

                if (time[customer] == 0) {
                    //customer finished
                    exit_time[customer] = current_time;
                    counters[i].pop();

                    if (cnt < total_customer) {
                        counters[i].push(++cnt);
                    }
                }
            }
        }
    } while (current_time <= CLOSED_TIME);

    //now time is 17:01, if any customer has not finished, set their time to CLOSED_TIME
    for (int i = 1; i <= n; ++i) {
        while(!counters[i].empty()) {
            int customer = counters[i].front(); counters[i].pop();
            exit_time[customer] = NOT_SERVERED;
        }
    }

    //将未排入队中的客户的时间设为无穷大
    while(cnt < total_customer) {
        exit_time[++cnt] = NOT_SERVERED;
    }
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
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    vector<int> time(k + 1);

    for (int i = 1; i <= k; ++i) {
        cin >> time[i];
    }

    vector<int> exitTime(k + 1, 0);
    compute_exit_time(exitTime, n, m, time);

    for (int i = 0; i < q; ++i) {
        int customer;
        cin >> customer;
        print(exitTime[customer], time[customer]);
    }

    return 0;
}
