//version 2
//for this question set the size limit to 100000, so we can use more space in change of time
/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <fzls.zju@gmail.com>
* @FILE NAME:    Source.cpp
* @version:
* @Time:         2016-02-16 14:37:03
* @Description:  1025. 反转链表 (25)
时间限制
300 ms
内存限制
65536 kB
代码长度限制
8000 B
判题程序
Standard
作者
CHEN, Yue
给定一个常数K以及一个单链表L，请编写程序将L中每K个结点反转。例如：给定L为1→2→3→4→5→6，K为3，则输出应该为3→2→1→6→5→4；如果K为4，则输出应该为4→3→2→1→5→6，即最后不到K个元素不反转。

输入格式：

每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址、结点总个数正整数N(<= 105)、以及正整数K(<=N)，即要求反转的子链结点的个数。结点的地址是5位非负整数，NULL地址用-1表示。

接下来有N行，每行格式为：

Address Data Next

其中Address是结点地址，Data是该结点保存的整数数据，Next是下一结点的地址。

输出格式：

对每个测试用例，顺序输出反转后的链表，其上每个结点占一行，格式与输入相同。

输入样例：
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218
输出样例：
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1

*
+----------------------------------------------------------
*/
#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(linker, "/STACK:66777216")

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int null = -1;

struct Node {
    int address;
    int data;
    int next;

    Node(int a = null, int d = 0, int n = null) : address{ a }, data{ d }, next{ n } {
    }
    inline bool operator == (const Node &right) {
        return this->address == right.address && this->data == right.data
               && this->next == right.next;
    }
};

void print(Node &node) {
    cout << setw(5) << setfill('0') << node.address << " " << node.data << " ";

    if (node.next != -1) {
        cout << setw(5) << setfill('0');
    }

    cout << node.next << endl;
}
const int BEFORE_HEAD = -2;

void get_input(Node &head, vector<Node> &nodes, int total) {
    Node tmp;

    for (int i = 0; i < total; ++i) {
        cin >> tmp.address >> tmp.data >> tmp.next;
        nodes[tmp.address] = tmp;

        if (tmp.address == head.address) {
            head = tmp;
        }
    }
}

void extract_k_node(vector<Node> &nodes, int k, vector<int> &keysOfkNodes, bool &getKNode,
                    Node &node) {
    keysOfkNodes.clear();

    for (int i = 0; i < k; ++i) {
        if (node.next != null) {
            keysOfkNodes.push_back(node.address);
            node = nodes[node.next];
        } else {
            if (i == k - 1) {
                keysOfkNodes.push_back(node.address);
            } else {
                getKNode = false;
                break;
            }
        }
    }
}

void reverse(Node &head, vector<Node> &nodes, int k, vector<int> &keysOfkNodes, int &pre,
             bool &getKNode) {
    //reverse k node
    //store the next node of the k-1
    int next_address = nodes[keysOfkNodes[k - 1]].next;

    //change 1~k-1's next
    for (int i = 1; i < k; ++i) {
        nodes[keysOfkNodes[i]].next = keysOfkNodes[i - 1];
    }

    //change 0's next to next_node_to_k
    nodes[keysOfkNodes[0]].next = next_address;

    //change pre's next to k-1

    if (pre == BEFORE_HEAD) {
        head = nodes[keysOfkNodes[k - 1]];
    } else {
        nodes[pre].next = keysOfkNodes[k - 1];
    }

    //store the last one as pre to the next k item
    pre = keysOfkNodes[0];
    //set the flag to true
    getKNode = true;
}

void k_reverse(Node &head, vector<Node> &nodes, int k) {
    auto keysOfkNodes = vector<int>(k);
    int pre = BEFORE_HEAD;
    bool getKNode = true;

    for (auto node = head; node.next != null;) {
        //get k node
        extract_k_node(nodes, k, keysOfkNodes, getKNode, node);

        if (getKNode) {
            reverse(head, nodes, k, keysOfkNodes, pre, getKNode);
        }
    }
}

