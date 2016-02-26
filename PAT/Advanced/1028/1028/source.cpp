/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-26 17:55:00
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1028. List Sorting (25)
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
Excel can sort records according to any column. Now you are supposed to imitate this function.

Input

Each input file contains one test case. For each case, the first line contains two integers N (<=100000) and C, where N is the number of records and C is the column that you are supposed to sort the records with. Then N lines follow, each contains a record of a student. A student's record consists of his or her distinct ID (a 6-digit number), name (a string with no more than 8 characters without space), and grade (an integer between 0 and 100, inclusive).

Output

For each test case, output the sorting result in N lines. That is, if C = 1 then the records must be sorted in increasing order according to ID's; if C = 2 then the records must be sorted in non-decreasing order according to names; and if C = 3 then the records must be sorted in non-decreasing order according to grades. If there are several students who have the same name or grade, they must be sorted according to their ID's in increasing order.

Sample Input 1
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60
Sample Output 1
000001 Zoe 60
000007 James 85
000010 Amy 90
Sample Input 2
4 2
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 98
Sample Output 2
000010 Amy 90
000002 James 98
000007 James 85
000001 Zoe 60
Sample Input 3
4 3
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 90
Sample Output 3
000001 Zoe 60
000007 James 85
000002 James 90
000010 Amy 90
提交代码
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
#include <cstring>
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
#include <cstdio>
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
    int id;
    char name[20];
    int grade;
};

vector<Student> students;
inline bool cmp_id(const Student &lhs, const Student &rhs) {
    return lhs.id < rhs.id;
}
inline bool cmp_name(const Student &lhs, const Student &rhs) {
    return strcmp(lhs.name , rhs.name) < 0 || strcmp(lhs.name, rhs.name) == 0 && cmp_id(lhs, rhs);
}
inline bool cmp_grade(const Student &lhs, const Student &rhs) {
    return lhs.grade < rhs.grade || lhs.grade == rhs.grade && cmp_id(lhs, rhs);
}
typedef bool(*CMP)(const Student &, const Student &);

//inline bool cmp_id(const int &lhs, const int &rhs) {
//    return students[lhs].id < students[rhs].id;
//}
//inline bool cmp_name(const int &lhs, const int &rhs) {
//    return strcmp(students[lhs].name , students[rhs].name) < 0 || strcmp(students[lhs].name , students[rhs].name) == 0  && students[lhs].id < students[rhs].id;
//}
//inline bool cmp_grade(const int &lhs, const int &rhs) {
//    return students[lhs].grade < students[rhs].grade || students[lhs].grade == students[rhs].grade && students[lhs].id < students[rhs].id;
//}
//typedef bool(*CMP)(const int &, const int &);
int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    int n, cmd;
    cin >> n >> cmd;
    vector<int> index_util(n);

    for (int i = 0; i < index_util.size(); ++i) {
        index_util[i] = i;
    }

    while(n--) {
        Student tmp;
        scanf("%d%s%d", &tmp.id, &tmp.name, &tmp.grade);
        //!+cin and cout is slower than scanf and printf
        //        cin >> tmp.id >> tmp.name >> tmp.grade;
        students.push_back(move(tmp));
    }

    CMP cmp[] = { cmp_id, cmp_id , cmp_name , cmp_grade };
    sort(students.begin(), students.end(), cmp[cmd]);

    for(auto s : students) {
        //        cout << setw(6) << setfill('0') << s.id << " " << s.name << " " << s.grade << endl;
        printf("%06d %s %d\n", s.id, s.name, s.grade);
    }

    //    CMP cmp[] = { cmp_id, cmp_id , cmp_name , cmp_grade };
    //    sort(index_util.begin(), index_util.end(), cmp[cmd]);
    //
    //    for (auto s : index_util) {
    //        //        cout << setw(6) << setfill('0') << students[s].id << " " << students[s].name << " " << students[s].grade << endl;
    //        printf("%06d %s %d\n", students[s].id, students[s].name, students[s].grade);
    //    }
    return 0;
}
