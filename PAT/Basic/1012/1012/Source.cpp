/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-14 16:39:36
* @Description:  1012. 数字分类 (20)
时间限制
100 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
给定一系列正整数，请按要求对数字进行分类，并输出以下5个数字：

A1 = 能被5整除的数字中所有偶数的和；
A2 = 将被5除后余1的数字按给出顺序进行交错求和，即计算n1-n2+n3-n4...；
A3 = 被5除后余2的数字的个数；
A4 = 被5除后余3的数字的平均数，精确到小数点后1位；
A5 = 被5除后余4的数字中最大数字。
输入格式：

每个输入包含1个测试用例。每个测试用例先给出一个不超过1000的正整数N，随后给出N个不超过1000的待分类的正整数。数字间以空格分隔。

输出格式：

对给定的N个正整数，按题目要求计算A1~A5并在一行中顺序输出。数字间以空格分隔，但行末不得有多余空格。

若其中某一类数字不存在，则在相应位置输出“N”。

输入样例1：
13 1 2 3 4 5 6 7 8 9 10 20 16 18
输出样例1：
30 11 2 9.7 9
输入样例2：
8 1 2 4 5 6 7 9 16
输出样例2：
N 11 2 N 9
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
#pragma warning(disable:4996)

int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    int n, a1 = 0, a2 = 0, a3 = 0, a4_sum = 0, a4_n = 0, a5 = 0, number, sign = 1,
           remainder;
    bool flag1 = false, flag2 = false, flag3 = false, flag4 = false, flag5 = false;
    cin >> n;

    while (n--) {
        cin >> number;
        remainder = number % 5;

        switch (remainder) {
            case 0:
                if (number % 2 == 0) {
                    a1 += number;
                    flag1 = true;
                }

                break;

            case 1:
                a2 += sign * number;
                sign = -sign;
                flag2 = true;
                break;

            case 2:
                a3++;
                flag3 = true;
                break;

            case 3:
                a4_n++;
                a4_sum += number;
                flag4 = true;
                break;

            case 4:
                if (number > a5) {
                    a5 = number;
                    flag5 = true;
                }

                break;

            default:
                break;
        }
    }

    if (!flag1) {
        cout << "N ";
    } else {
        cout << a1 << " ";
    }

    if (!flag2) {
        cout << "N ";
    } else {
        cout << a2 << " ";
    }

    if (!flag3) {
        cout << "N ";
    } else {
        cout << a3 << " ";
    }

    if (!flag4) {
        cout << "N ";
    } else {
        printf("%.1f ", 1.0 * a4_sum / a4_n);
    }

    if (!flag5) {
        cout << "N";
    } else {
        cout << a5 ;
    }

    return 0;
}
