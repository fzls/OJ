/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:      v1.0
* @Time:         2016-02-19 14:17:03
* @Description:  1003. Emergency (25)
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
As an emergency rescue team leader of a city, you are given a special map of your country. The map shows several scattered cities connected by some roads. Amount of rescue teams in each city and the length of each road between any pair of cities are marked on the map. When there is an emergency call to you from some other city, your job is to lead your men to the place as quickly as possible, and at the mean time, call up as many hands on the way as possible.

Input

Each input file contains one test case. For each test case, the first line contains 4 positive integers: N (<= 500) - the number of cities (and the cities are numbered from 0 to N-1), M - the number of roads, C1 and C2 - the cities that you are currently in and that you must save, respectively. The next line contains N integers, where the i-th integer is the number of rescue teams in the i-th city. Then M lines follow, each describes a road with three integers c1, c2 and L, which are the pair of cities connected by a road and the length of that road, respectively. It is guaranteed that there exists at least one path from C1 to C2.

Output

For each test case, print in one line two numbers: the number of different shortest paths between C1 and C2, and the maximum amount of rescue teams you can possibly gather.
All the numbers in a line must be separated by exactly one space, and there is no extra space allowed at the end of a line.

Sample Input
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
Sample Output
2 4
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

const int INF = 0x7FFFFFFF;

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

    void findShortestPath(int currV, int desV) const;

    int find_min_unvisited(vector<int> min_d, vector<bool> labeled) const;


    vector<int> teams;
    vector<vector<int>> distance;
  private:
    int vertex, edge;
};

Graph::Graph(int v, int e) : vertex{ v }, edge{ e }, teams(v, 0), distance(v, vector<int>(v, INF)) {
}

Graph::~Graph() {
}

void Graph::findShortestPath(int currV, int desV) const {
    vector<bool> labeled(vertex, false);
    vector<int> min_d(vertex, INF);
    vector<int> max_t(vertex, 0);
    vector<int> min_n(vertex, 0);
    min_d[currV] = 0;
    max_t[currV] = teams[currV];
    min_n[currV] = 1;

    for (int i = 0; i < vertex; ++i) {
        //使用堆提升效率
        int min_index = find_min_unvisited(min_d, labeled);
        labeled[min_index] = true;

        for (int i = 0; i < vertex; ++i) {
            if(distance[min_index][i] != INF && !labeled[i]) { //find unlabeled sibling
                if(min_d[min_index] + distance[min_index][i] < min_d[i]) {
                    min_d[i] = min_d[min_index] + distance[min_index][i];
                    max_t[i] = max_t[min_index] + teams[i];
                    min_n[i] = min_n[min_index];
                } else if(min_d[min_index] + distance[min_index][i] == min_d[i]) {
                    if(max_t[min_index] + teams[i] > max_t[i]) {
                        max_t[i] = max_t[min_index] + teams[i];
                    }

                    min_n[i] += min_n[min_index];
                }
            }
        }
    }

    cout << min_n[desV] << " " << max_t[desV];
}

int Graph::find_min_unvisited(vector<int> min_d, vector<bool> labeled) const {
    //find first unlabeled
    int index = 0;

    while (labeled[index]) {
        ++index;
    }

    //find the min unlabeled
    for (int i = index; i < min_d.size(); ++i) {
        if (min_d[i] < min_d[index] && !labeled[i]) {
            index = i;
        }
    }

    return index;
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
    int v, e, currV, desV;
    cin >> v >> e >> currV >> desV;
    Graph graph(v, e);

    for (int i = 0; i < v; ++i) {
        cin >> graph.teams[i];
    }

    for (int i = 0; i < e; ++i) {
        int city1, city2, len;
        cin >> city1 >> city2 >> len;
        graph.distance[city1][city2] = len;
        graph.distance[city2][city1] = len;
    }

    graph.findShortestPath(currV, desV);
    return 0;
}
