/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-16 22:04:51
* @Description:  1033. 旧键盘打字(20)
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
旧键盘上坏了几个键，于是在敲一段文字的时候，对应的字符就不会出现。现在给出应该输入的一段文字、以及坏掉的那些键，打出的结果文字会是怎样？

输入格式：

输入在2行中分别给出坏掉的那些键、以及应该输入的文字。其中对应英文字母的坏键以大写给出；每段文字是不超过105个字符的串。可用的字符包括字母[a-z, A-Z]、数字0-9、以及下划线“_”（代表空格）、“,”、“.”、“-”、“+”（代表上档键）。题目保证第2行输入的文字串非空。

注意：如果上档键坏掉了，那么大写的英文字母无法被打出。

输出格式：

在一行中输出能够被打出的结果文字。如果没有一个字符能被打出，则输出空行。

输入样例：
7+IE.
7_This_is_a_test.
输出样例：
_hs_s_a_tst

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
#include <vector>

using namespace std;

char toUpper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 'A';
    }

    return ch;
}

bool isUppercase(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

string getOutput(string input, string brokenKeys) {
    string result;
    set<char> bk_set;
    bool is_plus_broken = false;

    for(auto brokenKey : brokenKeys) {
        bk_set.insert(toUpper(brokenKey));
    }

    if (bk_set.find('+') != bk_set.end()) {
        is_plus_broken = true;
    }

    for(auto key : input) {
        if(bk_set.find(toUpper(key)) == bk_set.end()) {
            if(!(is_plus_broken && isUppercase(key))) {
                result.append(1, key);
            }
        }
    }

    return result;
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
    string brokenKeys, input;
    //broken keys may be empty, in this case, cin will ignore the first line,
    //and jump to read the second line, which is not what we want, so we use getline here
    getline(cin, brokenKeys);
    getline(cin, input);
    cout << getOutput(input, brokenKeys) << endl;
    return 0;
}
