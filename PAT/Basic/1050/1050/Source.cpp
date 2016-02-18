/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:      v1.0
* @Time:         2016-02-18 15:44:23
* @Description:  1050. 螺旋矩阵(25)
时间限制
150 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
本题要求将给定的N个正整数按非递增的顺序，填入“螺旋矩阵”。所谓“螺旋矩阵”，是指从左上角第1个格子开始，按顺时针螺旋方向填充。要求矩阵的规模为m行n列，满足条件：m*n等于N；m>=n；且m-n取所有可能值中的最小值。

输入格式：

输入在第1行中给出一个正整数N，第2行给出N个待填充的正整数。所有数字不超过104，相邻数字以空格分隔。

输出格式：

输出螺旋矩阵。每行n个数字，共m行。相邻数字以1个空格分隔，行末不得有多余空格。

输入样例：
12
37 76 20 98 76 42 53 95 60 81 58 93
输出样例：
98 95 93
42 37 81
53 20 76
58 60 76
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
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif

enum Dir {
    UPPER,
    DOWN,
    LEFT,
    RIGHT
};

void print(vector<int> num, int m, int n) {
    auto map = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    int i, j;

    for (i = 1, j = 1; j <= n; ++j) {
        map[i][j] = j;
    }

    --j;
    Dir direction = DOWN;
    int hight = m, width = n, currentPositionInNum = n;
    int numOfVisited = n;

    while(hight > 0 || width > 0) {
        if(numOfVisited == m * n) {
            break;
        }

        switch (direction) {
            case UPPER:
                --hight;

                for (int cnt = 0; cnt < hight; ++cnt) {
                    --i;
                    ++currentPositionInNum;
                    ++numOfVisited;
                    map[i][j] = currentPositionInNum;
                }

                direction = RIGHT;
                break;

            case DOWN:
                --hight;

                for (int cnt = 0; cnt < hight; ++cnt) {
                    ++i;
                    ++currentPositionInNum;
                    ++numOfVisited;
                    map[i][j] = currentPositionInNum;
                }

                direction = LEFT;
                break;

            case LEFT:
                --width;

                for (int cnt = 0; cnt < width; ++cnt) {
                    --j;
                    ++currentPositionInNum;
                    ++numOfVisited;
                    map[i][j] = currentPositionInNum;
                }

                direction = UPPER;
                break;

            case RIGHT:
                --width;

                for (int cnt = 0; cnt < width; ++cnt) {
                    ++j;
                    ++currentPositionInNum;
                    ++numOfVisited;
                    map[i][j] = currentPositionInNum;
                }

                direction = DOWN;
                break;

            default:
                break;
        }
    }

    //print

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j != 1) {
                cout << " ";
            }

            cout << num[map[i][j]];
        }

        cout << endl;
    }
}

void compute(int &m, int &n, int N) {
    m = sqrt(N);

    while (N % m != 0) {
        ++m;
    }

    n = N / m;

    if (m < n) {
        swap(m, n);
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
    int N;
    cin >> N;
    int m, n;
    compute(m, n, N);
    vector<int> num(N + 1, 0x7FFFFFFF);

    for (int i = 1; i <= N; ++i) {
        cin >> num[i];
    }

    sort(num.begin(), num.end(), greater<int>());
    print(num, m, n);
    return 0;
}