void print_result(Node head, vector<Node> &nodes) {
    for (auto node = head;; node = nodes[node.next]) {
        print(node);

        if (node.next == null) {
            break;
        }
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
    Node head;
    auto nodes = vector<Node>(100000);
    int total, k;
    cin >> head.address >> total >> k;
    get_input(head, nodes, total);
    k_reverse(head, nodes, k);
    print_result(head, nodes);
    return 0;
}


///*
//+----------------------------------------------------------
//*
//* @authors: 风之凌殇 <fzls.zju@gmail.com>
//* @FILE NAME:    Source.cpp
//* @version:
//* @Time:         2016-02-16 14:37:03
//* @Description:  1025. 反转链表 (25)
//时间限制
//300 ms
//内存限制
//65536 kB
//代码长度限制
//8000 B
//判题程序
//Standard
//作者
//CHEN, Yue
//给定一个常数K以及一个单链表L，请编写程序将L中每K个结点反转。例如：给定L为1→2→3→4→5→6，K为3，则输出应该为3→2→1→6→5→4；如果K为4，则输出应该为4→3→2→1→5→6，即最后不到K个元素不反转。
//
//输入格式：
//
//每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址、结点总个数正整数N(<= 105)、以及正整数K(<=N)，即要求反转的子链结点的个数。结点的地址是5位非负整数，NULL地址用-1表示。
//
//接下来有N行，每行格式为：
//
//Address Data Next
//
//其中Address是结点地址，Data是该结点保存的整数数据，Next是下一结点的地址。
//
//输出格式：
//
//对每个测试用例，顺序输出反转后的链表，其上每个结点占一行，格式与输入相同。
//
//输入样例：
//00100 6 4
//00000 4 99999
//00100 1 12309
//68237 6 -1
//33218 3 00000
//99999 5 68237
//12309 2 33218
//输出样例：
//00000 4 33218
//33218 3 12309
//12309 2 00100
//00100 1 99999
//99999 5 68237
//68237 6 -1
//
//*
//+----------------------------------------------------------
//*/
//#define _CRT_SECURE_NO_DEPRECATE
//#pragma comment(linker, "/STACK:66777216")
//
//#include <algorithm>
//#include <ctime>
//#include <deque>
//#include <functional>
//#include <iomanip>
//#include <iostream>
//#include <list>
//#include <map>
//#include <random>
//#include <set>
//#include <stack>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//const int null = -1;
//
//struct Node {
//    int address;
//    int data;
//    int next;
//
//    Node(int a = null, int d = 0, int n = null): address{a}, data{d}, next{n} {
//    }
//    inline bool operator == (const Node &right) {
//        return this->address == right.address && this->data == right.data
//               && this->next == right.next;
//    }
//};
//
//void print(Node &node) {
//    cout << setw(5) << setfill('0') << node.address << " " << node.data << " ";
//
//    if(node.next != -1) {
//        cout << setw(5) << setfill('0');
//    }
//
//    cout << node.next << endl;
//}
//const int BEFORE_HEAD = -2;
//
//void get_input(Node &head, map<int, Node> &nodes_map, int total) {
//    Node tmp;
//
//    for (int i = 0; i < total; ++i) {
//        cin >> tmp.address >> tmp.data >> tmp.next;
//        nodes_map[tmp.address] = tmp;
//
//        if (tmp.address == head.address) {
//            head = tmp;
//        }
//    }
//}
//
//void extract_k_node(map<int, Node> &nodes_map, int k, vector<int> &keysOfkNodes, bool &getKNode,
//                    Node &node) {
//    keysOfkNodes.clear();
//
//    for (int i = 0; i < k; ++i) {
//        if(node.next != null) {
//            keysOfkNodes.push_back(node.address);
//            node = nodes_map[node.next];
//        } else {
//            if (i == k - 1) {
//                keysOfkNodes.push_back(node.address);
//            } else {
//                getKNode = false;
//                break;
//            }
//        }
//    }
//}
//
//void reverse(Node &head, map<int, Node> &nodes_map, int k, vector<int> &keysOfkNodes, int &pre,
//             bool &getKNode) {
//    //reverse k node
//    //store the next node of the k-1
//    int next_address = nodes_map[keysOfkNodes[k - 1]].next;
//
//    //change 1~k-1's next
//    for (int i = 1; i < k; ++i) {
//        nodes_map[keysOfkNodes[i]].next = keysOfkNodes[i - 1];
//    }
//
//    //change 0's next to next_node_to_k
//    nodes_map[keysOfkNodes[0]].next = next_address;
//
//    //change pre's next to k-1
//
//    if(pre == BEFORE_HEAD) {
//        head = nodes_map[keysOfkNodes[k - 1]];
//    } else {
//        nodes_map[pre].next = keysOfkNodes[k - 1];
//    }
//
//    //store the last one as pre to the next k item
//    pre = keysOfkNodes[0];
//    //set the flag to true
//    getKNode = true;
//}
//
//void k_reverse(Node &head, map<int, Node> &nodes_map, int k) {
//    auto keysOfkNodes = vector<int>(k);
//    int pre = BEFORE_HEAD;
//    bool getKNode = true;
//
//    for (auto node = head; node.next != null;) {
//        //get k node
//        extract_k_node(nodes_map, k, keysOfkNodes, getKNode, node);
//
//        if(getKNode) {
//            reverse(head, nodes_map, k, keysOfkNodes, pre, getKNode);
//        }
//    }
//}
//
//void print_result(Node head, map<int, Node> &nodes_map) {
//    for (auto node = head;; node = nodes_map[node.next]) {
//        print(node);
//
//        if (node.next == null) {
//            break;
//        }
//    }
//}
//
//int main() {
//    #pragma region GET_INPUT
//    {
//        #ifndef ONLINE_JUDGE
//        freopen("test.in", "r", stdin);
//        freopen("test.out", "w", stdout);
//        #endif
//    }
//    #pragma endregion
//    Node head;
//    map<int, Node> nodes_map;
//    int total, k;
//    cin >> head.address >> total >> k;
//    get_input(head, nodes_map, total);
//    k_reverse(head, nodes_map, k);
//    print_result(head, nodes_map);
//    return 0;
//}

