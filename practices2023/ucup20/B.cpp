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

struct Tree {
	typedef ll T;
	static constexpr T unit = LLONG_MAX;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
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

inline ll getx(ll a, ll b) {
    if(b==0) return a+1;
    ll ans = (a+b+1)/(b+1);
    // assert (a/ans <= b && a/(ans-1) > b);
    while (a/(ans+1) > b) ++ans;
    while (a/(ans-1) <= b) --ans;
    return ans;
}

void run() {
    ll n,m,k; cin >> n >> m >> k;
    VLL v(n), cost(m+1);
    INP(v,n);
    rep(i,1,m+1) cin >> cost[i];
    m++; cost.pb(2*cost.back());
    Tree opt(m+1);
    rep(i,1,m+1) opt.update(i, cost[i]);
    rep(i,2,m+1) {
        ll icst = opt.query(i, m+1);
        opt.update(i, icst);
        rep(j,2,i+1) {
            ll mtp = i*j;
            bool bval = 0;
            if (mtp > m) {
                bval = 1;
                mtp = m;
            }
            ll cmtp = opt.query(mtp, m+1);
            ll jcst = opt.query(j, m+1);
            opt.update(mtp, min(cmtp, icst + jcst));
            if (bval) break;
        }
    }
    VLL optcost(m+1);
    rep(i,2,m+1) {
        optcost[i] = opt.query(i,m+1);
    }

    sort(all(v));
    rep(i,0,n/2)v.pop_back();
    ll lo = 0, hi = v.back(), bst = v.back();
    while (lo <= hi) {
        ll mid = (lo+hi)/2;
        ll cst = 0;
        for (ll i : v) {
            if (i <= mid) continue;
            ll x = getx(i, mid);
            assert (2 <= x && x <= m);
            cst += optcost[x];
        }
        if (cst > k) lo = mid + 1;
        else {
            bst = mid;
            hi = mid-1;
        }
    }
    print(bst);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}