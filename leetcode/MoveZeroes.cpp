/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 MoveZeroes.cpp
* @version:
* @Time:
* @Description:
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void moveZeroes(vector<int>& nums);

int main() {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	vector<int> test ;
	int count;
	cin >> count;
	for (int i = 0; i < count; i++) {
		test.clear();
		int num, temp;
		cin >> num;
		for (int j = 0; j < num; j++) {
			cin >> temp;
			test.push_back(temp);
		}
		moveZeroes(test);
		for (int k : test)
			cout << k << " ";
		cout << endl << "the " << i + 1 << " th test" << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}

void moveZeroes(vector<int>& nums) {
	int n = nums.size();
	// int i = 0, j = 0;//let i and j point to the first element
	// while (i != n ) {//if i point to the position which is one off the last element, stop the loop
	// 	while (nums[i] == 0 && i != n) //find the first nonzero element
	// 		++i;
	// 	if (i == n) //if no such element, break
	// 		break;
	// 	if (i > j) {//if it is the element after j,then copy nums[i] to nums[j] and set nums[i] to zero.
	// 		nums[j] = nums[i];//ANALYSIS:at most m(the number of nonzero)
	// 		nums[i] = 0;
	// 	}
	// 	++i; ++j;//update the i and j ANALYSIS: i at most n, and j is m(the number of nonzero)

	// }

	for (int i = 0, j = 0; i != n; ++i, ++j) {
		for (; nums[i] == 0 && i != n; ++i);
		if (i > j && i != n) {
			nums[j] = nums[i];
			nums[i] = 0;
		}
	}


}
