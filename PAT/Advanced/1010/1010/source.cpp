/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-20 15:42:57
* @Description:  风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1010. Radix (25)
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
Given a pair of positive integers, for example, 6 and 110, can this equation 6 = 110 be true? The answer is "yes", if 6 is a decimal number and 110 is a binary number.

Now for any pair of positive integers N1 and N2, your task is to find the radix of one number while that of the other is given.

Input Specification:

Each input file contains one test case. Each case occupies a line which contains 4 positive integers:
N1 N2 tag radix
Here N1 and N2 each has no more than 10 digits. A digit is less than its radix and is chosen from the set {0-9, a-z} where 0-9 represent the decimal numbers 0-9, and a-z represent the decimal numbers 10-35. The last number "radix" is the radix of N1 if "tag" is 1, or of N2 if "tag" is 2.

Output Specification:

For each test case, print in one line the radix of the other number so that the equation N1 = N2 is true. If the equation is impossible, print "Impossible". If the solution is not unique, output the smallest possible radix.

Sample Input 1:
6 110 1 10
Sample Output 1:
2
Sample Input 2:
1 ab 1 2
Sample Output 2:
Impossible
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

map<char, long long> table;
void setTable() {
    for (long long i = 0; i < 10; ++i) {
        table[i + '0'] = i;
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        table[ch] = ch - 'a' + 10;
    }
}
long long getDecimal(string num, long long radix) {
    long long res = 0;

    for (long long i = 0; i < num.size(); ++i) {
        res = res * radix + table[num[i]];
    }

    return res;
}



int compare(string &num, long long radix, long long first_in_decimal) {
    long long res = 0;

    for (long long i = 0; i < num.size(); ++i) {
        res = res * radix + table[num[i]];

        if (res > first_in_decimal) {
            return 1;
        }
    }

    if (first_in_decimal == res) {
        return 0;
    } else if (first_in_decimal < res) {
        return 1;
    } else {
        return -1;
    }
}

long long find_radix_by_binary_search(long long lowerBound, long long upperBound, string &second, long long first_in_decimal, bool flag) {
    if (lowerBound > upperBound) {
        return -1;
    }

    long long mid = lowerBound + (upperBound - lowerBound) / 2;

    if(flag) {
        flag = false;
        mid = lowerBound;
    }

    int cmp = compare(second, mid, first_in_decimal);//avoid overflow

    if (cmp == 0) {
        long long left = find_radix_by_binary_search(lowerBound, mid - 1, second, first_in_decimal, flag);

        if (left != -1) {
            mid = min(mid, left);
        }

        return mid;
    } else if (cmp == -1) {
        return find_radix_by_binary_search(mid + 1, upperBound, second, first_in_decimal, flag);
    } else {
        return find_radix_by_binary_search(lowerBound, mid - 1, second, first_in_decimal, flag);
    }
}
//
//long long find_radix_by_binary_search(long long low, long long high, string &second, long long key) {
//    long long mid = low;
//    long long tmp;
//
//    while (low <= high) {
//        tmp = compare(second, mid, key);
//
//        if (tmp > 0) {
//            high = mid - 1;
//        } else if (tmp < 0) {
//            low = mid + 1;
//        } else { return mid; }
//
//        mid =low+ (high - low)/2;
//    }
//
//    return -1;
//}



int main() {
    #pragma region GET_INPUT
    {
        #ifndef ONLINE_JUDGE
        freopen("test.in", "r", stdin);
        freopen("test.out", "w", stdout);
        #endif
    }
    #pragma endregion
    setTable();
    string first, second;
    long long tag, radix;
    //radix is represented by 2~36
    cin >> first >> second >> tag >> radix;

    if (tag == 2) {
        swap(first, second);
    }

    //radix of first is known
    long long first_in_decimal = getDecimal(first, radix);
<<<<<<< HEAD
    long long radix_second;
    long long lowerBound = 0;

    for (int i = 0; i < second.size(); ++i)
        if (!(table[second[i]] < lowerBound)) {
            lowerBound = table[second[i]] + 1;
        }

    long long upperBound = first_in_decimal >= lowerBound ? first_in_decimal + 1 : lowerBound + 1;
    radix_second = find_radix_by_binary_search(lowerBound, upperBound, second, first_in_decimal, true);

    if (radix_second == -1) {
=======
    long long lowerBound = 2;

    for (int i = 0; i < second.size(); ++i) {
        if (table[second[i]] + 1 > lowerBound) {
            lowerBound = table[second[i]] + 1;
        }
    }

    long long upperBound = first_in_decimal >= lowerBound ? first_in_decimal : lowerBound;
    long long radix_second = lowerBound;
    long long accRate = 1;
    long long backup = 0;
    bool isTry = false;

    //线性搜索在基数很大时，运行效率会很低，可以使用二分法
    //但也可以使用如下的通过设定一个加速度并结合回溯法来提高效率
    while(true) {
        long long second_in_decimal = getDecimal(second, radix_second);

        if(second_in_decimal == first_in_decimal) {
            break;
        }

        if(second_in_decimal < first_in_decimal) {
            if (accRate > 1) {
                isTry = true;
                backup = radix_second;
            } else {
                isTry = false;
            }

            radix_second += accRate;
            accRate *= 2;
            //          radix_second += accRate;
        } else {
            if(!isTry) {
                break;
            }

            radix_second -= accRate / 2;
            accRate /= 4;
        }
    }

    bool isPossiable = getDecimal(second, radix_second) == first_in_decimal;

    if (!isPossiable) {
>>>>>>> add_aceratoer_1010
        cout << "Impossible" << endl;
    } else {
        cout << radix_second << endl;
    }

    return 0;
}
