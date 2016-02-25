/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    source.cpp
* @version:      v1.0
* @Time:         2016-02-25 15:33:52
* @Description:
Logo 风之凌殇 [编辑资料] [登出]
主页
题目集
基本信息
题目列表
提交列表
排名
帮助
1022. Digital Library (30)
时间限制
1000 ms
内存限制
65536 kB
代码长度限制
16000 B
判题程序
Standard
作者
CHEN, Yue
A Digital Library contains millions of books, stored according to their titles, authors, key words of their abstracts, publishers, and published years. Each book is assigned an unique 7-digit number as its ID. Given any query from a reader, you are supposed to output the resulting books, sorted in increasing order of their ID's.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (<=10000) which is the total number of books. Then N blocks follow, each contains the information of a book in 6 lines:

Line #1: the 7-digit ID number;
Line #2: the book title -- a string of no more than 80 characters;
Line #3: the author -- a string of no more than 80 characters;
Line #4: the key words -- each word is a string of no more than 10 characters without any white space, and the keywords are separated by exactly one space;
Line #5: the publisher -- a string of no more than 80 characters;
Line #6: the published year -- a 4-digit number which is in the range [1000, 3000].
It is assumed that each book belongs to one author only, and contains no more than 5 key words; there are no more than 1000 distinct key words in total; and there are no more than 1000 distinct publishers.

After the book information, there is a line containing a positive integer M (<=1000) which is the number of user's search queries. Then M lines follow, each in one of the formats shown below:

1: a book title
2: name of an author
3: a key word
4: name of a publisher
5: a 4-digit number representing the year
Output Specification:

For each query, first print the original query in a line, then output the resulting book ID's in increasing order, each occupying a line. If no book is found, print "Not Found" instead.

Sample Input:
3
1111111
The Testing Book
Yue Chen
test code debug sort keywords
ZUCS Print
2011
3333333
Another Testing Book
Yue Chen
test code sort keywords
ZUCS Print2
2012
2222222
The Testing Book
CYLL
keywords debug book
ZUCS Print2
2011
6
1: The Testing Book
2: Yue Chen
3: keywords
4: ZUCS Print
5: 2011
3: blablabla
Sample Output:
1: The Testing Book
1111111
2222222
2: Yue Chen
1111111
3333333
3: keywords
1111111
2222222
3333333
4: ZUCS Print
1111111
5: 2011
1111111
2222222
3: blablabla
Not Found
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
#include <queue>
#include <random>
#include <set>
#include <cstring>
#include <cstdio>
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
//struct Book {
//  int id;
//  string title;
//  string author;
//  vector<string> keywords;
//  string publisher;
//  string year;
//};
//
//struct Title {
//  string title;
//  vector<int> ids;
//};
//struct Author {
//  string author;
//  vector<int> ids;
//};
//struct Keyword {
//  string keyword;
//  vector<int> ids;
//};
//struct Publisher {
//  string publisher;
//  vector<int> ids;
//};
//struct Year {
//  string year;
//  vector<int> ids;
//};
//enum CMD {
//  TITLE = '1',
//  AUTHOR = '2',
//  KEY_WORD = '3',
//  PUBLISHER = '4',
//  YEAR = '5'
//};
//
//
//int main() {
//  #pragma region GET_INPUT
//  {
//#ifndef ONLINE_JUDGE
//      freopen("test.in", "r", stdin);
//      freopen("test.out", "w", stdout);
//#endif
//  }
//  #pragma endregion
//  int n;
//  cin >> n;
//  vector<Book> books;
//  vector<Title> titles;
//  map<string, int> util_title;
//  vector<Author> authors;
//  map<string, int> util_author;
//  vector<Keyword> keywords;
//  map<string, int> util_keyword;
//  vector<Publisher> publishers;
//  map<string, int> util_publisher;
//  vector<Year> years;
//  map<string, int> util_year;
//
//  for (int i = 0; i < n; ++i) {
//      Book tmp;
//      cin >> tmp.id;
//      cin.ignore();
//      getline(cin, tmp.title);
//
//      if (util_title.find(tmp.title) != util_title.end()) {
//          int index = util_title[tmp.title];
//          titles[index].ids.push_back(tmp.id);
//      } else {
//          Title t;
//          t.title = tmp.title;
//          t.ids.push_back(tmp.id);
//          titles.push_back(t);
//          util_title[tmp.title] = titles.size() - 1;
//      }
//
//      getline(cin, tmp.author);
//
//      if (util_author.find(tmp.author) != util_author.end()) {
//          int index = util_author[tmp.author];
//          authors[index].ids.push_back(tmp.id);
//      } else {
//          Author t;
//          t.author = tmp.author;
//          t.ids.push_back(tmp.id);
//          authors.push_back(t);
//          util_author[tmp.author] = authors.size() - 1;
//      }
//
//      //keywords
//      string key_words;
//      getline(cin, key_words);
//      int pos, last = 0;
//      string key_word;
//
//      while ((pos = key_words.find(' ', last)) != -1) {
//          key_word = key_words.substr(last, pos - last);
//          tmp.keywords.push_back(key_word);
//          last = pos + 1;
//      }
//
//      //last keyword
//      key_word = key_words.substr(last);
//      tmp.keywords.push_back(key_word);
//
//      for (auto keyword : tmp.keywords) {
//          if (util_keyword.find(keyword) != util_keyword.end()) {
//              int index = util_keyword[keyword];
//              keywords[index].ids.push_back(tmp.id);
//          } else {
//              Keyword t;
//              t.keyword = keyword;
//              t.ids.push_back(tmp.id);
//              keywords.push_back(t);
//              util_keyword[keyword] = keywords.size() - 1;
//          }
//      }
//
//      getline(cin, tmp.publisher);
//
//      if (util_publisher.find(tmp.publisher) != util_publisher.end()) {
//          int index = util_publisher[tmp.publisher];
//          publishers[index].ids.push_back(tmp.id);
//      } else {
//          Publisher t;
//          t.publisher = tmp.publisher;
//          t.ids.push_back(tmp.id);
//          publishers.push_back(t);
//          util_publisher[tmp.publisher] = publishers.size() - 1;
//      }
//
//      getline(cin, tmp.year);
//
//      if (util_year.find(tmp.year) != util_year.end()) {
//          int index = util_year[tmp.year];
//          years[index].ids.push_back(tmp.id);
//      } else {
//          Year t;
//          t.year = tmp.year;
//          t.ids.push_back(tmp.id);
//          years.push_back(t);
//          util_year[tmp.year] = years.size() - 1;
//      }
//
//      books.push_back(tmp);
//  }
//
//  for (auto &title : titles) {
//      sort(title.ids.begin(), title.ids.end());
//  }
//
//  for (auto &author : authors) {
//      sort(author.ids.begin(), author.ids.end());
//  }
//
//  for (auto &keyword : keywords) {
//      sort(keyword.ids.begin(), keyword.ids.end());
//  }
//
//  for (auto &publisher : publishers) {
//      sort(publisher.ids.begin(), publisher.ids.end());
//  }
//
//  for (auto &year : years) {
//      sort(year.ids.begin(), year.ids.end());
//  }
//
//  int m;
//  cin >> m;
//  cin.ignore();
//
//  while (m--) {
//      string query;
//      vector<int> query_result;
//      getline(cin, query);
//      char cmd = query[0];
//      string para = query.substr(3);
//      int index;
//
//      switch (cmd) {
//      case TITLE:
//          if (util_title.find(para) != util_title.end()) {
//              index = util_title[para];
//              query_result = titles[index].ids;
//          }
//
//          break;
//
//      case AUTHOR:
//          if (util_author.find(para) != util_author.end()) {
//              index = util_author[para];
//              query_result = authors[index].ids;
//          }
//
//          break;
//
//      case KEY_WORD:
//          if (util_keyword.find(para) != util_keyword.end()) {
//              index = util_keyword[para];
//              query_result = keywords[index].ids;
//          }
//
//          break;
//
//      case PUBLISHER:
//          if (util_publisher.find(para) != util_publisher.end()) {
//              index = util_publisher[para];
//              query_result = publishers[index].ids;
//          }
//
//          break;
//
//      case YEAR:
//          if (util_year.find(para) != util_year.end()) {
//              index = util_year[para];
//              query_result = years[index].ids;
//          }
//
//          break;
//
//      default:
//          break;
//      }
//
//      cout << query << endl;
//
//      if (query_result.empty()) {
//          cout << "Not Found" << endl;
//      } else {
//          for (auto id : query_result) {
//              cout << id << endl;
//          }
//      }
//  }
//
//  return 0;
//}


