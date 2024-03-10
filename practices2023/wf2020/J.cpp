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

vector<vector<pair<int,ll>>> chd;
vi par;
int n;

vector<VVLL> dp;

ll slv(int x, int extra_plow, int npaths);
ll slv2(int x, int extra_plow, int npaths) {
    // order by which ones are best to dedicate a inward path to
    sort(all(chd[x]), [&](pair<int,ll> c1, pair<int,ll> c2) {
        ll c1_1p = slv(c1.F, 0, 1) + c1.S;
        ll c1_2p = slv(c1.F, 0, 2) + 2 * c1.S;
        ll c2_1p = slv(c2.F, 0, 1) + c2.S;
        ll c2_2p = slv(c2.F, 0, 2) + 2 * c2.S;
        ll c1_saving = c1_1p - c1_2p;
        ll c2_saving = c2_1p - c2_2p;
        return c1_saving > c2_saving;
    });
    ll cst_base = 0;
    for (auto p : chd) cst_base += slv(p.F, 0, 2) + 2 * p.S;
    ll bst = LLONG_MAX;
    if (extra_plow && npaths <= 2) {
        // can try sending the extra plow down
        // (if npaths > 2, would need to spawn the extra plow now)
        int n_inward = 2 - npaths;
        // iterate over the places p to send the extra plow down to
        for (auto p : chd) {
            unordered_set<int> possible;
            possible
            // 
        }
    }

    return 0;
}

ll slv(int x, int extra_plow, int npaths) {
    if (dp[x][extra_plow][npaths] != -1) return dp[x][extra_plow][npaths];
    return dp[x][extra_plow][npaths] = slv2(x,extra_plow,npaths);
}

void run() {
    int n; cin >> n;
    par.resize(n);
    chd.resize(n);
    dp.resize(n, VVLL(2, VLL(5,-1)));

    vector<vector<pair<int,ll>>> adj(n);
    vi deg(n);
    rep(i,0,n-1) {
        int a,b; ll d; cin >> a >> b >> d;
        --a; --b;
        deg[a]++;
        deg[b]++;
        adj[a].pb({b,d});
        adj[b].pb({a,d});
    }
    int rt = 0;
    rep(i,0,n) {
        if (deg[i] == 1) rt = i;
    }

    vector<bool> visited(n,false);
    stack<int> stk;
    stk.push(rt);
    visited[rt] = true;
    par[rt] = -1;
    while (!stk.empty()) {
        int t = stk.top();
        stk.pop();
        for (auto x : adj[t]) {
            if (visited[x.F]) continue;
            par[x.F] = t;
            chd[t].push_back(x);
            visited[x.F] = true;
            stk.push(x.F);
        }
    }

    int rtchd = chd[rt][0].F;
    ll ans1 = slv(rtchd, 1, 1) + chd[rt][0].S;
    ll ans2 = slv(rtchd, 1, 2) + chd[rt][0].S * 2;
    print(max(ans1, ans2));
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