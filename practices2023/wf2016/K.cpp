
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

int n,m;

vector<vector<vector<int>>> dp;
vector<vector<bool>> dpM;
vi Free;

vi& ans(int pos, int k);

vi& ans_(int pos, int K) {

    if (K == 1) {
        for (int j = pos+1; j < m; j += 2) {
            dp[pos][K].pb(j);
        }
        return dp[pos][K];
    }

    if (Free[pos] < K) return dp[pos][K];
    if (pos + K >= m) return dp[pos][K];
    // for (int x : dp[pos+K][K-1]) {
    for (int x : ans(pos+K, K-1)) {
        if (Free[x+1] < K) continue;
        dp[pos][K].pb(x+K);
        if (x+K+1 < m) {
            for (int y : ans(x+K+1,K)) {
                dp[pos][K].pb(y);
            }
        }
    }
    return dp[pos][K];
}

vi& ans(int pos, int k) {
    if (dpM[pos][k]) {
        return dp[pos][k];
    }
    else {
        dpM[pos][k] = true;
        return ans_(pos,k);
    }
}

void solve() {
    cin >> n;
    vi v(n); rep(i,0,n) cin >> v[i];
    m = 0;
    rep(i,0,n) m += v[i];

    if (m == 2) {
        cout << "1\n";
        exit(0);
    }

    dp.resize(m, vector<vector<int>>(100));
    dpM.resize(m, vector<bool>(100));

    Free.resize(m+1);
    int ct = 0;
    rep(i,0,n) {
        rep(j,0,v[i]) {
            Free[ct++] = v[i]-j;
        }
    }

    for (int K = 100; K >= 2; --K) {
        if (Free[0] < K) continue;
        if (K >= m) continue;
        if (Free[m-K] < K) continue;
        for (int x : ans(K,K-1)) {
            if (x == m-K-1) {
                cout << K << '\n';
                return;
            }
        }
    }
    cout << "no quotation\n";
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
