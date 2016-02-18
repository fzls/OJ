/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-17 22:26:52
* @Description:  1044. 火星数字(20)
时间限制
400 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
火星人是以13进制计数的：

地球人的0被火星人称为tret。
地球人数字1到12的火星文分别为：jan, feb, mar, apr, may, jun, jly, aug, sep, oct, nov, dec。
火星人将进位以后的12个高位数字分别称为：tam, hel, maa, huh, tou, kes, hei, elo, syy, lok, mer, jou。
例如地球人的数字“29”翻译成火星文就是“hel mar”；而火星文“elo nov”对应地球数字“115”。为了方便交流，请你编写程序实现地球和火星数字之间的互译。

输入格式：

输入第一行给出一个正整数N（<100），随后N行，每行给出一个[0, 169)区间内的数字 —— 或者是地球文，或者是火星文。

输出格式：

对应输入的每一行，在一行中输出翻译后的另一种语言的数字。

输入样例：
4
29
5
elo nov
tam
输出样例：
hel mar
may
115
13

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

enum Planet {
    EARTH,
    MARS
};


string gewei[] = { "tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec" };
string shiwei[] = { "tret", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou" };

Planet get_type(string line) {
    for(auto ch : line) {
        if(isdigit(ch)) {
            return EARTH;
        }
    }

    return MARS;
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
    string line;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        int s, g, digit, pos;

        switch (get_type(line)) {
            case EARTH:
                digit = atoi(line.data());
                s = digit / 13;
                g = digit % 13;

                if(s == 0) {
                    cout << gewei[g] << endl;
                } else {
                    cout << shiwei[s] ;

                    if(g != 0) {
                        cout << " " << gewei[g];
                    }

                    cout << endl;
                }

                break;

            case MARS:
                pos = line.find(' ');

                if(pos == -1) {
                    s = 0;

                    for (s = 0; s < 13; ++s) {
                        if (shiwei[s] == line) {
                            break;
                        }
                    }

                    if(s != 13) {
                        cout << s * 13 << endl;
                    } else {
                        for (g = 0; g < 13; ++g) {
                            if (gewei[g] == line) {
                                break;
                            }
                        }

                        cout << g << endl;
                    }
                } else {
                    string shiwei_s = line.substr(0, pos);
                    string gewei_s = line.substr(pos + 1);

                    for (s = 0; s < 13; ++s) {
                        if (shiwei[s] == shiwei_s) {
                            break;
                        }
                    }

                    for (g = 0; g < 13; ++g) {
                        if (gewei[g] == gewei_s) {
                            break;
                        }
                    }

                    cout << s * 13 + g << endl;
                }

                break;

            default:
                break;
        }
    }

    return 0;
}
