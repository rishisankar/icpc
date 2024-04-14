
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
typedef pair<ll,ll> pll;
void fail() {
    cout << "impossible\n";
    exit(0);
}
void solve() {
    int n; cin >> n;
    vector<pll> v(n);
    vector<string> inp(n);
    rep(i,0,n) {
        cin >> inp[i];
        ll lo = 0, hi = 1e8, bst = hi;
        while (lo <= hi) {
            ll m = (lo+hi)/2;
            ll ct = m;
            bool ok = true;
            rep(j,0,sz(inp[i])) {
                if (inp[i][j] == '(') {
                    ct++;
                } else {
                    ct--;
                }
                if (ct < 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                bst = m;
                hi = m-1;
            } else {
                lo = m+1;
            }
        }
        v[i].F = bst;
        int ct = 0;
        rep(j,0,sz(inp[i])) {
            if (inp[i][j] == '(') {
                ct++;
            } else {
                ct--;
            }
        }
        v[i].S = ct;
    }
    dbg(v);
    vector<pair<pll,int>> pos;
    vector<pair<pll,int>> neg;
    rep(i,0,n) {
        if (v[i].S >= 0) {
            pos.pb({v[i], i});
        } else {
            neg.pb({v[i], i});
        }
    }
    sort(all(pos));
    sort(all(neg), [](auto p1, auto p2) {
        return p1.F.F + p1.F.S > p2.F.F + p2.F.S;
    });

    dbg(pos);
    dbg(neg);

    ll yd = 0;
    vi perm;
    for (auto p : pos) {
        if (p.F.F > yd) fail();
        yd += p.F.S;
        perm.pb(p.S);
    }
    dbg(yd);
    for (auto p : neg) {
        if (p.F.F > yd) fail();
        yd += p.F.S;
        perm.pb(p.S);
    }
    dbg(yd);
    if (yd != 0) fail();
    for (int i : perm) cout << (i+1) << ' ';
    cout << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
