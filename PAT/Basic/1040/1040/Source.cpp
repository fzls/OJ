/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:      v1.0
* @Time:         2016-02-17 18:09:00
* @Description:  1040. 有几个PAT（25）
时间限制
120 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CAO, Peng
字符串APPAPT中包含了两个单词“PAT”，其中第一个PAT是第2位(P),第4位(A),第6位(T)；第二个PAT是第3位(P),第4位(A),第6位(T)。

现给定字符串，问一共可以形成多少个PAT？

输入格式：

输入只有一行，包含一个字符串，长度不超过105，只包含P、A、T三种字母。

输出格式：

在一行中输出给定字符串中包含多少个PAT。由于结果可能比较大，只输出对1000000007取余数的结果。

输入样例：
APPAPT
输出样例：
2
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
#define DEBUG

#ifdef DEBUG
    #define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define debug(...)
#endif

//string pats;
//int upper;
//char gPat[] = { 'P', 'A', 'T' };
//int cnt = 0;
//vector<int> Ps, As, Ts;
//
//void findPAT(int pos, int index) {
//    //    if(index == 3) {
//    //        ++cnt;
//    //
//    //        if (cnt >= 1000000007) {
//    //            cnt -= 1000000007;
//    //        }
//    //
//    //        return;
//    //    }
//    //
//    //    for (int i = pos; i <= upper; ++i) {
//    //        if(pats[i] == gPat[index]) {
//    //            findPAT(i + 1, index + 1);
//    //        }
//    //    }
//    //    //iterative
//    // for (int p = pos; p <= upper - 2; ++p)
//    //     if(pats[p] == 'P') {
//    //         for (int a = p + 1; a <= upper - 1; ++a)
//    //             if(pats[a] == 'A') {
//    //                 for (int t = a + 1; t <= upper; ++t)
//    //                     if(pats[t] == 'T') {
//    //                         ++cnt;
//    //                         if (cnt >= 1000000007) {
//    //                             cnt -= 1000000007;
//    //                         }
//    //                     }
//    //             }
//    //     }
//    int upperP = static_cast<int>(Ps.size());
//    int upperA = static_cast<int>(As.size());
//    int upperT = static_cast<int>(Ts.size());
//
//    for (int p = 0; p < upperP; ++p)
//        for (int a = 0; a < upperA; ++a)
//            if(As[a] > Ps[p]) {
//                for (int t = 0; t < upperT; ++t)
//                    if(Ts[t] > As[a]) {
//                        ++cnt;
//
//                        if (cnt >= 1000000007) {
//                            cnt -= 1000000007;
//                        }
//                    }
//            }
//}


struct Util {
    int number;
    int next;
};
int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    //    cin >> pats;
    //    upper = pats.size() - 1;
    //
    //    for (int i = 0; i <= upper; ++i)
    //        if (pats[i] == 'P') {
    //            Ps.push_back(i);
    //        } else if (pats[i] == 'A') {
    //            As.push_back(i);
    //        } else {
    //            Ts.push_back(i);
    //        }
    //
    //    findPAT(0, 0);
    //    cout << cnt;
    string pats;
    cin >> pats;
    vector<int> Ps;
    vector<int> As;
    vector<Util> pUtil;
    Util tmp;
    int posP = 0, posA = 0;
    int np = 0, na = 0, nt = 0;

    for (int i = pats.find_first_of('P'); i < pats.size(); ++i) {
        if(pats[i] == 'P') {
            np++;
        } else if (pats[i] == 'A') {
            tmp.number = np - posP;
            tmp.next = na;
            pUtil.push_back(tmp);
            posP = np;
            na++;
        } else {
            for (int a = posA; a < na; ++a) {
                As.push_back(nt);
            }

            posA = na;
            nt++;
        }
    }

    int cnt = 0;

    for (int p = 0; p < pUtil.size(); ++p) {
        int _cnt = 0;

        for (int a = pUtil[p].next; a < posA; ++a) {
            _cnt += (nt - As[a]);
        }

        cnt += pUtil[p].number * _cnt;

        if (cnt >= 1000000007) {
            cnt -= 1000000007;
        }
    }

    cout << cnt;
    return 0;
}
