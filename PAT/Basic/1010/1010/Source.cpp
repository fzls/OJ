/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-14 13:38:20
* @Description:  1010. 一元多项式求导 (25)
时间限制
400 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
设计函数求一元多项式的导数。（注：xn（n为整数）的一阶导数为n*xn-1。）

输入格式：以指数递降方式输入多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式：以与输入相同的格式输出导数多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。注意“零多项式”的指数和系数都是0，但是表示为“0 0”。

输入样例：
3 4 -5 2 6 1 -2 0
输出样例：
12 3 -10 1 6 0
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

class Poly {
  public:
    Poly();
    ~Poly();
    int coff;
    int exp;
    void print();
    void diff();
  private:

};

Poly::Poly() {
}

Poly::~Poly() {
}

void Poly::print() {
    if(!(coff == 0 && exp != 0)) {
        cout << coff << " " << exp;
    }
}
void Poly::diff() {
    if (exp == 0) {
        coff = 0;
        exp = -1;
    } else {
        coff *= exp;
        --exp;
    }
}
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
    vector<Poly> polys;
    Poly temp;

    /*get input*/
    while (cin >> temp.coff && cin >> temp.exp) {
        polys.push_back(temp);
    }

    /*differential the poly*/
    for (auto &poly : polys) {
        poly.diff();
    }

    //!if there exit the zero poly which is identified by its exp equals to -1
    //!remove it
    decltype(polys.begin()) tmp = polys.end();

    for (auto i = polys.begin(); i != polys.end(); ++i)
        if (i->exp == -1) {
            tmp = i;
        }

    if (tmp != polys.end()) {
        polys.erase(tmp);
    }

    //?if the polys is zero polys , simply output 0 0
    if (polys.size() == 0) {
        cout << "0 0";
    }

    //?otherwise, output in the right format
    for (int i = 0; i < polys.size(); ++i) {
        if (i != 0) {
            cout << " ";
        }

        polys[i].print();
    }

    return 0;
}
