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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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
    const T inf = LLONG_MAX; // value that is not present in segtree
    T f(T a, T b) { return a|b; } // associative
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
};

void run() {
    int p,n; cin >> p >> n;
    unordered_map<string, int> ids;
    vector<pll> times(p-1);
    VVLL locs(p);
    rep(i,0,p) {
        string s; cin >> s;
        ids[s] = i;
        if (i != p-1) {
            cin >> times[i].F >> times[i].S;
        }
    }
    ll maxTime = 0;
    rep(i,0,n) {
        string s; cin >> s;
        ll t; cin >> t;
        auto it = ids.find(s);
        if (it == ids.end()) continue;
        locs[it->second].pb(t);
        maxTime = max(maxTime, t);
    }
    Node *tr = new Node(0, maxTime + 5);
    for (ll t : locs[p-1]) {
        tr->set(t, t+1, 1 << (p-1));
    }
    for (int i = p-2; i >= 0; --i) {
        for (ll t : locs[i]) {
            ll res = tr->query(t + times[i].F, t + times[i].S + 1);
            if ((res >> (i+1)) & 1) {
                if (i == 0) {
                    print("Yes");
                    return;
                }
                tr->set(t, t+1, 1 << i);
            }
        }
    }
    print("No");
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