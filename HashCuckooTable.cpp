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

class HashCuckooTable {
private:
    vector <ll> _table;
    size_t _size;

    ll mask1 = 14729323;
    ll mask2 = 75822853;

    hash <ll> hasher{};

    size_t hash1(ll num) { return hasher(num ^ mask1) % _table.size(); }

    size_t hash2(ll num) { return hasher(num ^ mask2) % _table.size(); }

    void increase_table() {
        if ((double)_size / _table.size() < 0.5) return;
        cout << "----- INCREASE -----\n";
        vector <ll> temp = move(_table);
        _table.assign(temp.size() * 2, INF);
        for (auto i : temp) {
            if (i != INF) {
                _size--;
                insert(i);
            }
        }
    }

    void rehash(int num) {
        cout << "----- REHASH -----\n";
        mask1 = (mask1 + 2) % 1111111111 + 12462;
        mask2 = (mask2 + 4) % 1111111111 + 12462;

        vector <ll> temp = move(_table);
        _table.assign(temp.size() * 2, INF);
        for (auto i : temp) {
            if (i != INF) {
                _size--;
                insert(i);
            }
        }
        _size--;
        insert(num);
    }
public:
    HashCuckooTable() : _table(10, INF), _size(0) {}

    void insert(ll num) {
        _size++;
        size_t temp = hash1(num);
        if (_table[temp] == INF || _table[temp] == num) {
            _table[temp] = num;
            increase_table();
            return;
        }
        temp = hash2(num);
        if (_table[temp] == INF || _table[temp] == num) {
            _table[temp] = num;
            increase_table();
            return;
        }
        rehash(num);
    }

    bool exist(ll num) {
        if (_table[hash1(num)] == num) return true;
        if (_table[hash2(num)] == num) return true;
        return false;
    }

    void info() {
        cout << "\nSize: " << _size << "\n";
        cout << "Cap:  " << _table.size() << "\n";
        for (auto i : _table) {
            // if (i == INF) cout << ".\t";
            // else cout << i << "\t";
            if (i != INF) cout << i << " ";
        }
        cout << "\n\n";
    }
};

void solve() {
    HashCuckooTable bird;

    for (int i = 0; i < 30; i++) {
        bird.info();
        cout << "Add: " << i << "\n";
        bird.insert(i);
    }

}

int main() {
    fast_io;
    ll t = 1; // cin >> t;
    while (t--) solve();
    return 0;
}
