//!+不知为何，这个程序超时了。。。。。。明明跟别人的基本一样
/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-15 13:47:35
* @Description:  1015. 德才论 (25)
时间限制
200 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Li
宋代史学家司马光在《资治通鉴》中有一段著名的“德才论”：“是故才德全尽谓之圣人，才德兼亡谓之愚人，德胜才谓之君子，才胜德谓之小人。凡取人之术，苟不得圣人，君子而与之，与其得小人，不若得愚人。”

现给出一批考生的德才分数，请根据司马光的理论给出录取排名。

输入格式：

输入第1行给出3个正整数，分别为：N（<=105），即考生总数；L（>=60），为录取最低分数线，即德分和才分均不低于L的考生才有资格被考虑录取；H（<100），为优先录取线——德分和才分均不低于此线的被定义为“才德全尽”，此类考生按德才总分从高到低排序；才分不到但德分到线的一类考生属于“德胜才”，也按总分排序，但排在第一类考生之后；德才分均低于H，但是德分不低于才分的考生属于“才德兼亡”但尚有“德胜才”者，按总分排序，但排在第二类考生之后；其他达到最低线L的考生也按总分排序，但排在第三类考生之后。

随后N行，每行给出一位考生的信息，包括：准考证号、德分、才分，其中准考证号为8位整数，德才分为区间[0, 100]内的整数。数字间以空格分隔。

输出格式：

输出第1行首先给出达到最低分数线的考生人数M，随后M行，每行按照输入格式输出一位考生的信息，考生按输入中说明的规则从高到低排序。当某类考生中有多人总分相同时，按其德分降序排列；若德分也并列，则按准考证号的升序输出。

输入样例：
14 60 80
10000001 64 90
10000002 90 60
10000011 85 80
10000003 85 80
10000004 80 85
10000005 82 77
10000006 83 76
10000007 90 78
10000008 75 79
10000009 59 90
10000010 88 45
10000012 80 100
10000013 90 99
10000014 66 60
输出样例：
12
10000013 90 99
10000012 80 100
10000003 85 80
10000011 85 80
10000004 80 85
10000007 90 78
10000006 83 76
10000005 82 77
10000002 90 60
10000014 66 60
10000008 75 79
10000001 64 90

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



class Examinee {
public:
    Examinee(int n = 0, int v = 0, int t = 0);
    ~Examinee();

    inline bool operator > (const Examinee &right) const;
    int number;
    int virtue;
    int talent;
    int sum;
private:
    int category;
};

inline bool Examinee::operator > (const Examinee &right) const {
    if (this->sum == right.sum) {
        if (this->virtue == right.virtue) {
            return this->number < right.number;
        } else {
            return this->virtue > right.virtue;
        }
    } else {
        return this->sum > right.sum;
    }
}

bool cmp (const Examinee &left, const Examinee &right) {
    if (left.sum == right.sum) {
        if (left.virtue == right.virtue) {
            return left.number < right.number;
        } else {
            return left.virtue > right.virtue;
        }
    } else {
        return left.sum > right.sum;
    }
}

Examinee::Examinee(int n, int v, int t) {
    number = n;
    virtue = v;
    talent = t;
}

Examinee::~Examinee() {
}

inline void print(const vector<Examinee> &admits) {
    for (Examinee admit : admits) {
        cout << admit.number << " " << admit.virtue << " " << admit.talent << endl;
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
    int total, virtue, talent, LEAST, BOUNDARY;
    vector<Examinee> saints, gentlemans, fool_with_more_virtues, villain_and_some_fools;
    Examinee examinee;
    cin >> total >> LEAST >> BOUNDARY;

    for (int i = 0; i < total; ++i) {
        cin >> examinee.number >> examinee.virtue >> examinee.talent;
        examinee.sum = examinee.virtue + examinee.talent;
        virtue = examinee.virtue;
        talent = examinee.talent;

        if (virtue >= LEAST && talent >= LEAST) {
            if (virtue >= BOUNDARY && talent >= BOUNDARY) {
                saints.push_back(examinee);
            } else if (virtue >= BOUNDARY && talent < BOUNDARY) {
                gentlemans.push_back(examinee);
            } else if (virtue < BOUNDARY && talent < BOUNDARY &&
                       virtue >= talent) {
                fool_with_more_virtues.push_back(examinee);
            } else {
                villain_and_some_fools.push_back(examinee);
            }
        }
    }

    sort(saints.begin(), saints.end(), cmp);
    sort(gentlemans.begin(), gentlemans.end(), cmp);
    sort(fool_with_more_virtues.begin(), fool_with_more_virtues.end(), cmp);
    sort(villain_and_some_fools.begin(), villain_and_some_fools.end(), cmp);
    int cnt = saints.size() + gentlemans.size() + fool_with_more_virtues.size() +
              villain_and_some_fools.size();
    cout << cnt << endl;
    print(saints);
    print(gentlemans);
    print(fool_with_more_virtues);
    print(villain_and_some_fools);
    return 0;
}
