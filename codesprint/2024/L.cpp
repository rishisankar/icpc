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

template<typename T> inline T ceildiv(T a, T b) {return (a+b-1)/b;}

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

// O(log(min(a,b))), can use __gcd instead
ll gcd(ll a, ll b) {
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 

// note that lcm(i, j) = ij / gcd(i,j)
ll lcm(ll a, ll b) {
  return a*b/gcd(a,b);
}

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
    if((a - b) % g != 0)return -1;
    // assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}


ll n,t;
VVI adj;
VLL death; // last time that can cross edge going into each node
vector<pair<pll,ll>> state; // a mod b, max reachable time c

VLL ans;
VLL sumans;

// return number of vals x <= M s.t. x = a mod b (#s of form a+bi)
ll nvals(ll a, ll b, ll M) {
    a%=b;
    if (a > M) return 0;
    ll lb = min(M / b - 5,0LL), ub = M / b + 5;
    for (ll i = ub; i >= lb; --i) {
        if (a + b * i <= M) return i+1;
    }
    return 0;

}

void dfs(int t) {
    ll l = lcm(state[t].F.S, sz(adj[t]));

    ll kids = 0;

    rep(i,0,sz(adj[t])) {
        int x = adj[t][i];
        state[x] = {{crt(state[t].F.F, state[t].F.S, i, sz(adj[t])), l}, min(state[t].S, death[x])};
        if (state[x].F.F == -1) {
            dbg(t,x);
            state[x] = {{0,1},-1};
        }
        dfs(x);

        kids += sumans[x];
    }

    ll tot = nvals(state[t].F.F, state[t].F.S, state[t].S);

    dbg(t+1, tot, kids, tot-kids, state[t]);

    ans[t] = tot - kids;
    sumans[t] = tot;
}

void run() {
    cin >> n >> t;
    adj.resize(n);
    ans.resize(n);
    sumans.resize(n);
    set<pii> edges;
    rep(i,0,n) {
        int k; cin >> k;
        rep(j,0,k) {
            int c; cin >> c; --c;
            adj[i].pb(c);
            edges.insert({i,c});
        }
    }

    death.resize(n);
    rep(i,0,n-1) {
        int a,b,ti; cin >> a >> b >> ti; --a; --b;
        if (!edges.count({a,b}))swap(a,b);
        death[b] = ti - 2;
    }

    state.resize(n);
    state[0] = {{0,1}, t-1};
    dfs(0);
    dbg(state);
    
    for (ll x : ans) cout << x << ' ';
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