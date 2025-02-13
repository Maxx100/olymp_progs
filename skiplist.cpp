/*#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma warning(disable: 4996)*/

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
#include <cstdint> // for int**_max/min, only for yandex :/

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

class SkipList {
private:
    struct Node {
        ll value;
        vector <Node*> next;
    };

    ll max_lvl = 10, lvl = 0;
    Node* root;
public:
    SkipList() {
        root = new Node;
        root->value = -1;
        root->next.resize(max_lvl + 1, nullptr);
    }

    void insert(ll value) {
        if (exists(value)) return;
        vector <Node*> _new(max_lvl + 1, nullptr);
        Node* _temp = root;

        for (int i = lvl; i >= 0; --i) {
            while (_temp->next[i] != nullptr && _temp->next[i]->value < value) _temp = _temp->next[i];
            _new[i] = _temp;
        }
        _temp = _temp->next[0];

        ll temp = 0;
        while (rand() / RAND_MAX < 0.5 && temp < max_lvl) temp++;
        
        if (temp > lvl) {
            for (int i = lvl + 1; i <= temp; i++) _new[i] = root;
            lvl = temp;
        }

        Node* newNode = new Node;
        newNode->value = value;
        newNode->next.resize(temp + 1, nullptr);

        for (int i = 0; i <= temp; ++i) {
            newNode->next[i] = _new[i]->next[i];
            _new[i]->next[i] = newNode;
        }
    }

    bool exists(ll value) {
        Node* _temp = root;
        for (int i = lvl; i >= 0; --i) {
            while (_temp->next[i] != nullptr && _temp->next[i]->value < value) {
                _temp = _temp->next[i];
            }
        }
        _temp = _temp->next[0];
        return _temp != nullptr && _temp->value == value;
    }

    void remove(ll value) {
        if (!exists(value)) return;

        vector<Node*> _new(max_lvl + 1, nullptr);
        Node* _temp = root;

        for (int i = lvl; i >= 0; --i) {
            while (_temp->next[i] != nullptr && _temp->next[i]->value < value) _temp = _temp->next[i];
            _new[i] = _temp;
        }

        _temp = _temp->next[0];

        if (_temp != nullptr && _temp->value == value) {
            for (int i = 0; i <= lvl; ++i) {
                if (_new[i]->next[i] != _temp) break;
                _new[i]->next[i] = _temp->next[i];
            }

            while (lvl > 0 && root->next[lvl] == nullptr) lvl--;
            delete _temp;
        }
    }
};

void solve() {
    srand(1337);
    SkipList lst;
    for (int i = 0; i < 5; i++) lst.insert(i);
    for (int i = 15; i < 20; i++) lst.insert(i);
    for (int i = 30; i > 25; i--) lst.insert(i);
    lst.insert(47); lst.insert(21); lst.insert(22); lst.insert(6);

    vector <ll> to_check = { 3, 4, 30, 29, 18, 16, 20, 47, 50 };

    for (auto& i : to_check) cout << lst.exists(i) << " ";
    cout << "\n";

    lst.remove(47); lst.remove(3);
    for (auto& i : to_check) cout << lst.exists(i) << " ";
    cout << "\n";

    lst.remove(4); lst.remove(53);
    for (auto& i : to_check) cout << lst.exists(i) << " ";
    cout << "\n";
}

int main() {
    fast_io;
    ll t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}
