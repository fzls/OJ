/*
ID: fzls.zj1
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

struct Person
{
	Person(string n = ""/*, int m = 0*/, int g = 0, int r = 0): name(n)/*, money(m)*/, give(g), receive(r) {}
	string name;
	// int money;
	int give;
	int receive;
};


int main() {
	ifstream input("gift1.in");
	ofstream output("gift1.out");
	int np;
	input >> np;
	input.ignore();
	std::map<string, Person> friends ;
	std::vector<string> vfriends ;

	for (int i = 0; i < np; i++ ) {
		Person person;
		getline(input, person.name);
		vfriends.push_back(person.name);
		friends[person.name] = person;
	}
	// for (int i = 0; i < np; i++) {
	// 	cout << vfriends[i]  << endl;
	// 	cout << friends[vfriends[i]].money  << endl;
	// }

	for (int i = 0; i < np; i++) {
		string giver;
		int total_money, num_of_friends;
		getline(input, giver);
		input >> total_money >> num_of_friends;
		input.ignore();
		// cout << "giver : " << giver << endl;
		if (num_of_friends != 0) {
			friends[giver].give += total_money / num_of_friends * num_of_friends;
		}

		for (int j = 0; j < num_of_friends; j++) {
			string receiver;
			getline(input, receiver);
			// cout << "receiver : " << receiver << " j " << j << endl;
			friends[receiver].receive += total_money / num_of_friends;
		}
		// cout << "i : " << i << endl;
	}



	for (int i = 0; i < np; i++) {
		output << vfriends[i] << " " << friends[vfriends[i]].receive - friends[vfriends[i]].give << endl;
	}



	// cout << endl;
	// system("pause");
	return 0;
}

