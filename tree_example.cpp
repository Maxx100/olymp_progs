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
#include <queue>
#include <bitset>
#include <numeric>

#define ll long long
#define ull unsigned ll
#define INF 1e9 + 1
// #define INF INT64_MAX
#define EPS 0.0000001
#define m1 1000000007
#define m2 1000000009
#define ppp 31
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define files freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#define prec cout.precision(15)

using namespace std;

struct Tree {
    vector <ll> tree;
    ll size = 1;

    void init(ll n) {
        while (size < n)
            size *= 2;
        tree.resize(2 * size - 1, INF);
    }

    void build(ll x, ll lx, ll rx, vector <ll>& a, ll n) {
        if (rx - lx == 1) {
            if (lx < n) tree[x] = a[lx];
            return;
        }
        ll m = (lx + rx) / 2;
        build(2 * x + 1, lx, m, a, n);
        build(2 * x + 2, m, rx, a, n);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector <ll>& a) {
        ll sz = a.size();
        init(sz);
        build(0, 0, size, a, sz);
    }

    ll rs(ll x, ll lx, ll rx, ll l, ll r) {
        if (l >= rx || lx >= r) return INF;
        if (lx >= l && rx <= r) return tree[x];
        ll m = (lx + rx) / 2;
        return min(rs(2 * x + 1, lx, m, l, r),
            rs(2 * x + 2, m, rx, l, r));
    }

    ll rs(ll l, ll r) {
        return rs(0, 0, size, l, r);
    }

    void upd(ll x, ll lx, ll rx, ll pos, ll el) {
        if (rx - lx == 1) {
            tree[x] = el;
            return;
        }
        ll m = (lx + rx) / 2;
        if (pos < m) upd(2 * x + 1, lx, m, pos, el);
        else upd(2 * x + 2, m, rx, pos, el);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void upd(ll pos, ll el) {
        upd(0, 0, size, pos, el);
    }

};

struct object {
    ll money, ed, par;
    // iota(arr.begin(), arr.end(), 0);
};

void solve() {
    ll q; cin >> q;
    vector <object> country(q);
    for (auto& i : country) cin >> i.money;
    for (auto& i : country) cin >> i.ed;
    for (auto& i : country) cin >> i.par;

    ll n; cin >> n;
    vector <object> human(n);
    for (auto& i : human) cin >> i.money;
    for (auto& i : human) cin >> i.ed;
    for (auto& i : human) cin >> i.par;

    vector <ll> ans(n, INF);

    for (int i = 0; i < n; i++) {
        if (human[i].par && country[human[i].par - 1].par) {
            ans[i] = human[i].par;
        }
    }

    vector <pair<ll, ll>> noeduc, educ;
    for (ll i = 0; i < q; i++) {
        if (country[i].ed == 0) noeduc.push_back({country[i].money, i + 1});
        educ.push_back({country[i].money, i + 1});
    }

    sort(noeduc.begin(), noeduc.end());
    sort(educ.begin(), educ.end());
    vector <ll> noeduc1d, educ1d, anothernoeduc1d, anothereduc1d;
    for (auto& i : noeduc) noeduc1d.push_back(i.second);
    for (auto& i : educ) educ1d.push_back(i.second);
    for (auto& i : noeduc) anothernoeduc1d.push_back(i.first);
    for (auto& i : educ) anothereduc1d.push_back(i.first);


    Tree tree_educ, tree_noeduc;
    tree_noeduc.build(noeduc1d);
    tree_educ.build(educ1d);

    for (int i = 0; i < n; i++) {
        if (human[i].ed) {
            ll temp = upper_bound(anothereduc1d.begin(), anothereduc1d.end(), human[i].money) - anothereduc1d.begin();
            ll mn = tree_educ.rs(0, temp);
            ans[i] = min(ans[i], mn);
        }
        else {
            ll temp = upper_bound(anothernoeduc1d.begin(), anothernoeduc1d.end(), human[i].money) - anothernoeduc1d.begin();
            ll mn = tree_noeduc.rs(0, temp);
            ans[i] = min(ans[i], mn);
        }
    }

    for (auto& i : ans) {
        if (i == INF) cout << "0 ";
        else cout << i << " ";
    }
}

int main() {
    fast_io;
    ll t = 1;
    while (t--) solve();
    return 0;
}
