/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-17 10:08:52
* @Description:  1034. 有理数四则运算(20)
时间限制
200 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
本题要求编写程序，计算2个有理数的和、差、积、商。

输入格式：

输入在一行中按照“a1/b1 a2/b2”的格式给出两个分数形式的有理数，其中分子和分母全是整型范围内的整数，负号只可能出现在分子前，分母不为0。

输出格式：

分别在4行中按照“有理数1 运算符 有理数2 = 结果”的格式顺序输出2个有理数的和、差、积、商。注意输出的每个有理数必须是该有理数的最简形式“k a/b”，其中k是整数部分，a/b是最简分数部分；若为负数，则须加括号；若除法分母为0，则输出“Inf”。题目保证正确的输出中没有超过整型范围的整数。

输入样例1：
2/3 -4/2
输出样例1：
2/3 + (-2) = (-1 1/3)
2/3 - (-2) = 2 2/3
2/3 * (-2) = (-1 1/3)
2/3 / (-2) = (-1/3)
输入样例2：
5/3 0/6
输出样例2：
1 2/3 + 0 = 1 2/3
1 2/3 - 0 = 1 2/3
1 2/3 * 0 = 0
1 2/3 / 0 = Inf
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

class Rational {
  public:
    Rational(long long n = 0, long long d = 1);
    ~Rational();

    Rational operator + (const Rational &rhs);
    Rational operator - (const Rational &rhs);
    Rational operator * (const Rational &rhs);
    Rational operator / (const Rational &rhs);
    friend ostream &operator <<(ostream &os, const Rational &obj);
    friend istream &operator >>(istream &is, Rational &obj);

  private:
    long long mNumerator;
    long long mDenominator;

};

ostream &operator<<(ostream &os, const Rational &obj) {
    bool isMinus = false;
    long long n = obj.mNumerator;

    if (n < 0) {
        isMinus = true;
        n = -n;
    }

    long long d = obj.mDenominator;

    // if zero divide, set the dennominator to 0 to match this case
    if (d == 0) {
        os << "Inf";
        return os;
    }

    long long k = n / d;
    long long a = n % d;
    long long b = d;

    if (isMinus) {
        os << "(-";
    }

    bool isKZero = true;

    if (k != 0) {
        isKZero = false;
        os << k ;
    }

    if (!isKZero && a != 0) {
        cout << " ";
    }

    if (a == 0) {
        if (isKZero) {
            os << "0";
        }
    } else {
        cout << a;

        if (b != 1) {
            cout << "/" << b;
        }
    }

    if (isMinus) {
        os << ")";
    }

    return os;
}

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

istream &operator>>(istream &is, Rational &obj) {
    is >> obj.mNumerator;
    char tmp;
    is >> tmp;
    is >> obj.mDenominator;

    if (obj.mNumerator != 0 && obj.mDenominator != 0) {
        long long _gcd = gcd(abs(obj.mNumerator), obj.mDenominator);
        obj.mNumerator /= _gcd;
        obj.mDenominator /= _gcd;
    }

    return is;
}

Rational::Rational(long long n, long long d) : mNumerator{ n }, mDenominator{ d } {
}

Rational::~Rational() {
}

Rational Rational::operator+(const Rational &rhs) {
    long long n = this->mNumerator * rhs.mDenominator + this->mDenominator * rhs.mNumerator;
    long long d = this->mDenominator * rhs.mDenominator;

    if (n != 0 && d != 0) {
        long long _gcd = gcd(abs(n), d);
        n /= _gcd;
        d /= _gcd;
    }

    return Rational(n, d);
}

Rational Rational::operator-(const Rational &rhs) {
    long long n = this->mNumerator * rhs.mDenominator - this->mDenominator * rhs.mNumerator;
    long long d = this->mDenominator * rhs.mDenominator;

    if (n != 0 && d != 0) {
        long long _gcd = gcd(abs(n), d);
        n /= _gcd;
        d /= _gcd;
    }

    return Rational(n, d);
}

Rational Rational::operator*(const Rational &rhs) {
    long long n = this->mNumerator * rhs.mNumerator ;
    long long d = this->mDenominator * rhs.mDenominator;

    if (n != 0 && d != 0) {
        long long _gcd = gcd(abs(n), d);
        n /= _gcd;
        d /= _gcd;
    }

    return Rational(n, d);
}

Rational Rational::operator/(const Rational &rhs) {
    long long n = this->mNumerator * rhs.mDenominator;
    long long d = this->mDenominator * rhs.mNumerator;

    if (d < 0) {
        d = -d;
        n = -n;
    }

    if (n != 0 && d != 0) {
        long long _gcd = gcd(abs(n), d);
        n /= _gcd;
        d /= _gcd;
    }

    return Rational(n, d);
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
    Rational first, second;
    cin >> first >> second;
    cout << first << " + " << second << " = " << first + second << endl;
    cout << first << " - " << second << " = " << first - second << endl;
    cout << first << " * " << second << " = " << first *second << endl;
    cout << first << " / " << second << " = " << first / second << endl;
    return 0;
}
