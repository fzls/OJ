/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-24 19:22:17
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1018. Public Bike Management (30)
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
There is a public bike service in Hangzhou City which provides great convenience to the tourists from all over the world. One may rent a bike at any station and return it to any other stations in the city.

The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations. A station is said to be in perfect condition if it is exactly half-full. If a station is full or empty, PBMC will collect or send bikes to adjust the condition of that station to perfect. And more, all the stations on the way will be adjusted as well.

When a problem station is reported, PBMC will always choose the shortest path to reach that station. If there are more than one shortest path, the one that requires the least number of bikes sent from PBMC will be chosen.


Figure 1
Figure 1 illustrates an example. The stations are represented by vertices and the roads correspond to the edges. The number on an edge is the time taken to reach one end station from another. The number written inside a vertex S is the current number of bikes stored at S. Given that the maximum capacity of each station is 10. To solve the problem at S3, we have 2 different shortest paths:

1. PBMC -> S1 -> S3. In this case, 4 bikes must be sent from PBMC, because we can collect 1 bike from S1 and then take 5 bikes to S3, so that both stations will be in perfect conditions.

2. PBMC -> S2 -> S3. This path requires the same time as path 1, but only 3 bikes sent from PBMC and hence is the one that will be chosen.

Input Specification:

Each input file contains one test case. For each case, the first line contains 4 numbers: Cmax (<= 100), always an even number, is the maximum capacity of each station; N (<= 500), the total number of stations; Sp, the index of the problem station (the stations are numbered from 1 to N, and PBMC is represented by the vertex 0); and M, the number of roads. The second line contains N non-negative numbers Ci (i=1,...N) where each Ci is the current number of bikes at Si respectively. Then M lines follow, each contains 3 numbers: Si, Sj, and Tij which describe the time Tij taken to move betwen stations Si and Sj. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print your results in one line. First output the number of bikes that PBMC must send. Then after one space, output the path in the format: 0->S1->...->Sp. Finally after another space, output the number of bikes that we must take back to PBMC after the condition of Sp is adjusted to perfect.

Note that if such a path is not unique, output the one that requires minimum number of bikes that we must take back to PBMC. The judge's data guarantee that such a path is unique.

Sample Input:
10 3 3 5
6 7 0
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
Sample Output:
3 0->2->3 0
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
const int INF = 0x7FFFFFFF;
struct Graph {
    int vertex, edge, capcity_max;
    vector<int> currentBikes;
    vector<vector<int>> time;
    vector<bool> labeled;
    Graph(int v, int e, int cm) : vertex{ v }, edge{ e }, capcity_max{ cm }, currentBikes(v + 1, 0), time(v + 1, vector<int>(v + 1, INF)), labeled(v + 1, false) {
    }

    void findPath(int destination);

    int findMinUnlabeled(vector<int> &shortest) {
        int index = 0;

        for (; labeled[index]; ++index)
            ;

        for (int i = index; i < shortest.size() && !labeled[i]; ++i) {
            if (shortest[i] < shortest[index]) {
                index = i;
            }
        }

        return index;
    }

    void printPath(vector<int> &path, int currV) {
        if (currV != 0) {
            printPath(path, path[currV]);
            cout << "->" << currV;
        } else {
            cout << currV;
        }
    }




};

int myAbs(int a) {
    return a >= 0 ? a : -a;
}

void Graph::findPath(int destination) {
    int source = 0;
    vector<int> shortest(vertex + 1, INF);
    vector<int> path(vertex + 1, 0);
    vector<int> take(vertex + 1, 0);
    vector<int> send(vertex + 1, 0);
    shortest[source] = 0;

    for (int t = 0; t < vertex; ++t) {
        //find min in the unlabeled
        int v = findMinUnlabeled(shortest);
        labeled[v] = true;

        //update unlabeled adjacent if necessary
        for (int i = 1; i <= vertex; ++i) {
            if (time[v][i] != INF && !labeled[i]) {
                if (shortest[v] + time[v][i] < shortest[i]) {
                    shortest[i] = shortest[v] + time[v][i];
                    int balance = currentBikes[i] - capcity_max / 2;

                    if(balance >= 0) {
                        take[i] = take[v] + balance;
                        send[i] = send[v];
                    } else {
                        if(take[v] + balance >= 0) {
                            take[i] = take[v] + balance;
                            send[i] = send[v];
                        } else {
                            take[i] = 0;
                            send[i] = send[v] - (take[v] + balance);
                        }
                    }

                    path[i] = v;
                } else if(shortest[v] + time[v][i] == shortest[i]) {
                    int send_tmp;
                    int take_tmp;
                    int balance = currentBikes[i] - capcity_max / 2;

                    if (balance >= 0) {
                        take_tmp = take[v] + balance;
                        send_tmp = send[v];
                    } else {
                        if (take[v] + balance >= 0) {
                            take_tmp = take[v] + balance;
                            send_tmp = send[v];
                        } else {
                            take_tmp = 0;
                            send_tmp = send[v] - (take[v] + balance);
                        }
                    }

                    if (send_tmp < send[i] || send_tmp == send[i] && take_tmp < take[i]) {
                        path[i] = v;
                        send[i] = send_tmp;
                        take[i] = take_tmp;
                    }
                }
            }
        }
    }

    cout << send[destination] << " ";
    printPath(path, destination);
    cout << " " << take[destination] << endl;
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
    int capcity_max, vertexs, destination, edges;
    cin >> capcity_max >> vertexs >> destination >> edges;
    Graph graph(vertexs, edges, capcity_max);

    for (int i = 1; i <= vertexs; ++i) {
        cin >> graph.currentBikes[i];
    }

    for (int i = 0; i < edges; ++i) {
        int v1, v2, t;
        cin >> v1 >> v2 >> t;
        graph.time[v1][v2] = t;
        graph.time[v2][v1] = t;
    }

    graph.findPath(destination);
    return 0;
}