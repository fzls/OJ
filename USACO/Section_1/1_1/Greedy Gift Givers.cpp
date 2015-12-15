/*
ID: fzls.zj1
PROG: Greedy Gift Givers.cpp
LANG: C++11
*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int toNumber(const string& name);


int main() {
	ifstream input("ride.in");
	ofstream output("ride.out");
	string comet, group;
	input >> comet >> group;
	int c_num, g_num;
	c_num = toNumber(comet);
	g_num = toNumber(group);
	if ((c_num - g_num) % 47 == 0 )
		output << "GO";
	else
		output << "STAY";
	output << endl;
	// cout << endl;
	system("pause");
	return 0;
}

int toNumber(const string& name) {
	int number = 1;
	for (unsigned i = 0; i < name.length(); i++) {
		number *= (name[i] - 'A' + 1);
	}
	return number;
}
