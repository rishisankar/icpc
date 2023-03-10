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

struct Node {
    typedef ll T;
    const T unit = 0;
    const T inf = LLONG_MIN; // value that is not present in segtree
    T f(T a, T b) { return a+b; } // associative
    T rangeF(T x) {
        // represents value from setting everything on range to x
        // or value to add to segment value when adding x on range
        return x*(hi-lo); // for addition ()
        // return x; // for max/min
    }
	Node *l = 0, *r = 0;
	int lo, hi;
    T mset = inf, madd = 0, val = unit;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of unit
	Node(vector<T>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
	T query(int L, int R) {
		if (R <= lo || hi <= L) return unit;
		if (L <= lo && hi <= R) return val;
		push();
		return f(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, T x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = x, val = rangeF(x), madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = f(l->val, r->val);
		}
	}
	void add(int L, int R, T x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += rangeF(x);
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = f(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

/*
Convert tree to array with each subtree contiguous (DFS)
Return vector<pii> d(n), where d[i] = {a,b} indicates 
subtree rooted at node i is at indices [a,b) of the array.
(root of subtree always at index a)
Time: O(n)
Tested on cses/trees/subtree_queries
*/
vector<pii> subtreeArrayDecomp(VVI& adj, int root) {
    int n = adj.size();
    int ct = 0;
    vector<pii> decomp(n);
    function<void (int,int)> dfs = [&](int t, int p) {
        decomp[t].F = ct++;
        for (int x : adj[t]) {
            if (x == p) continue;
            dfs(x,t);
        }
        decomp[t].S = ct;
    };
    dfs(root,-1);
    return decomp;
}

void dfs(int t, int p, VVI& adj, VLL& path_sum, VLL& vals) {
    if (p == -1) path_sum[t]=vals[t];
    else path_sum[t] = path_sum[p] + vals[t];
    for (int x : adj[t]) if (x!=p) dfs(x,t,adj,path_sum,vals);
}

void run() {
    int n,q; cin >> n >> q;
    VVI adj(n);
    VLL vals(n); INP(vals,n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    VLL path_sum(n);
    dfs(0,-1,adj,path_sum,vals);
    dbg(path_sum);
    VLL decomp_sum(n);
    vector<pii> decomp = subtreeArrayDecomp(adj, 0);
    rep(i,0,n) decomp_sum[decomp[i].F] = path_sum[i];
    Node t(decomp_sum,0,n);
    rep(Q,0,q) {
        int T; cin >> T;
        if (T == 1) {
            int s; ll x; cin >> s >> x; --s;
            t.add(decomp[s].F,decomp[s].S,x-vals[s]);
            vals[s] = x;
        } else {
            int s; cin >> s; --s;
            print(t.query(decomp[s].F,decomp[s].F+1));
        }
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