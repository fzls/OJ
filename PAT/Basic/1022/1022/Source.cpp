/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-15 19:41:40
* @Description:  1022. D进制的A+B (20)
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
输入两个非负10进制整数A和B(<=230-1)，输出A+B的D (1 < D <= 10)进制数。

输入格式：

输入在一行中依次给出3个整数A、B和D。

输出格式：

输出A+B的D进制数。

输入样例：
123 456 8
输出样例：
1103
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



void print_in_d_digit(unsigned long long result, unsigned long long d) {
	string result_in_d;
	unsigned long long dividend = result, quotient, remainder;

	do {
		quotient = dividend / d;
		remainder = dividend % d;
		result_in_d.insert(0, 1, remainder + '0');
		dividend = quotient;
	} while (dividend != 0);

	cout << result_in_d;
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
	unsigned long long a, b, d, result;
	cin >> a >> b >> d;
	result = a + b;
	print_in_d_digit(result, d);
	return 0;
}
