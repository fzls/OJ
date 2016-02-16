/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-16 11:39:04
* @Description:  1024. 科学计数法 (20)
时间限制
100 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
HOU, Qiming
科学计数法是科学家用来表示很大或很小的数字的一种方便的方法，其满足正则表达式[+-][1-9]"."[0-9]+E[+-][0-9]+，即数字的整数部分只有1位，小数部分至少有1位，该数字及其指数部分的正负号即使对正数也必定明确给出。

现以科学计数法的格式给出实数A，请编写程序按普通数字表示法输出A，并保证所有有效位都被保留。

输入格式：

每个输入包含1个测试用例，即一个以科学计数法表示的实数A。该数字的存储长度不超过9999字节，且其指数的绝对值不超过9999。

输出格式：

对每个测试用例，在一行中按普通数字表示法输出A，并保证所有有效位都被保留，包括末尾的0。

输入样例1：
+1.23400E-03
输出样例1：
0.00123400
输入样例2：
-1.2E+10
输出样例2：
-12000000000
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



string convert(string n_sic) {
    char sign_l = n_sic[0];
    auto e_pos = n_sic.find('E');
    string digit = n_sic.substr(1, e_pos - 1);
    char sign_r = n_sic[e_pos + 1];
    string expo = n_sic.substr(e_pos + 2);
    int k = atoi(expo.data());
    //delete '.'
    digit.erase(1, 1);

    if(sign_r == '-') {
        //move left
        //add k-1 to the left
        digit.insert(0, k - 1, '0');
        //add "0." to the left
        digit.insert(0, "0.");
    } else {
        // move right
        int numberOfDigitsToTheRightOfDot = digit.size() - 1;

        if(numberOfDigitsToTheRightOfDot > k) {
            // if '.' is still needed
            digit.insert(k + 1, 1, '.');
        } else {
            digit.append(k - numberOfDigitsToTheRightOfDot, '0');
        }
    }

    if (sign_l == '-') {
        digit.insert(0, "-");
    }

    return digit;
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
    string n_sic;
    cin >> n_sic;
    cout << convert(n_sic);
    return 0;
}
