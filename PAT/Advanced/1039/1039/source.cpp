/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-28 23:19:58
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1039. Course List for Student (25)
时间限制
200 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
CHEN, Yue
Zhejiang University has 40000 students and provides 2500 courses. Now given the student name lists of all the courses, you are supposed to output the registered course list for each student who comes for a query.

Input Specification:

Each input file contains one test case. For each case, the first line contains 2 positive integers: N (<=40000), the number of students who look for their course lists, and K (<=2500), the total number of courses. Then the student name lists are given for the courses (numbered from 1 to K) in the following format: for each course i, first the course index i and the number of registered students Ni (<= 200) are given in a line. Then in the next line, Ni student names are given. A student name consists of 3 capital English letters plus a one-digit number. Finally the last line contains the N names of students who come for a query. All the names and numbers in a line are separated by a space.

Output Specification:

For each test case, print your results in N lines. Each line corresponds to one student, in the following format: first print the student's name, then the total number of registered courses of that student, and finally the indices of the courses in increasing order. The query results must be printed in the same order as input. All the data in a line must be separated by a space, with no extra space at the end of the line.

Sample Input:
11 5
4 7
BOB5 DON2 FRA8 JAY9 KAT3 LOR6 ZOE1
1 4
ANN0 BOB5 JAY9 LOR6
2 7
ANN0 BOB5 FRA8 JAY9 JOE4 KAT3 LOR6
3 1
BOB5
5 9
AMY7 ANN0 BOB5 DON2 FRA8 JAY9 KAT3 LOR6 ZOE1
ZOE1 ANN0 BOB5 JOE4 JAY9 FRA8 DON2 AMY7 KAT3 LOR6 NON9
Sample Output:
ZOE1 2 4 5
ANN0 3 1 2 5
BOB5 5 1 2 3 4 5
JOE4 1 2
JAY9 4 1 2 4 5
FRA8 3 2 4 5
DON2 2 4 5
AMY7 1 5
KAT3 3 2 4 5
LOR6 4 1 2 4 5
NON9 0
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
    set<int> courses;

    explicit Student(string name = string())
        : name(name) {
    }
};

void print(Student &student) {
    printf("%s %d", student.name.c_str(), student.courses.size());

    for (auto c : student.courses) {
        printf(" %d", c);
    }

    printf("\n");
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
    int n, c;
    scanf("%d%d", &n, &c);
    vector<Student> students;
    unordered_map<string, int> name2idx;
    int cnt = 0;

    for (int i = 1; i <= c; ++i) {
        int index, s;
        scanf("%d%d", &index, &s);

        for (int j = 0; j < s; ++j) {
            char name_c[5];
            scanf("%s", name_c);
            string name(name_c);

            //serilize
            if (name2idx.find(name) == name2idx.end()) {
                name2idx[name] = cnt;
                students.push_back(Student(name));
                ++cnt;
            }

            //add course
            students[name2idx[name]].courses.insert(index);
        }
    }

    for (int i = 0; i < n; ++i) {
        char query_c[5];
        scanf("%s", query_c);
        string query(query_c);

        if (name2idx.find(query) != name2idx.end()) {
            print(students[name2idx[query]]);
        } else {
            printf("%s 0\n", query_c);
        }
    }

    return 0;
}