enum CMD {
    TITLE = '1',
    AUTHOR = '2',
    KEY_WORD = '3',
    PUBLISHER = '4',
    YEAR = '5'
};



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
    cin.ignore();
    map<string, set<string>> titles;
    map<string, set<string>> authors;
    map<string, set<string>> keywords;
    map<string, set<string>> publishers;
    map<string, set<string>> years;
    string id, title, author, _keywords, publisher, year;
    char s[100];

    while(n--) {
        getline(cin, id);
        getline(cin, title);
        titles[title].insert(id);
        getline(cin, author);
        authors[author].insert(id);
        //        gets(s);
        //        char *p = strtok(s, " ");
        //
        //        while (p) {
        //            keywords[p].insert(id);
        //            p = strtok(NULL, " ");
        //        }
        //      //截取字符串出错
        getline(cin, _keywords);
        int pos, last = 0;
        string keyword;

        while((pos = _keywords.find(' ', last)) != -1) {
            keyword = _keywords.substr(last, pos - last);
            keywords[keyword].insert(id);
            last = pos + 1;
        }

        keyword = _keywords.substr(last);
        keywords[keyword].insert(id);
        getline(cin, publisher);
        publishers[publisher].insert(id);
        getline(cin, year);
        years[year].insert(id);
    }

    int m;
    cin >> m;
    cin.ignore();

    while(m--) {
        string query;
        getline(cin, query);
        char cmd = query[0];
        string para = query.substr(3);
        set<string> result;

        switch (cmd) {
            case TITLE:
                result = titles[para];
                break;

            case AUTHOR:
                result = authors[para];
                break;

            case KEY_WORD:
                result = keywords[para];
                break;

            case PUBLISHER:
                result = publishers[para];
                break;

            case YEAR:
                result = years[para];
                break;

            default:
                break;
        }

        cout << query << endl;

        if (result.empty()) {
            cout << "Not Found" << endl;
        } else {
            for (auto _id : result) {
                cout << _id << endl;
            }
        }
    }

    return 0;
}
