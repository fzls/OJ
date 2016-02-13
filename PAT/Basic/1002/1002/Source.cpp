/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-13 11:57:50
* @Description:  1002. 写出这个数 (20)
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
    读入一个自然数n，计算其各位数字之和，用汉语拼音写出和的每一位数字。

    输入格式：每个测试输入包含1个测试用例，即给出自然数n的值。这里保证n小于10100。

    输出格式：在一行内输出n的各位数字之和的每一位，拼音数字间有1 空格，但一行中最后一个拼音数字后没有空格。

    输入样例：
    1234567890987654321123456789
    输出样例：
    yi san wu

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

int sum(std::string number);

void voiceOfTheDigit(int digit);

void voice(int number);

int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    string number;
    cin >> number;
    voice(sum(number));
    return 0;
}



int sum(string number) {
    int temp_sum = 0;

    for (char digit : number) {
        temp_sum += (digit - '0');
    }

    return temp_sum;
}

void voiceOfTheDigit(int digit) {
    switch (digit) {
        case 0:
            cout << "ling";
            break;

        case 1:
            cout << "yi";
            break;

        case 2:
            cout << "er";
            break;

        case 3:
            cout << "san";
            break;

        case 4:
            cout << "si";
            break;

        case 5:
            cout << "wu";
            break;

        case 6:
            cout << "liu";
            break;

        case 7:
            cout << "qi";
            break;

        case 8:
            cout << "ba";
            break;

        case 9:
            cout << "jiu";
            break;

        default:
            break;
    }
}

void voice(int number) {
    if (number > 9) {
        voice(number / 10);
        cout << " ";
    }

    voiceOfTheDigit(number % 10);
}
