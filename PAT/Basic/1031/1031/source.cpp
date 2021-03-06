/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:
* @Time:         2016-02-16 21:15:51
* @Description:  1031. 查验身份证(15)
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
一个合法的身份证号码由17位地区、日期编号和顺序编号加1位校验码组成。校验码的计算规则如下：

首先对前17位数字加权求和，权重分配为：{7，9，10，5，8，4，2，1，6，3，7，9，10，5，8，4，2}；然后将计算的和对11取模得到值Z；最后按照以下关系对应Z值与校验码M的值：

Z：0 1 2 3 4 5 6 7 8 9 10
M：1 0 X 9 8 7 6 5 4 3 2

现在给定一些身份证号码，请你验证校验码的有效性，并输出有问题的号码。

输入格式：

输入第一行给出正整数N（<= 100）是输入的身份证号码的个数。随后N行，每行给出1个18位身份证号码。

输出格式：

按照输入的顺序每行输出1个有问题的身份证号码。这里并不检验前17位是否合理，只检查前17位是否全为数字且最后1位校验码计算准确。如果所有号码都正常，则输出“All passed”。

输入样例1：
4
320124198808240056
12010X198901011234
110108196711301866
37070419881216001X
输出样例1：
12010X198901011234
110108196711301866
37070419881216001X
输入样例2：
2
320124198808240056
110108196711301862
输出样例2：
All passed
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

int weights[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
char checkSumMap[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2', };

bool consist_of_digit_only(string id) {
    for (char digit : id)
        if (!(digit >= '0' && digit <= '9')) {
            return false;
        }

    return true;
}

char compute_check_sum(string id) {
    int checkSum = 0;

    for (int i = 0; i < id.size(); ++i) {
        checkSum += (id[i] - '0') * weights[i];
    }

    return checkSumMap[checkSum % 11];
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
    bool isAllPassed = true;
    string ID, ID_17;
    char checkSum;

    for (int i = 0; i < n; ++i) {
        cin >> ID;
        ID_17 = ID.substr(0, 17);
        checkSum = ID[17];

        if (!(consist_of_digit_only(ID_17) && compute_check_sum(ID_17) == checkSum)) {
            isAllPassed = false;
            cout << ID << endl;
        }
    }

    if (isAllPassed) {
        cout << "All passed" << endl;
    }

    return 0;
}
