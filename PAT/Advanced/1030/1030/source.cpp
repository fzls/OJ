/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-26 19:41:26
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1030. Travel Plan (30)
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
A traveler's map gives the distances between cities along the highways, together with the cost of each highway. Now you are supposed to write a program to help a traveler to decide the shortest path between his/her starting city and the destination. If such a shortest path is not unique, you are supposed to output the one with the minimum cost, which is guaranteed to be unique.

Input Specification:

Each input file contains one test case. Each case starts with a line containing 4 positive integers N, M, S, and D, where N (<=500) is the number of cities (and hence the cities are numbered from 0 to N-1); M is the number of highways; S and D are the starting and the destination cities, respectively. Then M lines follow, each provides the information of a highway, in the format:

City1 City2 Distance Cost

where the numbers are all integers no more than 500, and are separated by a space.

Output Specification:

For each test case, print in one line the cities along the shortest path from the starting point to the destination, followed by the total distance and the total cost of the path. The numbers must be separated by a space and there must be no extra space at the end of output.

Sample Input
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
Sample Output
0 2 3 3 40
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

struct Adjacent {
    int city;
    int distance;
    int cost;

    Adjacent(int c, int d, int ct)
        : city(c),
          distance(d),
          cost(ct) {
    }
};

struct City {
    int vertex, edge;
    vector<list<Adjacent>> citys;//0~v-1

    City(int v, int e)
        : vertex(v),
          edge(e),
          citys(v) {
    }

    void find_Shortest_Path_With_Min_Cost_And_Print(int s, int d);

    void print_path(int cv, vector<int> &path, int source);


};

void City::find_Shortest_Path_With_Min_Cost_And_Print(int source, int destination) {
    vector<int> min_dis(vertex, INF >> 2);
    vector<int> min_cost(vertex, INF >> 2);
    vector<int> path(vertex, INF >> 2);
    vector<bool> labeled(vertex, false);
    //init
    min_dis[source] = 0;
    min_cost[source] = 0;
    path[source] = source;
    //?using heap to get min
    vector<int> remaining;

    for (int i = 0; i < vertex; ++i) {
        remaining.push_back(i);
    }

    auto cmp = [&](int a, int b) { return min_dis[a] > min_dis[b]; };
    make_heap(remaining.begin(), remaining.end(), cmp);

    for (int i = 0; i < vertex; ++i) {
        //find min dis in unlabeled
        int v = remaining[0];
        pop_heap(remaining.begin(), remaining.end(), cmp);
        remaining.pop_back();
        //label this city
        labeled[v] = true;

        //update unlabeled adj if any
        for (auto &adj : citys[v]) {
            int nc = adj.city;

            if (labeled[nc]) { //ignore labeled one
                continue;
            }

            int dis = min_dis[v] + adj.distance;
            int cost = min_cost[v] + adj.cost;

            if (dis < min_dis[nc]) {
                min_dis[nc] = dis;
                min_cost[nc] = cost;
                path[nc] = v;
            } else if (dis == min_dis[nc] && cost < min_cost[nc]) {
                min_cost[nc] = cost;
                path[nc] = v;
            }
        }

        //after update, resume heap proprity
        make_heap(remaining.begin(), remaining.end(), cmp);
    }

    print_path(destination, path, source);
    cout << min_dis[destination] << " " << min_cost[destination] << endl;
}

void City::print_path(int cv, vector<int> &path, int source) {
    if (cv != source) {
        print_path(path[cv], path, source);
    }

    cout << cv << " ";
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
    int v, e, s, d;
    cin >> v >> e >> s >> d;
    City city(v, e);

    //?+try to use adj list
    for (int i = 0; i < e; ++i) {
        int c1, c2, dis, cost;
        cin >> c1 >> c2 >> dis >> cost;
        city.citys[c1].push_back(Adjacent(c2, dis, cost));
        city.citys[c2].push_back(Adjacent(c1, dis, cost));
    }

    city.find_Shortest_Path_With_Min_Cost_And_Print(s, d);
    return 0;
}


//struct City {
//    int vertex, edge;
//    vector<vector<int>> distance;//0~v-1
//    vector<vector<int>> cost;
//    City(int v, int e)
//        : vertex(v),
//          edge(e),
//          distance(v, vector<int>(v, INF)),
//          cost(v, vector<int>(v, INF)) {
//    }
//
//    void find_Shortest_Path_With_Min_Cost_And_Print(int s, int d);
//
//    int find_min_dis_unlabeled(vector<int> &min_dis, vector<bool> &labeld);
//
//    void print_path(int cv, vector<int> &path, int source);
//
//
//};
//
//void City::find_Shortest_Path_With_Min_Cost_And_Print(int source, int destination) {
//    vector<int> min_dis(vertex, INF);
//    vector<int> min_cost(vertex, INF);
//    vector<int> path(vertex, 0);
//    vector<bool> labeld(vertex, false);
//    //init
//    min_dis[source] = 0;
//    min_cost[source] = 0;
//
//    for (int t = 0; t < vertex; ++t) {
//        //find min dis in unlabeled
//        int v = find_min_dis_unlabeled(min_dis, labeld);
//        //label this city
//        labeld[v] = true;
//
//        //update unlabeled adj if any
//        for (int i = 0; i < vertex; ++i) {
//            if(distance[v][i] == INF || labeld[i]) {
//                continue;
//            }
//
//            int dis = min_dis[v] + distance[v][i];
//            int cos = min_cost[v] + cost[v][i];
//
//            if (dis < min_dis[i]) {
//                min_dis[i] = dis;
//                min_cost[i] = cos;
//                path[i] = v;
//            } else if (dis == min_dis[i] && cos < min_cost[i]) {
//                min_cost[i] = cos;
//                path[i] = v;
//            }
//        }
//    }
//
//    print_path(destination, path, source);
//    cout << min_dis[destination] << " " << min_cost[destination] << endl;
//}
//
//int City::find_min_dis_unlabeled(vector<int> &min_dis, vector<bool> &labeld) {
//    int idx = 0;
//
//    for (; labeld[idx]; ++idx)
//        ;
//
//    for (int i = idx + 1; i < vertex; ++i) {
//        if (min_dis[i] < min_dis[idx]) {
//            idx = i;
//        }
//    }
//
//    return idx;
//}
//
//void City::print_path(int cv, vector<int> &path, int source) {
//    if (cv != source) {
//        print_path(path[cv], path, source);
//    }
//
//    cout << cv << " ";
//}
//
//int main() {
//    #pragma region GET_INPUT
//    {
//        #ifndef ONLINE_JUDGE
//        freopen("test.in", "r", stdin);
//        freopen("test.out", "w", stdout);
//        #endif
//    }
//    #pragma endregion
//    int v, e, s, d;
//    cin >> v >> e >> s >> d;
//    City city(v, e);
//
//    for (int i = 0; i < e; ++i) {
//        int c1, c2, dis, cost;
//        cin >> c1 >> c2 >> dis >> cost;
//        city.distance[c1][c2] = city.distance[c2][c1] = dis;
//        city.cost[c1][c2] = city.cost[c2][c1] = cost;
//    }
//
//    city.find_Shortest_Path_With_Min_Cost_And_Print(s, d);
//    return 0;
//}
