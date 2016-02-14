/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-14 14:19:49
* @Description:  1011. A+B和C (15)
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
给定区间[-231, 231]内的3个整数A、B和C，请判断A+B是否大于C。

输入格式：

输入第1行给出正整数T(<=10)，是测试用例的个数。随后给出T组测试用例，每组占一行，顺序给出A、B和C。整数间以空格分隔。

输出格式：

对每组测试用例，在一行中输出“Case #X: true”如果A+B>C，否则输出“Case #X: false”，其中X是测试用例的编号（从1开始）。

输入样例：
4
1 2 3
2 3 4
2147483647 0 2147483646
0 -2147483648 -2147483647
输出样例：
Case #1: false
Case #2: true
Case #3: true
Case #4: false
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

bool larger(string left, string right) {
    bool isLeftMinus = left[0] == '-';
    bool isRightMinus = right[0] == '-';

    if (isLeftMinus && !isRightMinus || left == right) {
        return false;
    } else if (!isLeftMinus && isRightMinus) {
        return true;
    } else {
        int m = left.size();
        int n = right.size();

        if (m != n) {
            if (m > n) {
                if (!isLeftMinus) {
                    return true;
                } else {
                    return false;
                }
            } else {
                if (!isLeftMinus) {
                    return false;
                } else {
                    return true;
                }
            }
        } else {
            for (int i = 0; i < m; ++i)
                if (left[i] > right[i]) {
                    return !isLeftMinus ? true : false;
                } else if (left[i] < right[i]) {
                    return !isLeftMinus ? false : true;
                }

            return false;
        }
    }
}

string sum(string left, string right) {
    bool isLeftMinus = left[0] == '-';
    bool isRightMinus = right[0] == '-';
    string sum;
    int tmp, carry = 0;

    if (isLeftMinus && isRightMinus || !isLeftMinus && !isRightMinus) {
        auto m = left.size();
        auto n = right.size();
        int p = min(m, n);

        if (isLeftMinus) {
            p--;
            //去除负号，简化过程
            left.erase(0, 1);
            right.erase(0, 1);
        }

        auto i = left.rbegin(), j = right.rbegin();

        for (; p != 0; ++i, ++j, --p) {
            tmp = ((*i - '0') + (*j - '0') + carry) % 10;
            carry = ((*i - '0') + (*j - '0') + carry) / 10;
            sum.append(1, tmp + '0');
        }

        while (i != left.rend()) {
            tmp = ((*i - '0') + carry) % 10;
            carry = ((*i - '0') + carry) / 10;
            sum.append(1, tmp + '0');
            ++i;
        }

        while (j != right.rend()) {
            tmp = ((*j - '0') + carry) % 10;
            carry = ((*j - '0') + carry) / 10;
            sum.append(1, tmp + '0');
            ++j;
        }

        if (carry != 0) {
            sum.append(1, carry + '0');
        }

        for (int i = 0, j = sum.size() - 1; i < j; ++i, --j) {
            swap(sum[i], sum[j]);
        }

        if (isLeftMinus && isRightMinus) {
            sum.insert(0, "-");
        }
    } else {
        //if one is positive while other is negative
        bool isResultMinus = false;

        if (isLeftMinus) {
            swap(left, right);
        }

        right.erase(0, 1);

        if (!larger(left, right)) {
            swap(left, right);
            isResultMinus = true;
        }

        auto p = right.size();
        auto i = left.rbegin(), j = right.rbegin();

        for (; p != 0; ++i, ++j, --p) {
            tmp = ((*i - '0') - (*j - '0') + carry + 10) % 10;
            carry = ((*i - '0') - (*j - '0') + carry) >= 0 ? 0 : -1;
            sum.append(1, tmp + '0');
        }

        while (i != left.rend()) {
            tmp = ((*i - '0') + carry + 10) % 10;
            carry = ((*i - '0') + carry) >= 0 ? 0 : -1;
            sum.append(1, tmp + '0');
            ++i;
        }

        if (sum.back() == '0') {
            sum.pop_back();
        }

        for (int i = 0, j = sum.size() - 1; i < j; ++i, --j) {
            swap(sum[i], sum[j]);
        }

        if (isResultMinus) {
            sum.insert(0, "-");
        }
    }

    cout << sum << endl;
    return sum;
}


#pragma warning(disable:4996)
int main() {
    /*#pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion*/
    string a, b, c;
    int n;
    cin >> n;

    for (int test_case = 1; test_case <= n; ++test_case) {
    cin >> a >> b >> c;

    if (larger(sum(a, b), c)) {
    cout << "Case #" << test_case << ": true" << endl;
    } else {
    cout << "Case #" << test_case << ": false" << endl;
    }
    }

    return 0;
    }
