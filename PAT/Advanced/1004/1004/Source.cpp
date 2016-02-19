/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:      v1.0
* @Time:         2016-02-19 15:33:59
* @Description:  1004. Counting Leaves (30)
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
A family hierarchy is usually presented by a pedigree tree. Your job is to count those family members who have no child.
Input

Each input file contains one test case. Each case starts with a line containing 0 < N < 100, the number of nodes in a tree, and M (< N), the number of non-leaf nodes. Then M lines follow, each in the format:

ID K ID[1] ID[2] ... ID[K]
where ID is a two-digit number representing a given non-leaf node, K is the number of its children, followed by a sequence of two-digit ID's of its children. For the sake of simplicity, let us fix the root ID to be 01.
Output

For each test case, you are supposed to count those family members who have no child for every seniority level starting from the root. The numbers must be printed in a line, separated by a space, and there must be no extra space at the end of each line.

The sample case represents a tree with only 2 nodes, where 01 is the root and 02 is its only child. Hence on the root 01 level, there is 0 leaf node; and on the next level, there is 1 leaf node. Then we should output "0 1" in a line.

Sample Input
2 1
01 1 02
Sample Output
0 1
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

using namespace std;
#pragma region DebugSetting
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif
#pragma endregion
const int ROOT = 1;
const int START_LEVEL = 1;
vector<int> cnt(100, 0);
int max_level;
//count for 1,2,3,4 ....level  index start from 1

struct Node {
    vector<int> childs;
};

void count_leaf_this_level(vector<Node> &nodes, int node, int level) {
    /*if this is a leaf, inc the cnt and update max_level if necessary*/
    if(nodes[node].childs.empty()) {
        cnt[level]++;
        max_level = max(max_level, level);
        return;
    }

    /*else recurse to it's child*/
    for (int i = 0; i < nodes[node].childs.size(); ++i) {
        count_leaf_this_level(nodes, nodes[node].childs[i], level + 1);
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
    int total, nonLeaf;
    cin >> total >> nonLeaf;
    vector<Node> nodes(100);
    //index start from 1
    int id, k, tmp;

    for (int i = 0; i < nonLeaf; ++i) {
        cin >> id >> k;

        for (int j = 1; j <= k; ++j) {
            cin >> tmp;
            nodes[id].childs.push_back(tmp);
        }
    }

    count_leaf_this_level(nodes, ROOT, START_LEVEL);

    for (int i = 1; i <= max_level; ++i) {
        if(i != 1) {
            cout << " ";
        }

        cout << cnt[i];
    }

    return 0;
}
