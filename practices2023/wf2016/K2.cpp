
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

    vector<vector<vector<uint16_t>>> dp(m, vector<vector<uint16_t>>(2));
    vector<vector<bitset<10000>>> dp2(m, vector<bitset<10000>>(2));


    // base case
    // rep(i,0,m-1) {
    //     for (int j = i+1; j < m; j += 2) {
    //         dp2[i][1][j] = 1;
    //     }
    // }

    // base case
    rep(pos,0,m) {
        rep(end,pos+2,m) {
            if (free[pos] >= 2 && free[end-1] >= 2 && ((end - pos)&1)) {
                dp2[pos][0][end] = 1;
            }
            
        }
    }
    if (dp2[0][0][m-1])bst=2;

    rep(K, 3, C) {
        for (int pos = m-K-1; pos >= 0; --pos) {
            dp2[pos][K&1].reset();
            if (free[pos] < K) continue;
            // for (int x : dp[pos+K][K-1]) {
            rep(x,0,m) {
                if (!dp2[pos+K][(K-1)&1][x]) continue;
                if ( free[x+1] < K) continue;
                dp2[pos][K&1][x+K] = 1;
                if (x+K+1 < m) {
                    // for (int y : dp[x+K+1][K]) {
                        // dp[pos][K].pb(y);
                    // }
                    dp2[pos][K&1] |= dp2[x+K+1][K&1];
                }
            }
        }

        if (free[0] < K) break;
        if (K >= m) break;
        if (free[m-K] < K) continue;
        if (dp2[K][(K-1)&1][m-K-1]) bst = K;
    }

    if (free[0] >= C && C < m){
    rep(pos,0,m) {
        rep(i,0,m) {
            if (dp2[pos][(C-1)&1][i])
            dp[pos][(C-1)&1].pb(i);
        }
    }
    }


    rep(K, C, 100) {
        if (free[0] < K) break;
        if (K >= m) break;

        for (int pos = m-K-1; pos >= 0; --pos) {
            dp[pos][K&1].clear();
            if (free[pos] < K) continue;
            for (int x : dp[pos+K][(K-1)&1]) {
                if ( free[x+1] < K) continue;
                dp[pos][K&1].pb(x+K);
                if (x+K+1 < m) {
                    for (int y : dp[x+K+1][K&1]) {
                        dp[pos][K&1].pb(y);
                    }
                }
            }
        }

        if (free[0] < K) break;
        if (K >= m) break;
        if (free[m-K] < K) continue;
        for (int x : dp[K][(K-1)&1]) {
            if (x == m-K-1) bst = K;
        }
    }

    // check K=100
    rep(K,100,101) {
        if (free[0] < K) continue;
        if (K >= m) continue;
        if (free[m-K] < K) continue;
        for (int x : dp[K][(K-1)&1]) {
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
