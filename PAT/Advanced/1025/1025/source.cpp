/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-25 18:37:36
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1025. PAT Ranking (25)
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
Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of Zhejiang University. Each test is supposed to run simultaneously in several places, and the ranklists will be merged immediately after the test. Now it is your job to write a program to correctly merge all the ranklists and generate the final rank.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive number N (<=100), the number of test locations. Then N ranklists follow, each starts with a line containing a positive integer K (<=300), the number of testees, and then K lines containing the registration number (a 13-digit number) and the total score of each testee. All the numbers in a line are separated by a space.

Output Specification:

For each test case, first print in one line the total number of testees. Then print the final ranklist in the following format:

registration_number final_rank location_number local_rank

The locations are numbered from 1 to N. The output must be sorted in nondecreasing order of the final ranks. The testees with the same score must have the same rank, and the output must be sorted in nondecreasing order of their registration numbers.

Sample Input:
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
Sample Output:
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4
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

//registration_number final_rank location_number local_rank
struct Testee {
    string registration_number;
    int final_rank;
    int location_number;
    int local_rank;
    int score;
    void print();
};

void Testee::print() {
    cout << registration_number << " " << final_rank << " " << location_number << " " << local_rank << endl;
}

bool cmp_testee(const Testee &lhs, const Testee &rhs) {
    return lhs.score > rhs.score || lhs.score == rhs.score && lhs.registration_number < rhs.registration_number;
}
void merge(vector<Testee> &combined, vector<Testee> &place) {
    vector<Testee> tmp;
    int i = 0, j = 0;

    while (i < combined.size() && j < place.size()) {
        if (cmp_testee(combined[i], place[j])) {
            tmp.push_back(combined[i++]);
        } else {
            tmp.push_back(place[j++]);
        }
    }

    while (i < combined.size()) {
        tmp.push_back(combined[i++]);
    }

    while (j < place.size()) {
        tmp.push_back(place[j++]);
    }

    combined = tmp;
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
    int n_place;
    cin >> n_place;
    vector<vector<Testee>> places(n_place);

    for (int p = 0; p < n_place; ++p) {
        int n_testee;
        cin >> n_testee;

        while(n_testee--) {
            Testee tmp;
            cin >> tmp.registration_number >> tmp.score;
            tmp.location_number = p + 1;
            places[p].push_back(std::move(tmp));
        }

        sort(places[p].begin(), places[p].end(), cmp_testee);
        int local_rank = 1;

        for (int i = 0; i < places[p].size(); ++i) {
            if (i != 0 && places[p][i - 1].score > places[p][i].score) {
                local_rank = i + 1;
            }

            places[p][i].local_rank = local_rank;
        }
    }

    //合并结果
    vector<Testee> combined;

    //method 1 simplely combine and sort
    for (auto place : places)
        for (auto testee : place) {
            combined.push_back(std::move(testee));
        }

    sort(combined.begin(), combined.end(), cmp_testee);
    //method 2 make use of the sorted vector
    //    for (int i = 0; i < places.size(); ++i) {
    //        merge(combined, places[i]);
    //    }
    int final_rank = 1;

    for (int i = 0; i < combined.size(); ++i) {
        if (i != 0 && combined[i - 1].score > combined[i].score) {
            final_rank = i + 1;
        }

        combined[i].final_rank = final_rank;
    }

    cout << combined.size() << endl;

    for (auto testee : combined) {
        testee.print();
    }

    return 0;
}
