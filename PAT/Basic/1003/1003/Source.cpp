/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-13 14:54:35
* @Description:  1003. 我要通过！(20)
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
“答案正确”是自动判题系统给出的最令人欢喜的回复。本题属于PAT的“答案正确”大派送 —— 只要读入的字符串满足下列条件，系统就输出“答案正确”，否则输出“答案错误”。

得到“答案正确”的条件是：

1. 字符串中必须仅有P, A, T这三种字符，不可以包含其它字符；
2. 任意形如 xPATx 的字符串都可以获得“答案正确”，其中 x 或者是空字符串，或者是仅由字母 A 组成的字符串；
3. 如果 aPbTc 是正确的，那么 aPbATca 也是正确的，其中 a, b, c 均或者是空字符串，或者是仅由字母 A 组成的字符串。

现在就请你为PAT写一个自动裁判程序，判定哪些字符串是可以获得“答案正确”的。
输入格式： 每个测试输入包含1个测试用例。第1行给出一个自然数n (<10)，是需要检测的字符串个数。接下来每个字符串占一行，字符串长度不超过100，且不包含空格。

输出格式：每个字符串的检测结果占一行，如果该字符串可以获得“答案正确”，则输出YES，否则输出NO。

输入样例：
8
PAT
PAAT
AAPATAA
AAPAATAAAA
xPATx
PT
Whatever
APAAATAA
输出样例：
YES
YES
YES
YES
NO
NO
NO
NO
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



bool containOnlyOne(string str, char ch) {
    int cnt = 0;

    for (char c : str)
        if (c == ch) {
            ++cnt;
        }

    return cnt == 1;
}

bool containOtherChar(string str) {
    for (char c : str) {
        if (!(c == 'P' || c == 'A' || c == 'T')) {
            return true;
        }
    }

    return false;
}

bool isValid(string input_case) {
    if (!containOnlyOne(input_case, 'P') ||
            !containOnlyOne(input_case, 'T') ||
            containOtherChar(input_case) ) {
        return false;
    }

    //now the input is sure to be consist of only one P and one T and maybe more than one A
    int pos_P = input_case.find('P');
    int pos_T = input_case.find('T');
    int size = input_case.size();
    int left = pos_P;
    int center = pos_T - pos_P - 1;
    int right = size - pos_T - 1;
    //cout << left << " " << center << " " << right << " " << pos_P << " " << pos_T << endl;
    return left * (center - 1) == right - left && center >= 1;
}
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
    int n;
    cin >> n;

    while (n--) {
        string input_case;
        cin >> input_case;

        if (isValid(input_case)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
