/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-27 13:50:30
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1032. Sharing (25)
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
To store English words, one method is to use linked lists and store a word letter by letter. To save some space, we may let the words share the same sublist if they share the same suffix. For example, "loading" and "being" are stored as showed in Figure 1.


Figure 1
You are supposed to find the starting position of the common suffix (e.g. the position of "i" in Figure 1).

Input Specification:

Each input file contains one test case. For each case, the first line contains two addresses of nodes and a positive N (<= 105), where the two addresses are the addresses of the first nodes of the two words, and N is the total number of nodes. The address of a node is a 5-digit positive integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next

where Address is the position of the node, Data is the letter contained by this node which is an English letter chosen from {a-z, A-Z}, and Next is the position of the next node.

Output Specification:

For each case, simply output the 5-digit starting position of the common suffix. If the two words have no common suffix, output "-1" instead.

Sample Input 1:
11111 22222 9
67890 i 00002
00010 a 12345
00003 g -1
12345 D 67890
00002 n 00003
22222 B 23456
11111 L 00001
23456 e 67890
00001 o 00010
Sample Output 1:
67890
Sample Input 2:
00001 00002 4
00001 a 10001
10001 s -1
00002 a 10002
10002 t -1
Sample Output 2:
-1
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

struct Node {
    int address;
    char key;
    int next;
};



Node nodes[100000];
//bool visited[100000];
int str1[100000], str2[100000];
void getStr(int str1[], int h1, int &n1) {
    n1 = 0;

    while(h1 != -1) {
        str1[n1] = h1;
        n1++;
        h1 = nodes[h1].next;
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
    int h1, h2, n;
    cin >> h1 >> h2 >> n;

    while(n--) {
        Node tmp;
        cin >> tmp.address >> tmp.key >> tmp.next;
        nodes[tmp.address] = tmp;
    }

    int ch = -1;
    //    //see if some node occured in the first node and then appear in second
    //    memset(visited, false, sizeof(visited));
    //    while(h1 != -1) {
    //        visited[h1] = true;
    //        h1 = nodes[h1].next;
    //    }
    //
    //    while(h2 != -1) {
    //        if(visited[h2]) {
    //            ch = h2;
    //            break;
    //        }
    //
    //        h2 = nodes[h2].next;
    //    }
    //process
    int n1, n2;
    getStr(str1, h1, n1);
    getStr(str2, h2, n2);

    for (int i = n1 - 1, j = n2 - 1; i >= 0, j >= 0; --i, --j) {
        if (nodes[str1[i]].address == nodes[str2[j]].address) {
            ch = nodes[str1[i]].address;
        } else {
            break;
        }
    }

    //print common head
    if (ch == -1) {
        cout << "-1" << endl;
    } else {
        cout << setw(5) << setfill('0') << ch << endl;
    }

    return 0;
}
