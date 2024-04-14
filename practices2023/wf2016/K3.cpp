
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

void solve() {
    int n; cin >> n;
    vi v(n); rep(i,0,n) cin >> v[i];
    int m = 0;
    rep(i,0,n) m += v[i];

    if (m == 2) {
        cout << "1\n";
        exit(0);
    }

    vi free(m+1);
    int ct = 0;
    rep(i,0,n) {
        rep(j,0,v[i]) {
            free[ct++] = v[i]-j;
        }
    }
    dbg(free);
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(100));

    int bst = 0;

    // base case
    rep(pos,0,m) {
        rep(end,pos+2,m) {
            if (free[pos] >= 2 && free[end-1] >= 2 && ((end - pos)&1)) {
                if (pos == 0 && end == m-1) bst=2;
                dp[pos][2].pb(end);
            }
            
        }
    }
    dbg(dp[0][2]);

    rep(K, 3, 100) {
        for (int pos = m-1; pos >= 0; --pos) {
            if (free[pos] < K) continue;
            if (pos + K >= m) continue;
            for (int x : dp[pos+K][K-1]) {
                if (free[x+1] < K) continue;
                dp[pos][K].pb(x+K);
                if (x+K+1 < m) {
                    for (int y : dp[x+K+1][K]) {
                        dp[pos][K].pb(y);
                    }
                }
            }
        }
    }
    
    rep(K,3,101) {
        if (free[0] < K) continue;
        if (K >= m) continue;
        if (free[m-K] < K) continue;
        for (int x : dp[K][K-1]) {
            if (x == m-K-1) bst = K;
        }
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
