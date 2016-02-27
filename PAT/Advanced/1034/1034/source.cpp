/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-27 20:45:05
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1034. Head of a Gang (30)
时间限制
100 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
CHEN, Yue
One way that the police finds the head of a gang is to check people's phone calls. If there is a phone call between A and B, we say that A and B is related. The weight of a relation is defined to be the total time length of all the phone calls made between the two persons. A "Gang" is a cluster of more than 2 persons who are related to each other with total relation weight being greater than a given threshold K. In each gang, the one with maximum total weight is the head. Now given a list of phone calls, you are supposed to find the gangs and the heads.

Input Specification:

Each input file contains one test case. For each case, the first line contains two positive numbers N and K (both less than or equal to 1000), the number of phone calls and the weight threthold, respectively. Then N lines follow, each in the following format:

Name1 Name2 Time

where Name1 and Name2 are the names of people at the two ends of the call, and Time is the length of the call. A name is a string of three capital letters chosen from A-Z. A time length is a positive integer which is no more than 1000 minutes.

Output Specification:

For each test case, first print in a line the total number of gangs. Then for each gang, print in a line the name of the head and the total number of the members. It is guaranteed that the head is unique for each gang. The output must be sorted according to the alphabetical order of the names of the heads.

Sample Input 1:
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
Sample Output 1:
2
AAA 3
GGG 3
Sample Input 2:
8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
Sample Output 2:
0
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
const int MAX_SIZE = 2000;
//?+there is at most 1000 call records, which means if no people appear twice, then there can be at most 2000 different people, so we should set the upbound as 2000
//?+ or we can first find out how many people there are, and then allocate the space
//!++find out where will out of index if max_size is 1000
struct Record {
    int peo;
    int time;

    Record(int peo, int time)
        : peo(peo),
          time(time) {
    }
};
struct Gang {
    string head;
    int scale;

    Gang(string head, int scale)
        : head(head),
          scale(scale) {
    }
};

bool cmp_head_name(const Gang &lhs, const Gang &rhs) {
    return lhs.head < rhs.head;
}
struct Graph {
    int v;
    vector<list<Record>> guys;
    vector<string> id_to_name;
    vector<int> times;
    vector<vector<bool>> visited;
    vector<bool> visited_peo;
    Graph(): guys(MAX_SIZE), times(MAX_SIZE, 0), visited(MAX_SIZE, vector<bool>(MAX_SIZE, false)), visited_peo(MAX_SIZE, false) {
    }

    void findGangs(int threshold) {
        // vector out of index?
        vector<Gang> gangs;

        for (int i = 0; i < v; ++i) {
            if (visited_peo[i]) {
                continue;
            }

            int totalTime = 0, head;
            vector<int> gang;
            dfs(i, totalTime, gang);

            //find the head
            if (gang.size() <= 2 || totalTime <= threshold) {
                continue;
            }

            head = gang[0];

            for (auto p : gang) {
                if (times[p] > times[head]) {
                    head = p;
                }
            }

            gangs.push_back(Gang(id_to_name[head], gang.size()));
        }

        sort(gangs.begin(), gangs.end(), cmp_head_name);
        cout << gangs.size() << endl;

        for (auto gang : gangs) {
            cout << gang.head << " " << gang.scale << endl;
        }
    }

    void dfs(int v, int &totalTime, vector<int> &gang) {
        if (!visited_peo[v]) {
            gang.push_back(v);
        }

        visited_peo[v] = true;

        for (auto nv : guys[v]) {
            if (!visited[v][nv.peo]) {
                totalTime += nv.time;
                times[v] += nv.time;
                times[nv.peo] += nv.time;
                visited[v][nv.peo] = true;

                if (!visited_peo[nv.peo]) {
                    dfs(nv.peo, totalTime, gang);
                }
            }
        }
    }



};

int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    int n, k;
    cin >> n >> k;
    int cnt = 0;
    map<string, int> name_to_id;
    Graph graph;

    for (int t = 0; t < n; ++t) {
        string v1, v2;
        int time;
        cin >> v1 >> v2 >> time;

        if (name_to_id.find(v1) == name_to_id.end()) {
            name_to_id[v1] = cnt;
            graph.id_to_name.push_back(v1);
            cnt++;
        }

        if (name_to_id.find(v2) == name_to_id.end()) {
            name_to_id[v2] = cnt;
            graph.id_to_name.push_back(v2);
            cnt++;
        }

        graph.guys[name_to_id[v1]].push_back(Record(name_to_id[v2], time));
    }

    graph.v = cnt;
    graph.findGangs(k);
    return 0;
}
