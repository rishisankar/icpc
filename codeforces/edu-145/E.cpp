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
 
/*
Lazy segtree (can work implicitly? not tested) ; based on kactl
Example: cses/range_queries/range_updates_and_sums
Initialization: Node tree(v, 0, n);
O(nlogn) build, O(logn) set/add/query
*/
 
struct Node {
    typedef ll T;
    const T unit = LLONG_MAX;
    const T inf = LLONG_MIN; // value that is not present in segtree
    T f(T a, T b) { return min(a,b); }
    T rangeF(T x) {
        // represents value from setting everything on range to x
        // or value to add to segment value when adding x on range
        // return x*(hi-lo); // for addition ()
        return x; // for max/min
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
  /* query on range [L,R) */
	T query(int L, int R) {
		if (R <= lo || hi <= L) return unit;
		if (L <= lo && hi <= R) return val;
		push();
		return f(l->query(L, R), r->query(L, R));
	}
  /* set on range [L,R) */
	void set(int L, int R, T x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = x, val = rangeF(x), madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = f(l->val, r->val);
		}
	}
  /* add on range [L,R) */
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
 
    /*
    return smallest index st val[i]<=v
    */
    int get_first(ll v) {
        if (v < val) return hi;
        if (lo + 1 == hi) return lo;
        push();
        int i1 = l->get_first(v);
        if (i1 == l->hi) return r->get_first(v); else return i1;
    }
 
};
 
void run() {
    ll n,a,b; cin >> n >> a >> b;
    VLL ops(n); INP(ops,n);
    VVLL ans(a+1,VLL(b+1));
    for (ll tot = 0; tot <= a+b; ++tot) {
        VLL mapping(a+1,-1);
        VLL vals;
        for (ll av = min(a,tot); av>=0; --av) {
            ll bv = tot-av;
            if (bv<=b) {
                mapping[av] = sz(vals);
                vals.pb(av);
            }
        }
        int cc = sz(vals);
        Node* st = new Node(vals,0,cc+1);
        for (ll op : ops) {
            if (op < 0) {
                ll amt = -op;
                // moving amt from second --> first (things on left are set)
                ll fa1 = a-amt; // need a-v>=amt to add
                ll fa2 = tot-amt; // need tot-v>=amt to add
                ll fa = min(fa1,fa2);
                int fi = st->get_first(fa);
                st->set(0,fi,min(a,tot));
                st->add(fi,cc+1,amt);
            } else {
                ll amt = op;
                // moving amt from first --> second (things on right are set)
                ll fs1 = tot+amt-b; // need b>=tot-v+amt to add
                ll fs2 = amt; // need tot-v>=amt to add
                ll fs = max(fs1,fs2);
                int fi = st->get_first(fs);
                st->add(0,fi,-amt);
                st->set(fi,cc+1,max(0LL, tot-b));
            }
        }
        rep(av,0,tot+1) {
            int bv = tot - av;
            if (av > a || bv > b) continue;
            ans[av][bv] = st->query(mapping[av],mapping[av]+1);
        }
    }
    rep(av,0,a+1) {
        rep(bv,0,b+1) {
            cout << ans[av][bv] << ' ';
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