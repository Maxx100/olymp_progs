// only if necessary
/*#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma warning(disable:4996)*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <bitset>
#include <numeric>
// for int**_max/min, only for yandex contests
// #include <cstdint>

#define ll long long
#define ull unsigned long long
#define INF INT64_MAX
#define EPS 0.00000001
#define m1 1000000007
#define m2 1000000009
#define p 27
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define files freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#define prec cout.precision(15)

using namespace std;

class Stack {
private:
    int _size;
    struct Node {
        int value, min;
        Node* prev;
    };
    Node* node;
public:
    Stack() {
        _size = 0;
        node = new Node[sizeof(Node)];
        node->value = NULL;
        node->min = NULL;
        node->prev = nullptr;
    }
    
    int top() {
        if (_size == 0) {} // exception
        return node->value;
    }

    int pop() {
        if (_size == 0) {} // exception
        int value = node->value;
        if (_size == 1) {
            node->value = NULL;
            node->min = NULL;
        } else {
            Node* temp_node = node;
            node = node->prev;
            delete temp_node;
        }
        _size--;
        return value;
    }

    int currentMin() {
        if (_size == 0) {} // exception
        return node->min;
    }

    void push(int value) {
        if (_size == 0) {
            node->value = value;
            node->min = value;
        } else {
            Node* new_node = new Node[sizeof(Node)];
            new_node->value = value;
            new_node->min = min(value, node->min);
            new_node->prev = node;
            node = new_node;
        }
        _size++;
    }

    int size() {
        return _size;
    }
};

class Queue {
private:
    Stack pushStack, popStack;
    int pushStack_value, popStack_value;
public:
    Queue() {
        pushStack_value = NULL;
        popStack_value = NULL;
    }
    int front() {
        if (popStack.size() == 0) return pushStack_value;
        return popStack.top();
    }
    
    int back() {
        if (pushStack.size() == 0) return popStack_value;
        return pushStack.top();
    }

    int pop() {
        if (popStack.size() == 0) {
            popStack_value = pushStack.top();
            pushStack_value = NULL;
            while (pushStack.size() != 0)
                popStack.push(pushStack.pop());
        }
        return popStack.pop();
    }

    int currentMin() {
        if (pushStack.size() == 0 && popStack.size() == 0) {} // exception
        if (pushStack.size() == 0) return popStack.currentMin();
        if (popStack.size() == 0) return pushStack.currentMin();
        return min(pushStack.currentMin(), popStack.currentMin());
    }

    void push(int value) {
        if (pushStack.size() == 0) pushStack_value = value;
        pushStack.push(value);
    }
};

bool check(Queue q, queue <int> q2) {
    if (q.back() != q2.back()) return false;
    if (q.front() != q2.front()) return false;
    return true;
}

void solve() {
    Queue q;
    
}

int main() {
    fast_io;
    ll t = 1; // cin >> t; // if each test contains several cases
    while (t--) solve();
    return 0;
}   
