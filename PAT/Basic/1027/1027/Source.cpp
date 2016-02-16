/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-16 18:19:37
* @Description:  1027. 打印沙漏(20)
时间限制
200 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
本题要求你写个程序把给定的符号打印成沙漏的形状。例如给定17个“*”，要求按下列格式打印

*****
***
 *
***
*****
所谓“沙漏形状”，是指每行输出奇数个符号；各行符号中心对齐；相邻两行符号数差2；符号数先从大到小顺序递减到1，再从小到大顺序递增；首尾符号数相等。

给定任意N个符号，不一定能正好组成一个沙漏。要求打印出的沙漏能用掉尽可能多的符号。

输入格式：

输入在一行给出1个正整数N（<=1000）和一个符号，中间以空格分隔。

输出格式：

首先打印出由给定符号组成的最大的沙漏形状，最后在一行中输出剩下没用掉的符号数。

输入样例：
19 *
输出样例：
*****
***
 *
***
*****
2
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
#include <vector>

using namespace std;



int get_order(const int n) {
    int cnt = -1;
    int order = 0;
    int k = 1;

    while(cnt <= n) {
        cnt += 2 * k;
        k += 2;
        ++order;
    }

    --order;
    return order;
}

void print_line(int chars, int blanks, char symbol) {
    string line;
    line.append(blanks, ' ');
    line.append(chars, symbol);
    //line.append(blanks, ' ');
    line.append("\n");
    cout << line;
}

void printInHourglassForm(int order, char symbol) {
    //upper order to 1
    for (int i = order; i > 0; --i) {
        print_line(2 * i - 1, order - i, symbol);
    }

    //lower 2 to order
    for (int i = 2; i <= order; ++i) {
        print_line(2 * i - 1, order - i, symbol);
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
    char symbol;
    cin >> n >> symbol;
    int order, unused;
    order = get_order(n);
    unused = n - 2 * order * order + 1;
    printInHourglassForm(order, symbol);
    cout << unused;
    return 0;
}
