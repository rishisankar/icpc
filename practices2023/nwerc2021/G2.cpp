#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

int n, w;
vector<string> words;

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

vi test(int k, RMQ<int>& rmq) {
    // swapped dp: f(i) = min width required to fill first i words + last col len
    vector<pair<int,pii>> dp(n+1, {100000,{-2,-2}}); // best width, last col len, # things in last col
    dp[0] = {0,{-1,-1}};
    rep(x,1,n+1) {
        int bw = 100000, blen = -1, bi = -1;
        for (int i = 1; i <= min(x, k); ++i) { // i = # words in last col
            int clen = rmq.query(x-i, x);
            int nw = clen + dp[x-i].F + (x==i?0:1);
            if (nw < bw) {
                bw = nw;
                blen = clen;
                bi = i;
            }
        }
        dp[x] = {bw,{blen,bi}};
    }
    if (dp[n].F > w) return {};
    vi seq;
    int cur = n;
    while (cur > 0) {
        seq.pb(dp[cur].S.F);
        cur -= dp[cur].S.S;
    }
    reverse(all(seq));
    return seq;
}

void run() {
    cin >> n >> w;
    words.resize(n);
    vi wlen(n);
    rep(i,0,n) {
        cin >> words[i];
        wlen[i] = sz(words[i]);
    }
    RMQ rmq(wlen);
    // dbg(test(3,rmq));
    vi seq;
    int bst;
    int lo = 1, hi = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        vi ans = test(mid, rmq);
        if (sz(ans) > 0) {
            bst = mid;
            seq = ans;
            hi = mid - 1;
        } else lo = mid + 1;
    }
    print(bst, sz(seq));
    rep(i,0,sz(seq)) {
        cout << seq[i];
        if (i != sz(seq)-1) cout << ' ';
    }
    cout << '\n';
    vector<vector<int>> ans(sz(seq));
    int cc = 0;
    rep(i,0,n) {
        if (sz(ans[cc]) == bst) ++cc;
        while (wlen[i] > seq[cc]) ++cc;
        ans[cc].pb(i);
        words[i].resize(seq[cc], ' ');
    }
    vector<string> spc(sz(seq));
    rep(i,0,sz(seq)) spc[i].resize(seq[i],' ');
    dbg(ans);
    rep(i,0,bst) {
        rep(j,0,sz(seq)) {
            if (i < sz(ans[j])) {
                cout << words[ans[j][i]];
            } else {
                cout << spc[j];
            }
            cout << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}