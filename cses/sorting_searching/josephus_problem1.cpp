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
    T f(T a, T b) { return a+b; }
	Node *l = 0, *r = 0;
	int lo, hi;
    T val = unit;
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
		return f(l->query(L, R), r->query(L, R));
	}
	void clr(int p) {
		if (p < lo || hi <= p) return;
        if (lo == hi-1) {
            val = 0;
            return;
        }
        l->clr(p); r->clr(p);
        val = f(l->val, r->val);
	}
    int geti(int x) {
        if (lo == hi-1) return lo;
        if (l->val > x) {
            return l->geti(x);
        } else {
            return r->geti(x-(l->val));
        }
    }
};

void run() {
    int n; cin >> n;
    int k = 1;
    VLL v(n, 1);
    Node* st = new Node(v,0,n);
    int sz = n;
    int cur = -1;
    vi ans;
    while (sz > 0) {
        cur += k+1;
        cur %= sz;
        int p = st->geti(cur);
        ans.pb(p+1);
        st->clr(p);
        --sz;
        --cur;
    }
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