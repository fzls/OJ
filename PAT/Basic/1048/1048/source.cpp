/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-18 13:19:17
* @Description:  1048. 数字加密(20)
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
本题要求实现一种数字加密方法。首先固定一个加密用正整数A，对任一正整数B，将其每1位数字与A的对应位置上的数字进行以下运算：对奇数位，对应位的数字相加后对13取余——这里用J代表10、Q代表11、K代表12；对偶数位，用B的数字减去A的数字，若结果为负数，则再加10。这里令个位为第1位。

输入格式：

输入在一行中依次给出A和B，均为不超过100位的正整数，其间以空格分隔。

输出格式：

在一行中输出加密后的结果。

输入样例：
1234567 368782971
输出样例：
3695Q8118
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



char get_odd(char a, char b) {
    int result = (a - '0') + (b - '0');
    result %= 13;

    if (result == 10) {
        return 'J';
    }

    if (result == 11) {
        return 'Q';
    }

    if (result == 12) {
        return 'K';
    }

    return result + '0';
}

char get_even(char a, char b) {
    int result = b - a + 10;
    result %= 10;
    return result + '0';
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
    string a, b;
    cin >> a >> b;
    string result;
    auto i = a.rbegin(), j = b.rbegin();
    bool isOdd = true;
    int n = max(a.size(), b.size());

    for (int k = 0; k < n; ++k) {
        char _i = '0', _j = '0';

        if(k < a.size()) {
            _i = *i;
            ++i;
        }

        if(k < b.size()) {
            _j = *j;
            ++j;
        }

        if(isOdd) {
            result.insert(0, 1, get_odd(_i, _j));
        } else {
            result.insert(0, 1, get_even(_i, _j));
        }

        isOdd = !isOdd;
    }

    cout << result << endl;
    return 0;
}
