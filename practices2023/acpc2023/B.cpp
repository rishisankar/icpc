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

void rf(pll& p) {
  if (p.F == 0) p = {0,1};
  else {
    ll g = __gcd(llabs(p.F), llabs(p.S));
    p = {p.F/g, p.S/g};
    if (p.S < 0) p = {-p.F, -p.S};
  }
}

pll af(pll p1, pll p2) {
  pll res = {p2.S*p1.F+p2.F*p1.S, p1.S*p2.S};
  rf(res);
  return res;
}

pll sf(pll p1, pll p2) {
  pll res = {p2.S*p1.F-p2.F*p1.S, p1.S*p2.S};
  rf(res);
  return res;
}

pll mf(pll p1, pll p2) {
  pll res = {p1.F*p2.F, p1.S*p2.S};
  rf(res); return res;
}

pll df(pll p1, pll p2) {
  pll swp = {p2.S,p2.F};
  return mf(p1,swp);
}

bool lt(pll p1, pll p2) {
  rf(p1); rf(p2);
  return p1.F*p2.S < p1.S*p2.F;
}

bool gt(pll p1, pll p2) {
  rf(p1); rf(p2);
  return p1.F*p2.S > p1.S*p2.F;
}


struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

typedef pair<pii, pll> T;

void run() {
    int n,m; cin >> n >> m;
    vector<pair<pii, pll>> edges;
    rep(i,0,m) {
        int a,b; ll c,d; cin >> a >> b >> c >> d;
        --a; --b;
        edges.pb({{a,b},{c,d}});
    }
    pll x = {1,1};
    while (true) {
        sort(all(edges), [&](T& a, T& b) {
            return (a.S.F * x.S - a.S.S * x.F) < (b.S.F * x.S - b.S.S * x.F);
        });
        // dbg(edges);
        ll N=0,D=0;
        UF dsu(n);
        rep(i,0,m) {
            if (dsu.join(edges[i].F.F, edges[i].F.S)) {
                N += edges[i].S.F;
                D += edges[i].S.S;
            }
        }
        pll y = {N,D};
        // dbg(x,y);
        rf(y);
        if (y == x) {
            cout << y.F << '/' << y.S << '\n';
            return;
        }
        x = y;
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