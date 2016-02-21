/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-21 14:39:07
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1012. The Best Rank (25)
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
To evaluate the performance of our first year CS majored students, we consider their grades of three courses only: C - C Programming Language, M - Mathematics (Calculus or Linear Algebra), and E - English. At the mean time, we encourage students by emphasizing on their best ranks -- that is, among the four ranks with respect to the three courses and the average grade, we print the best rank for each student.

For example, The grades of C, M, E and A - Average of 4 students are given as the following:

StudentID  C  M  E  A
310101     98 85 88 90
310102     70 95 88 84
310103     82 87 94 88
310104     91 91 91 91
Then the best ranks for all the students are No.1 since the 1st one has done the best in C Programming Language, while the 2nd one in Mathematics, the 3rd one in English, and the last one in average.

Input

Each input file contains one test case. Each case starts with a line containing 2 numbers N and M (<=2000), which are the total number of students, and the number of students who would check their ranks, respectively. Then N lines follow, each contains a student ID which is a string of 6 digits, followed by the three integer grades (in the range of [0, 100]) of that student in the order of C, M and E. Then there are M lines, each containing a student ID.

Output

For each of the M students, print in one line the best rank for him/her, and the symbol of the corresponding rank, separated by a space.

The priorities of the ranking methods are ordered as A > C > M > E. Hence if there are two or more ways for a student to obtain the same best rank, output the one with the highest priority.

If a student is not on the grading list, simply output "N/A".

Sample Input
5 6
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 91 91 91
310105 85 90 90
310101
310102
310103
310104
310105
999999
Sample Output
1 C
1 M
1 E
1 A
3 A
N/A
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
#pragma region DebugSetting
//#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif
#pragma endregion


const int COURSE_NUM = 3;
const int AVG = 3;
enum COURSE {
    C = 0,
    M = 1,
    E = 2
};
char kind[] = { 'C', 'M', 'E' };
struct Student {
    string id;
    vector<int> score;
    //four elem, respectly stand for c,m,e,a
    vector<int> rank;
    //stand for rank_c,m,e,a
    int rank_best;
    char rank_kind;
    Student() : score(4, 0), rank(4, 0) {}

    void getAVG() {
        int sum = 0;

        for (int i = 0; i < AVG; ++i) {
            sum += score[i];
        }

        score[AVG] = sum / AVG;
    }
};

bool cmp_c(const Student &lhs, const Student &rhs) {
    return lhs.score[C] > rhs.score[C];
}

bool cmp_m(const Student &lhs, const Student &rhs) {
    return lhs.score[M] > rhs.score[M];
}

bool cmp_e(const Student &lhs, const Student &rhs)  {
    return lhs.score[E] > rhs.score[E];
}

bool cmp_a(const Student &lhs, const Student &rhs) {
    return lhs.score[AVG] > rhs.score[AVG];
}

void compute_best_rank(Student &student) {
    char rank_kind = 'A';
    int rank_best = student.rank[AVG];

    for (int i = C; i <= E; ++i) {
        if (student.rank[i] < rank_best) {
            rank_best = student.rank[i];
            rank_kind = kind[i];
        }
    }

    student.rank_kind = rank_kind;
    student.rank_best = rank_best;
}
typedef bool(*MyCmp)(const Student &lhs, const Student &rhs);

MyCmp myCmp[] = {cmp_c, cmp_m, cmp_e, cmp_a,};

void compute_best_rank(vector<Student> &students, map<string, int> &index_of_id) {
    int rank;
    vector<Student> tmp;

    //计算出四个尺度的排名
    for (int t = 0; t <= AVG; ++t) {
        tmp = students;
        sort(tmp.begin(), tmp.end(), myCmp[t]);
        //降序排列
        rank = 1;

        for (int i = 0; i < tmp.size(); ++i) {
            int index = index_of_id[tmp[i].id];

            if (i != 0) {
                int index_last = index_of_id[tmp[i - 1].id];

                if (students[index].score[t] < students[index_last].score[t]) {
                    rank = i + 1;
                }
            }

            students[index].rank[t] = rank;
        }
    }

    //get the best rank
    for (int i = 0; i < students.size(); ++i) {
        compute_best_rank(students[i]);
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
    int total, query_m;
    cin >> total >> query_m;
    vector<Student> students(total);
    map<string, int> index_of_id;

    for (int i = 0; i < total; ++i) {
        cin >> students[i].id;

        for (int c = 0; c < COURSE_NUM; ++c) {
            cin >> students[i].score[c];
        }

        students[i].getAVG();
        index_of_id[students[i].id] = i;
    }

    //get the best rank for each
    compute_best_rank(students, index_of_id);
    #pragma region DEBUG_CODE
    {
        #ifdef DEBUG

        for (int i = 0; i < students.size(); ++i) {
            cout << "student " << students[i].id << " " << students[i].rank[C] << " " << students[i].rank[M] << " " << students[i].rank[E] << " " << students[i].rank[AVG] << endl;
        }

        #endif
    }
    #pragma endregion

    //output the student's rank who wanna query it
    for (int i = 0; i < query_m; ++i) {
        string id;
        cin >> id;

        if(index_of_id.find(id) != index_of_id.end()) {
            cout << students[index_of_id[id]].rank_best << " " << students[index_of_id[id]].rank_kind << endl;
        } else {
            cout << "N/A" << endl;
        }
    }

    return 0;
}
