/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-28 21:15:52
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1036. Boys vs Girls (25)
时间限制
400 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
CHEN, Yue
This time you are asked to tell the difference between the lowest grade of all the male students and the highest grade of all the female students.

Input Specification:

Each input file contains one test case. Each case contains a positive integer N, followed by N lines of student information. Each line contains a student's name, gender, ID and grade, separated by a space, where name and ID are strings of no more than 10 characters with no space, gender is either F (female) or M (male), and grade is an integer between 0 and 100. It is guaranteed that all the grades are distinct.

Output Specification:

For each test case, output in 3 lines. The first line gives the name and ID of the female student with the highest grade, and the second line gives that of the male student with the lowest grade. The third line gives the difference gradeF-gradeM. If one such kind of student is missing, output "Absent" in the corresponding line, and output "NA" in the third line instead.

Sample Input 1:

3
Joe M Math990112 89
Mike M CS991301 100
Mary F EE990830 95
Sample Output 1:
Mary EE990830
Joe Math990112
6
Sample Input 2:
1
Jean M AA980920 60
Sample Output 2:
Absent
Jean AA980920
NA
提交代码
*
+----------------------------------------------------------
*/
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:66777216")

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
#pragma region DebugSetting
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif
#pragma endregion

const int INF = 0x7FFFFFFF;

struct Student {
    string name;
    char gender;
    string id;
    int grade;

    Student(string name = string(), char gender = 'F', string id = string(), int grade = 0)
        : name(name),
          gender(gender),
          id(id),
          grade(grade) {
    }
};

void print(Student student) {
    if (student.name != "tmp") {
        cout << student.name << " " << student.id << endl;
    } else {
        cout << "Absent" << endl;
    }
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
    Student minBoy("tmp", 'M', "tmp", 101);
    Student maxGirl("tmp", 'F', "tmp", -1);

    for (int i = 0; i < n; ++i) {
        Student tmp;
        cin >> tmp.name >> tmp.gender >> tmp.id >> tmp.grade;

        if (tmp.gender == 'M' && tmp.grade < minBoy.grade) {
            minBoy = tmp;
        }

        if (tmp.gender == 'F' && tmp.grade > maxGirl.grade) {
            maxGirl = tmp;
        }
    }

    print(maxGirl);
    print(minBoy);

    if (maxGirl.name != "tmp" && minBoy.name != "tmp") {
        cout << maxGirl.grade - minBoy.grade << endl;
    } else {
        cout << "NA" << endl;
    }

    return 0;
}
