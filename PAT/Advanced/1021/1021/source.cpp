/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-25 11:04:03
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1021. Deepest Root (25)
时间限制
1500 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
CHEN, Yue
A graph which is connected and acyclic can be considered a tree. The height of the tree depends on the selected root. Now you are supposed to find the root that results in a highest tree. Such a root is called the deepest root.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=10000) which is the number of nodes, and hence the nodes are numbered from 1 to N. Then N-1 lines follow, each describes an edge by given the two adjacent nodes' numbers.

Output Specification:

For each test case, print each of the deepest roots in a line. If such a root is not unique, print them in increasing order of their numbers. In case that the given graph is not a tree, print "Error: K components" where K is the number of connected components in the graph.

Sample Input 1:
5
1 2
1 3
1 4
2 5
Sample Output 1:
3
4
5
Sample Input 2:
5
1 3
1 4
2 5
3 4
Sample Output 2:
Error: 2 components
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

struct Graph {
    int vertex, edge;
    vector<list<int>> adjList;
    vector<bool> visited;
    Graph(int v = 0): vertex{v}, edge{0}, adjList(v + 1), visited(v + 1, false) {
    }

    void findRoot();

    void dfs(int v);
    void dfs(int v, int depth, int &max_depth);


};

void Graph::findRoot() {
    int components = 0;
    vector<bool> backup = visited;

    for (int i = 1; i <= vertex; ++i) {
        if (!visited[i]) {
            components++;
            dfs(i);
        }
    }

    if(components > 1) {
        cout << "Error: " << components << " components" << endl;
    } else {
        //find root
        vector<int> deepestRoots;
        int max_depth = 0;

        for (int i = 1; i <= vertex; ++i) {
            int depth = 0;
            visited = backup;
            dfs(i, 0, depth);

            if(depth > max_depth) {
                max_depth = depth;
                deepestRoots.clear();
                deepestRoots.push_back(i);
            } else if(depth == max_depth) {
                deepestRoots.push_back(i);
            }
        }

        //print
        for (auto root : deepestRoots) {
            cout << root << endl;
        }
    }
}

void Graph::dfs(int v) {
    visited[v] = true;

    for(auto adj : adjList[v]) {
        if (!visited[adj]) {
            dfs(adj);
        }
    }
}

void Graph::dfs(int v, int depth, int &max_depth) {
    visited[v] = true;

    if (depth > max_depth) {
        max_depth = depth;
    }

    for(auto adj : adjList[v]) {
        if (!visited[adj]) {
            dfs(adj, depth + 1, max_depth);
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
    int n;
    cin >> n;
    Graph graph(n);

    for (int i = 1; i <= n - 1; ++i) {
        int v1, v2;
        cin >> v1 >> v2;
        graph.adjList[v1].push_back(v2);
        graph.adjList[v2].push_back(v1);
        graph.edge++;
    }

    graph.findRoot();
    return 0;
}
