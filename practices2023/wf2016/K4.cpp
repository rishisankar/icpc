
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

const int C = 12;

void solve() {
    int n; cin >> n;
    vi v(n); rep(i,0,n) cin >> v[i];
    int m = 0;
    rep(i,0,n) m += v[i];
    vi free(m+1);
    int ct = 0;
    rep(i,0,n) {
        rep(j,0,v[i]) {
            free[ct++] = v[i]-j;
        }
    }
    dbg(free);

    if (m == 2) {
        cout << "1\n";
        exit(0);
    }

    int bst = 0;
    rep(K,2,101) {
        ll sm = K * (K+1) / 2;
        sm *= 2;
        if (sm > m) continue;
        if ((m - sm) & 1) continue;
        int pos = 0;
        bool ok = true;
        for (int i = K; i >= 1; --i) {
            if (free[pos] < i) {
                ok = false;
                break;
            }
            pos += i;
        }
        pos = m;
        for (int i = K; i >= 1; --i) {
            if (free[pos-i] < i) {
                ok = false;
                break;
            }
            pos -= i;
        }
        if (ok) bst = K;
    }
    if (bst == 0) {
        cout << "no quotation\n";
    } else {
        cout << bst << '\n';
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
