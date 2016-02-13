/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-13 15:47:03
* @Description:  1004. 成绩排名 (20)
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
读入n名学生的姓名、学号、成绩，分别输出成绩最高和成绩最低学生的姓名和学号。

输入格式：每个测试输入包含1个测试用例，格式为

 第1行：正整数n
 第2行：第1个学生的姓名 学号 成绩
 第3行：第2个学生的姓名 学号 成绩
 ... ... ...
 第n+1行：第n个学生的姓名 学号 成绩
其中姓名和学号均为不超过10个字符的字符串，成绩为0到100之间的一个整数，这里保证在一组测试用例中没有两个学生的成绩是相同的。
输出格式：对每个测试用例输出2行，第1行是成绩最高学生的姓名和学号，第2行是成绩最低学生的姓名和学号，字符串间有1空格。

输入样例：
3
Joe Math990112 89
Mike CS991301 100
Mary EE990830 95
输出样例：
Mike CS991301
Joe Math990112
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

struct Student {
    string name;
    string number;
    int score;
};
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
    int min = 0, max = 0;
    vector<Student> students = vector<Student>(n);

    for (int i = 0; i < n; ++i) {
        cin >> students[i].name >> students[i].number >> students[i].score;

        if (students[i].score < students[min].score) {
            min = i;
        }

        if (students[i].score > students[max].score) {
            max = i;
        }
    }

    cout << students[max].name << " " << students[max].number << endl;
    cout << students[min].name << " " << students[min].number << endl;
    return 0;
}
