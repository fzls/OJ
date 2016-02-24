/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-24 14:12:17
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1016. Phone Bills (25)
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
A long-distance telephone company charges its customers by the following rules:

Making a long-distance call costs a certain amount per minute, depending on the time of day when the call is made. When a customer starts connecting a long-distance call, the time will be recorded, and so will be the time when the customer hangs up the phone. Every calendar month, a bill is sent to the customer for each minute called (at a rate determined by the time of day). Your job is to prepare the bills for each month, given a set of phone call records.

Input Specification:

Each input file contains one test case. Each case has two parts: the rate structure, and the phone call records.

The rate structure consists of a line with 24 non-negative integers denoting the toll (cents/minute) from 00:00 - 01:00, the toll from 01:00 - 02:00, and so on for each hour in the day.

The next line contains a positive number N (<= 1000), followed by N lines of records. Each phone call record consists of the name of the customer (string of up to 20 characters without space), the time and date (mm:dd:hh:mm), and the word "on-line" or "off-line".

For each test case, all dates will be within a single month. Each "on-line" record is paired with the chronologically next record for the same customer provided it is an "off-line" record. Any "on-line" records that are not paired with an "off-line" record are ignored, as are "off-line" records not paired with an "on-line" record. It is guaranteed that at least one call is well paired in the input. You may assume that no two records for the same customer have the same time. Times are recorded using a 24-hour clock.

Output Specification:

For each test case, you must print a phone bill for each customer.

Bills must be printed in alphabetical order of customers' names. For each customer, first print in a line the name of the customer and the month of the bill in the format shown by the sample. Then for each time period of a call, print in one line the beginning and ending time and date (dd:hh:mm), the lasting time (in minute) and the charge of the call. The calls must be listed in chronological order. Finally, print the total charge for the month in the format shown by the sample.

Sample Input:
10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10
10
CYLL 01:01:06:01 on-line
CYLL 01:28:16:05 off-line
CYJJ 01:01:07:00 off-line
CYLL 01:01:08:03 off-line
CYJJ 01:01:05:59 on-line
aaa 01:01:01:03 on-line
aaa 01:02:00:01 on-line
CYLL 01:28:15:41 on-line
aaa 01:05:02:24 on-line
aaa 01:04:23:59 off-line
Sample Output:
CYJJ 01
01:05:59 01:07:00 61 $12.10
Total amount: $12.10
CYLL 01
01:06:01 01:08:03 122 $24.40
28:15:41 28:16:05 24 $3.85
Total amount: $28.25
aaa 01
02:00:01 04:23:59 4318 $638.80
Total amount: $638.80
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
const string START = "on-line";
const string END = "off-line";
vector<int> prices(24);

void get_prices() {
    for (int i = 0; i < 24; ++i) {
        cin >> prices[i];
    }
}

struct Record {
    string time;
    string state;
    Record(string t = string(), string s = string()): time{t}, state{s} {
    }
};

struct PairedRecord {
    string startTime;
    string endTime;
    double cost;
    int duration;
    void compute_cost();
    void print() {
        cout << startTime.substr(3) << " " << endTime.substr(3) << " " << duration << " $" << setprecision(2) << fixed << cost << endl;
    }
    void getTime(int &month_s, int &day_s, int &hour_s, int &minute_s, string &startTime);


};

void PairedRecord::compute_cost() {
    cost = 0.0;
    duration = 0;
    int month_s, day_s, hour_s, minute_s;
    int month_e, day_e, hour_e, minute_e;
    getTime(month_s, day_s, hour_s, minute_s, startTime);
    getTime(month_e, day_e, hour_e, minute_e, endTime);

    for (int day = day_s; day <= day_e; ++day) {
        int hour_lower = day == day_s ? hour_s : 0;
        int hour_upper = day == day_e ? hour_e : 23;

        for (int hour = hour_lower; hour <= hour_upper; ++hour) {
            int minute_lower = hour == hour_s && day == day_s ? minute_s : 0;
            int minute_upper = hour == hour_e && day == day_e ? minute_e : 60;
            cost += 1.0 * (minute_upper - minute_lower) * prices[hour] / 100;
            duration += minute_upper - minute_lower;
        }
    }
}

void PairedRecord::getTime(int &month, int &day, int &hour, int &minute, string &time) {
    int lastOffByOne, first;
    //get month
    first = 0;
    lastOffByOne = time.find(':', first);
    month = atoi(time.substr(first, lastOffByOne - first).data());
    //get day
    first = lastOffByOne + 1;
    lastOffByOne = time.find(':', first);
    day = atoi(time.substr(first, lastOffByOne - first).data());
    //get hour
    first = lastOffByOne + 1;
    lastOffByOne = time.find(':', first);
    hour = atoi(time.substr(first, lastOffByOne - first).data());
    //get minute
    first = lastOffByOne + 1;
    lastOffByOne = time.find(':', first);
    minute = atoi(time.substr(first, lastOffByOne - first).data());
}

struct Bill {
    string name;
    vector<Record> records;
    vector<PairedRecord> pairedRecords;
    double totalCost;
};
bool cmp_record(const Record &lhs, const Record &rhs) {
    return lhs.time < rhs.time;
}
void compute_bills(vector<Bill> &bills) {
    for(auto &bill : bills) {
        sort(bill.records.begin(), bill.records.end(), cmp_record);
        Record start, end;
        int index = 0;

        while(true) {
            //find first start which followed by end
            for (; index < bill.records.size() - 1 && !(bill.records[index].state == START && bill.records[index + 1].state == END); ++index)
                ;

            if (index >= bill.records.size() - 1) {
                break;
            } else {
                start = bill.records[index];
                end = bill.records[index + 1];
                index += 2;
                PairedRecord tmp;
                tmp.startTime = start.time;
                tmp.endTime = end.time;
                tmp.compute_cost();
                bill.pairedRecords.push_back(tmp);
            }
        }

        bill.totalCost = 0.0;

        for (int i = 0; i < bill.pairedRecords.size(); ++i) {
            bill.totalCost += bill.pairedRecords[i].cost;
        }
    }
}
bool cmp_bill(const Bill &lhs, const Bill &rhs) {
    return lhs.name < rhs.name;
}

void print_result(vector<Bill> &bills) {
    // sort by name
    sort(bills.begin(), bills.end(), cmp_bill);

    for(auto bill : bills) {
        //?note: although in the Input Specification it is said that
        //? "It is guaranteed that at least one call is well paired in the input."
        //? but actuallly in the test data , it is not guaranteed :(
        if(bill.pairedRecords.empty()) {
            continue;
        }

        string month = bill.pairedRecords[0].startTime.substr(0, 2);
        cout << bill.name << " " << month << endl;

        for (auto i = bill.pairedRecords.begin(); i != bill.pairedRecords.end(); ++i) {
            i->print();
        }

        cout << "Total amount: $" << setprecision(2) << fixed << bill.totalCost << endl;
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
    get_prices();
    int records_n;
    cin >> records_n;
    vector<Bill> bills;
    map<string, int> nameToIndex;

    while(records_n--) {
        string name, time, state;
        cin >> name >> time >> state;

        if(nameToIndex.find(name) == nameToIndex.end()) {
            nameToIndex[name] = bills.size();
            Bill tmp;
            tmp.name = name;
            tmp.records.push_back(Record(time, state));
            bills.push_back(tmp);
        } else {
            int index = nameToIndex[name];
            bills[index].records.push_back(Record(time, state));
        }
    }

    //process data
    compute_bills(bills);
    //output result
    print_result(bills);
    return 0;
}
