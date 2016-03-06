/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-03-06 18:34:29
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1043. Is It a Binary Search Tree (25)
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
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
If we swap the left and right subtrees of every node, then the resulting tree is called the Mirror Image of a BST.

Now given a sequence of integer keys, you are supposed to tell if it is the preorder traversal sequence of a BST or the mirror image of a BST.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=1000). Then N integer keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:

For each test case, first print in a line "YES" if the sequence is the preorder traversal sequence of a BST or the mirror image of a BST, or "NO" if not. Then if the answer is "YES", print in the next line the postorder traversal sequence of that tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
7
8 6 5 7 10 8 11
Sample Output 1:
YES
5 7 6 8 11 10 8
Sample Input 2:
7
8 10 11 8 6 7 5
Sample Output 2:
YES
11 8 10 7 5 6 8
Sample Input 3:
7
8 6 8 5 10 9 11
Sample Output 3:
NO
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
vector<int> nodes;
bool cmp(int a, int b) {
    return nodes[a] < nodes[b];
}

bool cmp_M(int a, int b) {
    return !cmp(a, b);
}
bool checkRight(int l, int r, int key, bool(*cmp)(int, int)) {
    for (int i = l; i <= r; ++i)
        if (cmp(i, key)) {
            return false;
        }

    return true;
}

bool checkBST(int l, int r, bool(*cmp)(int, int)) {
    if (l >= r) {
        return true;
    }

    int rl = l + 1;

    while (rl <= r && cmp(rl, l)) {
        rl++;
    }

    if (!checkRight(rl, r, l, cmp)) {
        return false;
    } else {
        return checkBST(l + 1, rl - 1, cmp) && checkBST(rl, r, cmp);
    }
}

void postBST(int l, int r, bool (*cmp)(int, int)) {
    if (l > r) {
        return;
    }

    int rl = l + 1;

    while (rl <= r && cmp(rl, l)) {
        rl++;
    }

    postBST(l + 1, rl - 1, cmp);
    postBST(rl, r, cmp);
    cout << nodes[l];

    if (l != 0) {
        cout << " ";
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
    nodes.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> nodes[i];
    }

    if(checkBST(0, n - 1, cmp)) {//BST
        cout << "YES" << endl;
        postBST(0, n - 1, cmp);
    } else if(checkBST(0, n - 1, cmp_M)) {//Mirror
        cout << "YES" << endl;
        postBST(0, n - 1, cmp_M);
    } else {//Neither
        cout << "NO" << endl;
    }

    return 0;
}
