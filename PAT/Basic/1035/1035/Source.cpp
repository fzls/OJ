/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-17 13:06:42
* @Description:  1035. 插入与归并(25)
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
根据维基百科的定义：

插入排序是迭代算法，逐一获得输入数据，逐步产生有序的输出序列。每步迭代中，算法从输入序列中取出一元素，将之插入有序序列中正确的位置。如此迭代直到全部元素有序。

归并排序进行如下迭代操作：首先将原始序列看成N个只包含1个元素的有序子序列，然后每次迭代归并两个相邻的有序子序列，直到最后只剩下1个有序的序列。

现给定原始序列和由某排序算法产生的中间序列，请你判断该算法究竟是哪种排序算法？

输入格式：

输入在第一行给出正整数N (<=100)；随后一行给出原始序列的N个整数；最后一行给出由某排序算法产生的中间序列。这里假设排序的目标序列是升序。数字间以空格分隔。

输出格式：

首先在第1行中输出“Insertion Sort”表示插入排序、或“Merge Sort”表示归并排序；然后在第2行中输出用该排序算法再迭代一轮的结果序列。题目保证每组测试的结果是唯一的。数字间以空格分隔，且行末不得有多余空格。
输入样例1：
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
输出样例1：
Insertion Sort
1 2 3 5 7 8 9 4 6 0
输入样例2：
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
输出样例2：
Merge Sort
1 2 3 8 4 5 7 9 0 6
*
+----------------------------------------------------------
*/
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:66777216")
//#define DEBUG

#ifdef DEBUG
#define debug(format, ...) printf("[line:%d:@%s] "format, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define debug(...)
#endif

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

const string INSERTION = "Insertion Sort";
const string MERGE = "Merge Sort";
const string INSET_DEBUG = "INSERTION step ";
const string MERGE_DEBUG = "MERGE step with length ";

void print(const vector<int> &origin, string type, int id = -1) {
	cout << type ;

	if (id != -1) {
		cout << id;
	}

	cout << endl;

	for (int i = 0; i < origin.size(); ++i) {
		if (i != 0) {
			cout << " ";
		}

		cout << origin[i];
	}

	cout << endl;
}

bool is_insertion_then_print(vector<int> origin, vector<int> middle) {
	bool is_isertion = false;
	int n = static_cast<int>(origin.size());

	for (int i = 1; i < n ; ++i) {
		int key = origin[i], j;

		for (j = i - 1; j >= 0; --j)
			if (origin[j] > key) {
				origin[j + 1] = origin[j];
			} else {
				break;
			}

		origin[j + 1] = key;

		if (is_isertion) {
			print(origin, INSERTION);
			return true;
		}

		if (origin == middle ) {
			is_isertion = true;
		}
	}

	if (is_isertion) {
		print(origin, INSERTION);
		return true;
	}

	return false;
}

void merge_util(int ll, int lr, int rl, int rr, vector<int> &origin, vector<int> &tmp) {
	int i, j, index;

	for (i = ll, j = rl, index = ll; i <= lr && j <= rr;) {
		if (origin[i] <= origin[j]) {
			tmp[index++] = origin[i++];
		} else {
			tmp[index++] = origin[j++];
		}
	}

	for (; i <= lr; ) {
		tmp[index++] = origin[i++];
	}

	for (; j <= rr;) {
		tmp[index++] = origin[j++];
	}
}

void merge_sort(vector<int> &origin, vector<int> &tmp, int len) {
	int i;
	int n = static_cast<int>(origin.size());

	for (i = 0; n - i >= 2 * len; i += 2 * len) {
		//merge origin, store in tmp
		merge_util(i, i + len - 1, i + len, i + 2 * len - 1, origin, tmp);
	}

	if (n - i > len) {
		merge_util(i, i + len - 1, i + len, n - 1, origin, tmp);
	}
}

bool is_merge_then_print(vector<int> origin, vector<int> middle) {
	debug("another debug\n");
	debug("this is a test\n");
	int n = static_cast<int>(origin.size());
	vector<int> tmp(n);
	bool is_merge = false;

	for (int len = 1; 2 * len <= n;) {
		merge_sort(origin, tmp, len);
		len *= 2;

		if (is_merge) {
			print(tmp, MERGE);
			return true;
		}

		if (tmp == middle) {
			is_merge = true;
		}

		merge_sort(tmp, origin, len);
		len *= 2;

		if (is_merge) {
			print(origin, MERGE);
			return true;
		}

		if (origin == middle) {
			is_merge = true;
		}
	}

	if (is_merge) {
		print(origin, MERGE);
		return true;
	}

	return false;
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
	vector<int> origin(n), middle(n);

	for (int i = 0; i < n; ++i) {
		cin >> origin[i];
	}

	for (int i = 0; i < n; ++i) {
		cin >> middle[i];
	}

	debug("Debugging_Mode_was_enabled %s %d:%d:%d\n", "test the var", 12, 34, 56);
	is_insertion_then_print(origin, middle);
	is_merge_then_print(origin, middle);
	return 0;
}

