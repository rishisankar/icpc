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
        return x*(hi-lo);
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

inline ll gxi(ll ti, ll pi) { return pi-ti; }
typedef pair<pll,pll> T; // ai, pi, ti, bi

void run() {
    ll t,n,a;
    cin >> t >> n >> a;
    unordered_map<ll, vector<T>> segs;
    rep(i,0,t) {
        ll ti, pi, bi, ai;
        cin >> ti >> pi >> bi >> ai;
        if (bi > n) {
            ti = ti+bi-n;
            pi = (pi + bi) % n;
            bi = n;
        }
        if (pi + bi > n) {
            segs[gxi(ti, pi)].pb({{ai,pi},{ti,n-pi}});
            segs[gxi(ti+n-pi,0)].pb({{ai,0},{ti+n-pi,bi-n+pi}});
        } else segs[gxi(ti,pi)].pb({{ai,pi},{ti,bi}});
    }
    vector<T> fs;
    for (auto& xv : segs) {
        vector<pair<ll,pair<bool,ll>>> pts;  // pos, S/F, ai
        for (T& seg : xv.S) {
            pts.pb({seg.F.S, {0, seg.F.F}});
            pts.pb({seg.F.S+seg.S.S-1, {1, seg.F.F}});
        }
        sort(all(pts));
        ll prev = pts[0].F;
        unordered_map<ll, int> counts;
        for (auto& p : pts) {
            if (sz(counts)) {
                ll val = (sz(counts)==1 ? counts.begin()->F : a);
                fs.pb({{val, prev}, {prev-xv.F, p.F-prev+1}});
            }
            prev = p.F;
            if (!p.S.F) counts[p.S.S]++;
            else if (--counts[p.S.S] == 0) counts.erase(counts.find(p.S.S));
        }
    }
    sort(all(fs), [&](T& t1, T& t2) {
        int x1 = gxi(t1.S.F,t1.F.S), x2 = gxi(t2.S.F,t2.F.S);
        return (x1 < x2) || (x1 == x2 && t1.F.F > t2.F.F);
    });
    vi ans(a+1);
    Node* tr = new Node(0, n);
    tr->set(0,n,1);
    for (auto& seg : fs) {
        ans[seg.F.F] += tr->query(seg.F.S, seg.F.S + seg.S.S);
        tr->set(seg.F.S, seg.F.S + seg.S.S, 0);
    }
    ans[0] += tr->query(0,n);
    for (int i : ans) cout << i << ' ';
    cout << '\n';
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