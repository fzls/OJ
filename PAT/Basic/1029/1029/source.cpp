/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:
* @Time:         2016-02-16 19:24:46
* @Description:  1029. 旧键盘(20)
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
旧键盘上坏了几个键，于是在敲一段文字的时候，对应的字符就不会出现。现在给出应该输入的一段文字、以及实际被输入的文字，请你列出肯定坏掉的那些键。

输入格式：

输入在2行中分别给出应该输入的文字、以及实际被输入的文字。每段文字是不超过80个字符的串，由字母A-Z（包括大、小写）、数字0-9、以及下划线“_”（代表空格）组成。题目保证2个字符串均非空。

输出格式：

按照发现顺序，在一行中输出坏掉的键。其中英文字母只输出大写，每个坏键只输出一次。题目保证至少有1个坏键。

输入样例：
7_This_is_a_test
_hs_s_a_es
输出样例：
7TI

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

char to_upper_case(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return letter - 'a' + 'A';
    }

    return letter;
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
    string input, output;
    set<char> broken_keys_set;
    vector<char> broken_keys;
    cin >> input >> output;
    int i = 0, j = 0;

    for (; i < input.size() && j < output.size();) {
        if(input[i] == output[j]) {
            ++i; ++j;
        } else {
            char upper_case = to_upper_case(input[i]);

            if(broken_keys_set.find(upper_case) == broken_keys_set.end()) {
                broken_keys_set.insert(upper_case);
                broken_keys.push_back(upper_case);
            }

            ++i;
        }
    }

    for (; i < input.size(); ++i) {
        char upper_case = to_upper_case(input[i]);

        if (broken_keys_set.find(upper_case) == broken_keys_set.end()) {
            broken_keys_set.insert(upper_case);
            broken_keys.push_back(upper_case);
        }
    }

    for (auto missed : broken_keys) {
        cout << missed;
    }

    return 0;
}
