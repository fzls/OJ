//!++模拟队列的题目多看看，注意总结
//!++做模拟题时，先将整个流程搞明白，再进行coding
/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-25 19:32:47
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1026. Table Tennis (30)
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
A table tennis club has N tables available to the public. The tables are numbered from 1 to N. For any pair of players, if there are some tables open when they arrive, they will be assigned to the available table with the smallest number. If all the tables are occupied, they will have to wait in a queue. It is assumed that every pair of players can play for at most 2 hours.

Your job is to count for everyone in queue their waiting time, and for each table the number of players it has served for the day.

One thing that makes this procedure a bit complicated is that the club reserves some tables for their VIP members. When a VIP table is open, the first VIP pair in the queue will have the priviledge to take it. However, if there is no VIP in the queue, the next pair of players can take it. On the other hand, if when it is the turn of a VIP pair, yet no VIP table is available, they can be assigned as any ordinary players.

Input Specification:

Each input file contains one test case. For each case, the first line contains an integer N (<=10000) - the total number of pairs of players. Then N lines follow, each contains 2 times and a VIP tag: HH:MM:SS - the arriving time, P - the playing time in minutes of a pair of players, and tag - which is 1 if they hold a VIP card, or 0 if not. It is guaranteed that the arriving time is between 08:00:00 and 21:00:00 while the club is open. It is assumed that no two customers arrives at the same time. Following the players' info, there are 2 positive integers: K (<=100) - the number of tables, and M (< K) - the number of VIP tables. The last line contains M table numbers.

Output Specification:

For each test case, first print the arriving time, serving time and the waiting time for each pair of players in the format shown by the sample. Then print in a line the number of players served by each table. Notice that the output must be listed in chronological order of the serving time. The waiting time must be rounded up to an integer minute(s). If one cannot get a table before the closing time, their information must NOT be printed.

Sample Input:
9
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 5 0
08:12:00 10 1
20:50:00 10 0
08:01:30 15 1
20:53:00 10 1
3 1
2
Sample Output:
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:12:00 08:16:30 5
08:10:00 08:20:00 10
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
3 3 2
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

const int OPEN_TIME = 8 * 60 * 60;
const int CLOSED_TIME = 21 * 60 * 60;
const int INF = 0x7FFFFFFF;
struct Player {
    string arriving_time;
    int arriving_time_ser;
    int playing_time;
    int vip_tag;
    string serving_time;
    int serving_time_ser;
    int waiting_time;

    void get_arriving_time_serilized() {
        int hour, minute, second;
        hour = atoi(arriving_time.substr(0, 2).data());
        minute = atoi(arriving_time.substr(3, 2).data());
        second = atoi(arriving_time.substr(6, 2).data());
        arriving_time_ser = hour * 60 * 60 + minute * 60 + second;
    }


};



struct Table {
    int served_num;
    int vip_tag;
    int current_player;
    int current_player_tag;
    Table() : served_num{ 0 }, vip_tag{ 0 }, current_player{ -1 }, current_player_tag{ 0 } {
    }

    bool isIdle();
};

bool Table::isIdle() {
    return current_player == -1;
}

bool cmp_arriving_time(const Player &lhs, const Player &rhs) {
    return lhs.arriving_time_ser < rhs.arriving_time_ser;
}
bool cmp_serving_time(const Player &lhs, const Player &rhs) {
    return lhs.serving_time_ser < rhs.serving_time_ser;
}

void startQueuing(vector<Player> &players, vector<Table> &tables) {
    int current_time = OPEN_TIME;
    int cnt = 0;
    queue<int> player[2];

    while(current_time < CLOSED_TIME) {
        //for the table that has player, continue play and set idle if played enough
        for (int i = 0; i < tables.size(); ++i) {
            if(!tables[i].isIdle()) {
                int cp = tables[i].current_player;
                int duration = current_time - players[cp].serving_time_ser;//in seconds

                if(duration == players[cp].playing_time * 60) {
                    tables[i].current_player = -1;
                }
            }
        }

        //if customer come, enque to corresponding queue
        if(cnt < players.size() && players[cnt].arriving_time_ser == current_time) {
            player[players[cnt].vip_tag].push(cnt);
            cnt++;
        }

        //if has idle table, deque
        //1.vip table ,if idle put vip in, if any
        for (int i = 0; i < tables.size(); ++i) {
            if(tables[i].vip_tag == 0 || !tables[i].isIdle()) {
                continue;
            }

            if(!player[1].empty()) {
                int p = player[1].front(); player[1].pop();
                tables[i].current_player = p;
                tables[i].served_num++;
                players[p].serving_time_ser = current_time;
            }
        }

        //2.normal table, if idle put first player in, if any
        for (int i = 0; i < tables.size(); ++i) {
            if(!tables[i].isIdle()) {
                continue;
            }

            if (!player[0].empty() && !player[1].empty()) {
                int pv = player[1].front();
                int pn = player[0].front();

                if (players[pv].arriving_time_ser < players[pn].arriving_time_ser) {
                    //vip
                    player[1].pop();
                    tables[i].served_num++;
                    tables[i].current_player = pv;
                    players[pv].serving_time_ser = current_time;
                } else {
                    //nor
                    player[0].pop();
                    tables[i].served_num++;
                    tables[i].current_player = pn;
                    players[pn].serving_time_ser = current_time;
                }
            } else if (!player[0].empty()) {
                //nor
                int pn = player[0].front(); player[0].pop();
                tables[i].served_num++;
                tables[i].current_player = pn;
                players[pn].serving_time_ser = current_time;
            } else if (!player[1].empty()) {
                //vip
                int pv = player[1].front(); player[1].pop();
                tables[i].served_num++;
                tables[i].current_player = pv;
                players[pv].serving_time_ser = current_time;
            }
        }

        current_time++;
    }

    sort(players.begin(), players.end(), cmp_serving_time);
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
    vector<Player> players;

    while(n--) {
        Player tmp;
        cin >> tmp.arriving_time >> tmp.playing_time >> tmp.vip_tag;
        tmp.playing_time = min(tmp.playing_time, 120);
        tmp.get_arriving_time_serilized();
        tmp.serving_time_ser = INF;
        tmp.waiting_time = 0;
        players.push_back(std::move(tmp));
    }

    sort(players.begin(), players.end(), cmp_arriving_time);
    int n_table, n_vip;
    cin >> n_table >> n_vip;
    vector<Table> tables(n_table);

    while(n_vip--) {
        int vip;
        cin >> vip;
        tables[vip - 1].vip_tag = 1;
    }

    startQueuing(players, tables);

    for(auto player : players) {
        if(player.serving_time_ser == INF) {
            continue;
        }

        cout << player.arriving_time << " ";
        int hour, minute, second;
        hour = player.serving_time_ser / 3600;
        minute = player.serving_time_ser % 3600 / 60;
        second = player.serving_time_ser % 60;
        cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << ":" << setw(2) << setfill('0') << second;
        cout << " " << (player.serving_time_ser - player.arriving_time_ser + 30) / 60 << endl;
    }

    for (int i = 0; i < tables.size(); ++i) {
        if (i) {
            cout << " ";
        }

        cout << tables[i].served_num;
    }

    return 0;
}
