/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-21 17:32:59
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1013. Battle Over Cities (25)
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
It is vitally important to have all the cities connected by highways in a war. If a city is occupied by the enemy, all the highways from/toward that city are closed. We must know immediately if we need to repair any other highways to keep the rest of the cities connected. Given the map of cities which have all the remaining highways marked, you are supposed to tell the number of highways need to be repaired, quickly.

For example, if we have 3 cities and 2 highways connecting city1-city2 and city1-city3. Then if city1 is occupied by the enemy, we must have 1 highway repaired, that is the highway city2-city3.

Input

Each input file contains one test case. Each case starts with a line containing 3 numbers N (<1000), M and K, which are the total number of cities, the number of remaining highways, and the number of cities to be checked, respectively. Then M lines follow, each describes a highway by 2 integers, which are the numbers of the cities the highway connects. The cities are numbered from 1 to N. Finally there is a line containing K numbers, which represent the cities we concern.

Output

For each of the K cities, output in a line the number of highways need to be repaired if that city is lost.

Sample Input
3 2 3
1 2
1 3
1 2 3
Sample Output
1
0
0
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

class Graph {
  public:
    Graph(int v = 0, int e = 0);
    ~Graph();

    int getConnectedParts();

    void dfs(int i);

    void bfs(int i);


    vector<vector<bool>> roads;
  private:
    int mVertex, mEdge;
    vector<bool> visited;

};

Graph::Graph(int v, int e) : roads(v + 1, vector<bool>(v + 1, false)) , mVertex{ v }, mEdge{ e }, visited(v + 1, false) {
}

Graph::~Graph() {
}

int Graph::getConnectedParts() {
    int parts = 0;

    //dfs
    for (int i = 1; i <= mVertex; ++i)
        if (!visited[i]) {
            dfs(i);
            parts++;
        }

    //bfs
    //    for (int i = 1; i <= mVertex; ++i) {
    //        if (!visited[i]) {
    //            bfs(i);
    //            parts++;
    //        }
    //    }
    return parts;
}

void Graph::dfs(int vertex) {
    if(!visited[vertex]) {
        visited[vertex] = true;

        for (int nv = 1; nv <= mVertex; ++nv) {
            if(roads[vertex][nv]) {
                dfs(nv);
            }
        }
    }
}

void Graph::bfs(int vertex) {
    queue<int> Q;
    Q.push(vertex);

    while(!Q.empty()) {
        int v = Q.front(); Q.pop();
        visited[v] = true;

        for (int i = 1; i <= mVertex; ++i) {
            if (!visited[i] && roads[v][i]) {
                Q.push(i);
            }
        }
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
    int v, e, k;
    cin >> v >> e >> k;
    Graph citys(v, e);

    //index 1...n
    for (int i = 0; i < e; ++i) {
        int city1, city2;
        cin >> city1 >> city2;
        citys.roads[city1][city2] = true;
        citys.roads[city2][city1] = true;
    }

    Graph backup;

    for (int t = 0; t < k; ++t) {
        int lost_city;
        cin >> lost_city;
        //backup
        backup = citys;

        //remove this city
        for (int i = 1; i <= v; ++i) {
            citys.roads[lost_city][i] = false;
            citys.roads[i][lost_city] = false;
        }

        //compute connected parts
        cout << citys.getConnectedParts() - 2 << endl;
        //restore
        citys = backup;
    }

    return 0;
}
