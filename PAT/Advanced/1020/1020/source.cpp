/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-25 10:19:59
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1020. Tree Traversals (25)
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
Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<=30), the total number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder sequence. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding binary tree. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
Sample Output:
4 1 6 3 5 7 2
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
vector<int> post, in;
struct Node {
    int key;
    Node *left;
    Node *right;
    Node(int k = 0, Node *l = NULL, Node *r = NULL): key{k}, left{l}, right{r} {}
};
typedef Node *Tree;

void visit(bool &isFirst, Tree node) {
    if(!isFirst) {
        cout << " ";
    } else {
        isFirst = false;
    }

    cout << node->key;
}

void buildTree(int pl, int pr, int il, int ir, Tree &root) {
    if (pl > pr || ir > ir) {
        return;
    }

    if (root == NULL) {
        root = new Node;
    }

    root->key = post[pr];
    int root_in = il;

    for (; root_in <= ir && !(in[root_in] == post[pr]); ++root_in)
        ;

    debug("%d:%d:%d:%d\n", pl, pl + root_in - il - 1, il, root_in - 1);
    buildTree(pl, pl + root_in - il - 1, il, root_in - 1, root->left);
    debug("%d:%d:%d:%d\n", pl + root_in - il, pr - 1, root_in + 1, ir);
    buildTree(pl + root_in - il, pr - 1, root_in + 1, ir, root->right);
}

void levelOrder(const Tree &root) {
    if (root == NULL) {
        return;
    }

    queue<Tree> nodes;
    nodes.push(root);
    bool isFirst = true;

    while(!nodes.empty()) {
        Tree node = nodes.front(); nodes.pop();
        visit(isFirst, node);

        if (node->left != NULL) {
            nodes.push(node->left);
        }

        if (node->right != NULL) {
            nodes.push(node->right);
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
    post.resize(n);
    in.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> post[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> in[i];
    }

    Tree root = NULL;
    buildTree(0, n - 1, 0, n - 1, root);
    levelOrder(root);
    return 0;
}
