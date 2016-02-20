/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-20 15:09:50
* @Description:  风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1009. Product of Polynomials (25)
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
This time, you are supposed to find A*B where A and B are two polynomials.

Input Specification:

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of a polynomial: K N1 aN1 N2 aN2 ... NK aNK, where K is the number of nonzero terms in the polynomial, Ni and aNi (i=1, 2, ..., K) are the exponents and coefficients, respectively. It is given that 1 <= K <= 10, 0 <= NK < ... < N2 < N1 <=1000.

Output Specification:

For each test case you should output the product of A and B in one line, with the same format as the input. Notice that there must be NO extra space at the end of each line. Please be accurate up to 1 decimal place.

Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5
Sample Output
3 3 3.6 2 6.0 1 1.6
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

struct Node {
    int exp;
    double coeff;
    Node() {
        exp = 0;
        coeff = 0;
    }
};

void print(vector<double> &poly) {
    int nonzeroItems = 0;

    for (int i = 0; i < poly.size(); ++i) {
        if (poly[i] != 0) {
            nonzeroItems++;
        }
    }

    cout << nonzeroItems;

    if (nonzeroItems == 0) {
        cout << " 0 0" << endl;
    } else {
        for (int i = poly.size() - 1; i >= 0; --i) {
            if (poly[i] != 0) {
                cout << " " << i << " " << setprecision(1) << fixed << poly[i];
            }
        }
    }
}

void getPoly(vector<Node> &poly) {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Node tmp;
        cin >> tmp.exp >> tmp.coeff;
        poly.push_back(tmp);
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
    vector<Node> first, second;
    vector<double> product(2001, 0) ;
    getPoly(first);
    getPoly(second);

    //get product
    for (int i = 0; i < first.size(); ++i) {
        for (int j = 0; j < second.size(); ++j) {
            product[first[i].exp + second[j].exp] += first[i].coeff * second[j].coeff;
        }
    }

    //print nonzero item
    print(product);
    return 0;
}
