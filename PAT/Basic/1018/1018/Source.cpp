/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-15 16:42:23
* @Description:  1018. 锤子剪刀布 (20)
时间限制
100 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
大家应该都会玩“锤子剪刀布”的游戏：两人同时给出手势，胜负规则如图所示：


现给出两人的交锋记录，请统计双方的胜、平、负次数，并且给出双方分别出什么手势的胜算最大。

输入格式：

输入第1行给出正整数N（<=105），即双方交锋的次数。随后N行，每行给出一次交锋的信息，即甲、乙双方同时给出的的手势。C代表“锤子”、J代表“剪刀”、B代表“布”，第1个字母代表甲方，第2个代表乙方，中间有1个空格。

输出格式：

输出第1、2行分别给出甲、乙的胜、平、负次数，数字间以1个空格分隔。第3行给出两个字母，分别代表甲、乙获胜次数最多的手势，中间有1个空格。如果解不唯一，则输出按字母序最小的解。

输入样例：
10
C J
J B
C B
B B
B C
C C
C B
J B
B C
J J
输出样例：
5 3 2
2 3 5
B B
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
enum State {
    WIN,
    DRAW,
    LOSE
};

struct Game {
    int win;
    int draw;
    int lose;
    int win_c;
    int win_j;
    int win_b;
    Game() {
        win = 0;
        draw = 0;
        lose = 0;
        win_c = 0;
        win_j = 0;
        win_b = 0;
    }

    char frequent() {
        //+only one result
        if (win_c > win_b && win_c > win_j) {
            return 'C';
        } else if (win_b > win_c && win_b > win_j) {
            return 'B';
        } else if (win_j > win_b && win_j > win_c) {
            return 'J';
        }
        //+two result
        else if (win_b == win_c && win_b > win_j) {
            return 'B';
        } else if (win_b == win_j && win_b > win_c) {
            return 'B';
        } else if (win_c == win_j && win_c > win_b) {
            return 'C';
        }
        //+three reuslt
        else {
            return 'B';
        }
    }

    void jbc_cnt(char win_with_this) {
        switch (win_with_this) {
            case 'C':
                win_c++;
                break;

            case 'J':
                win_j++;
                break;

            case 'B':
                win_b++;
                break;

            default:
                break;
        }
    }



};
/*judge if the first person win, draw or lose*/
State judge(char first, char second) {
    if (first == second) {
        return DRAW;
    } else if (first == 'C' && second == 'J' || first == 'J' && second == 'B' || first == 'B' &&
               second == 'C') {
        return WIN;
    } else {
        return LOSE;
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
    int n;
    cin >> n;
    Game a, b;
    char first, second;

    while (n--) {
        cin >> first >> second;

        switch (judge(first, second)) {
            case WIN:
                a.win++;
                a.jbc_cnt(first);
                b.lose++;
                break;

            case DRAW:
                a.draw++;
                b.draw++;
                break;

            case LOSE:
                a.lose++;
                b.win++;
                b.jbc_cnt(second);
                break;

            default:
                break;
        }
    }

    cout << a.win << " " << a.draw << " " << a.lose << endl;
    cout << b.win << " " << b.draw << " " << b.lose << endl;
    cout << a.frequent() << " " << b.frequent();
    return 0;
}
