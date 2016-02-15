/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-15 01:25:44
* @Description:  1014. 福尔摩斯的约会 (20)
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
大侦探福尔摩斯接到一张奇怪的字条：“我们约会吧！ 3485djDkxh4hhGE 2984akDfkkkkggEdsb s&hgsfdk d&Hyscvnm”。大侦探很快就明白了，字条上奇怪的乱码实际上就是约会的时间“星期四 14:04”，因为前面两字符串中第1对相同的大写英文字母（大小写有区分）是第4个字母'D'，代表星期四；第2对相同的字符是'E'，那是第5个英文字母，代表一天里的第14个钟头（于是一天的0点到23点由数字0到9、以及大写字母A到N表示）；后面两字符串第1对相同的英文字母's'出现在第4个位置（从0开始计数）上，代表第4分钟。现给定两对字符串，请帮助福尔摩斯解码得到约会的时间。

输入格式：

输入在4行中分别给出4个非空、不包含空格、且长度不超过60的字符串。

输出格式：

在一行中输出约会的时间，格式为“DAY HH:MM”，其中“DAY”是某星期的3字符缩写，即MON表示星期一，TUE表示星期二，WED表示星期三，THU表示星期四，FRI表示星期五，SAT表示星期六，SUN表示星期日。题目输入保证每个测试存在唯一解。

输入样例：
3485djDkxh4hhGE
2984akDfkkkkggEdsb
s&hgsfdk
d&Hyscvnm
输出样例：
THU 14:04
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
#include <iomanip>
using namespace std;

string weekday[] = {
	"MON",
	"TUE",
	"WED",
	"THU",
	"FRI",
	"SAT",
	"SUN",
};

bool isSameUpperCaseLetter(char first, char second) {
	return first == second && first >= 'A' && first <= 'G';
}

bool isSameChar(char first, char second) {
	return first == second && (first >= '0' && first <= '9' || first >= 'A' && first <= 'N');
}

int getHour(char first) {
	if (first >= '0' && first <= '9') {
		return first - '0';
	}

	if (first >= 'A' && first <= 'N') {
		return first - 'A' + 10;
	}
}

void getWeekdayAndHour(string str3, string str4) {
	int n = min(str3.size(), str4.size());
	int i = 0;

	//weekday
	for (; i < n; ++i) {
		if (isSameUpperCaseLetter(str3[i], str4[i])) {
			cout << weekday[str3[i] - 'A'] << " " ;
			++i;
			break;
		}
	}

	//hour
	for (; i < n; ++i) {
		if (isSameChar(str3[i], str4[i])) {
			cout << setw(2) << setfill('0') << getHour(str3[i]);
			break;
		}
	}

	cout << ":";
}

bool isSameLetter(char first, char second) {
	return first == second && (first >= 'a' && first <= 'z' || first >= 'A' && first <= 'Z');
}

void getMinute(string str3, string str4) {
	int n = min(str3.size(), str4.size());

	for (int i = 0; i < n; ++i) {
		if (isSameLetter(str3[i], str4[i])) {
			cout << setw(2) << setfill('0') << i;
			break;
		}
	}
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
	string str1, str2, str3, str4;
	cin >> str1 >> str2 >> str3 >> str4;
	getWeekdayAndHour(str1, str2);
	getMinute(str3, str4);
	return 0;
}
