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

struct Tree {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
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

vi ind;
VVI adj;
vi stz;
VLL p;
vi dep;
int build(int t, int i) {
    if (p[t] == -1) dep[t] = 0;
    else dep[t] = dep[p[t]]+1;
    ind[t] = i;
    stz[t] = 1;
    i++;
    for (int x : adj[t]) {
        i = build(x,i);
        stz[t] += stz[x];
    }
    return i;
}

void run() {
    int n; cin >> n;
    ind.resize(n);
    dep.resize(n);
    stz.resize(n);
    p.resize(n);
    VLL cost(n);
    vector<pll> skill(n);
    adj.resize(n);
    int r;
    rep(i,0,n) {
        ll a,b,c; cin >> a >> b >> c;
        if (a!=-1){
            --a;
            adj[a].pb(i);
        }
        else r=i;
        p[i] = a;
        cost[i] = c;
        skill[i] = {b,i};
    }
    build(r,0);
    sort(all(skill),[&](pll& a1, pll& a2) {
        return a1.F < a2.F || (a1.F == a2.F && dep[a1.S] < dep[a2.S]);
    });
    dbg(ind);
    dbg(stz);
    dbg(dep);
    Tree t(n);
    VLL ans(n);
    for (auto k : skill) {
        ans[k.S] = t.query(ind[k.S], ind[k.S] + stz[k.S]);
        t.update(ind[k.S], cost[k.S]);
    }
    dbg(ans);
    for (ll l : ans) {
        print(l);
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