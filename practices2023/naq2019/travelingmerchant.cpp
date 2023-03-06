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

int n;
vector<pll> v;

struct D {
    D() : len(0) {}
    int len;
    ll bestBuy[7];
    ll bestSell[7];
    ll buy[7];
    ll sell[7];
};

struct Tree {
	typedef D T;
	const T unit;
	T f(T a, T b) { 
        if (a.len == 0) return b;
        if (b.len == 0) return a;
        T ans;
        ans.len = a.len + b.len;
        rep(i,0,7) {
            int j = (i+a.len)%7;
            ans.bestBuy[i] = min(a.bestBuy[i], b.bestBuy[j]);
            ans.bestSell[i] = max(a.bestSell[i], b.bestSell[j]);
            ans.buy[i] = a.bestBuy[i];
            ans.sell[i] = b.bestSell[j];
            if (a.len >= 2 && a.sell[i]-a.buy[i] > ans.sell[i]-ans.buy[i]) {
                ans.buy[i] = a.buy[i];
                ans.sell[i] = a.sell[i];
            }
            if (b.len >= 2 && b.sell[j]-b.buy[j] > ans.sell[i] - ans.buy[i]) {
                ans.buy[i] = b.buy[j];
                ans.sell[i] = b.sell[j];
            }
        }
        return ans;
    }
	vector<T> s; int n;
	Tree(int n = 0) : s(2*n, unit), n(n) {}
	void update(int pos, pll val) {
        T x;
        x.len = 1;
        rep(i,0,7) {
            ll c = val.F;
            if (i == 1 || i == 5) c+=val.S;
            else if (i == 2 || i == 4) c+=2*val.S;
            else if (i == 3) c+=3*val.S;
            x.buy[i] = x.sell[i] = x.bestBuy[i] = x.bestSell[i] = c;
        }
		for (s[pos += n] = x; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

vector<ll> ans;

void solve(vector<pair<pii,int>>& queries) {
    //build segment tree
    Tree tree(n);
    rep(i,0,n) {
        tree.update(i, v[i]);
    }
    for (pair<pii,int> quer : queries) {
        pii p = quer.F;
        dbg(p.F-1, p.S, quer.S);
        D res = tree.query(p.F-1, p.S);
        dbg(res.buy[0], res.sell[0], res.len);
        if (res.sell[0] > res.buy[0]) ans[quer.S] = res.sell[0] - res.buy[0];
    }
}

void run() {
    cin >> n;
    rep(i,0,n) {
        ll a,b; cin >> a >> b;
        v.pb({a,b});
    }
    int q; cin >> q;
    ans.resize(q,0);
    vector<pair<pii,int>> qLR, qRL;
    rep(i,0,q) {
        int s,t; cin >> s >> t;
        if (s < t) {
            qLR.pb({{s,t},i});
        } else {
            qRL.pb({{n+1-s,n+1-t},i});
        }
    }
    solve(qLR);
    reverse(all(v));
    solve(qRL);
    for (ll x : ans) cout << x << '\n';
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