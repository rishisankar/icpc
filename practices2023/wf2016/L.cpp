#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef pair<ll,ll> pll;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
	return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
	os << '{';
	string sep;
	for (const auto &x: v) os << sep << x, sep = ", ";
	return os << '}';
}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

ll minReq(vector<pll> neg) {
    int n = sz(neg);
    if (n == 0) return 0;
    ll lo = 0, hi = 1e18, bst = hi;
    sort(all(neg), [](pll p1, pll p2) {
        return p1.S > p2.S;
    });
    while (lo <= hi) {
        ll m = lo + (hi-lo)/2;
        ll val = m;
        bool ok = true;
        for (auto p : neg) {
            if (val < p.F) {
                ok = false;
                break;
            } else {
                val -= (p.F-p.S);
            }
        }
        if (ok) {
            bst = m;
            hi = m-1;
        } else {
            lo = m + 1;
        }
    }
    return bst;
}

void solve() {
    int n; cin >> n;
    vector<pll> v(n);
    rep(i,0,n) { cin >> v[i].F >> v[i].S; }
    sort(all(v));
    dbg(v);
    
    vector<pll> neg;
    rep(i,0,n) {
        if (v[i].S - v[i].F < 0) {
            neg.pb(v[i]);
        }
    }
    ll mr = minReq(neg);
    int N = n - sz(neg);

    ll lo = 1, hi = 1e18, bst = hi;
    while (lo <= hi) {
        ll m = lo + (hi-lo)/2;

        ll space = m;
        bool ok = true;

        vector<pll> pos;
        rep(i,0,n) {
            if (v[i].S - v[i].F >= 0) {
                pos.pb(v[i]);
            }
        }

        sort(all(pos));
        reverse(all(pos));

        while (!pos.empty()) {
            pll t = pos.back();
            pos.pop_back();
            if (t.F > space) {
                ok = false;
                break;
            }
            space += (t.S - t.F);
        }

        if (space < mr) ok = false;
        if (ok) {
            bst = m;
            hi = m - 1;
        } else {
            lo = m + 1;
        }
    }
    cout << bst << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}