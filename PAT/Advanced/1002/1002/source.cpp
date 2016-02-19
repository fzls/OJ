/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-19 13:46:58
* @Description:  1002. A+B for Polynomials (25)
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
This time, you are supposed to find A+B where A and B are two polynomials.

Input

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of a polynomial: K N1 aN1 N2 aN2 ... NK aNK, where K is the number of nonzero terms in the polynomial, Ni and aNi (i=1, 2, ..., K) are the exponents and coefficients, respectively. It is given that 1 <= K <= 10，0 <= NK < ... < N2 < N1 <=1000.

Output

For each test case you should output the sum of A and B in one line, with the same format as the input. Notice that there must be NO extra space at the end of each line. Please be accurate to 1 decimal place.

Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5
Sample Output
3 2 1.5 1 2.9 0 3.2
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

struct Poly {
    int expo;
    double coeff;
};

void get_input(vector<Poly> &polys) {
    int n;
    cin >> n;
    Poly tmp;

    for (int i = 0; i < n; ++i) {
        cin >> tmp.expo >> tmp.coeff;
        polys.push_back(tmp);
    }
}

void print(const vector<Poly> &sum) {
    cout << sum.size();

    for (int i = 0; i < sum.size(); ++i) {
        cout << " " << sum[i].expo << " " << setprecision(1) << fixed << sum[i].coeff;
    }
}

vector<Poly> get_sum(const vector<Poly> &first, const vector<Poly> &second) {
    auto i = first.begin();
    auto j = second.begin();
    vector<Poly> sum;

    for (; i != first.end() && j != second.end();) {
        if(i->expo < j->expo) {
            sum.push_back(*j);
            ++j;
        } else if(i->expo > j->expo) {
            sum.push_back(*i);
            ++i;
        } else {
            if (i->coeff + j->coeff != 0) {
                Poly tmp;
                tmp.coeff = i->coeff + j->coeff;
                tmp.expo = i->expo;
                sum.push_back(tmp);
            }

            ++i; ++j;
        }
    }

    for (; i != first.end(); ++i) {
        sum.push_back(*i);
    }

    for (; j != second.end(); ++j) {
        sum.push_back(*j);
    }

    return sum;
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
    Poly tmp;
    vector<Poly> first, second;
    get_input(first);
    get_input(second);
    auto sum = get_sum(first, second);
    print(sum);
    return 0;
}
