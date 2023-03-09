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
const ll mod2 = 998244353;

typedef pair<ll,ll> H;

const H def = {193859, 7183823};
// from https://codeforces.com/contest/1800/problem/G (symmetree problem)

// returns hash, depth
pair<H, ll> test(vector<vi>& adj, int r, int par) {
    if (adj[r].size() == 0 || (adj[r].size() == 1 && adj[r][0]==par)) return {def,1};
    vector<H> childHashes;
    ll depth = 0;
    for (int x : adj[r]) {
        if (x == par) continue;
        pair<H,ll> p = test(adj,x,r);
        childHashes.pb(p.F);
        depth = max(depth, p.S);
    }
    depth++;
    sort(all(childHashes)); // sort by hash vals

    // poly hash
    ll ans1 = 0;
    ll ans2 = 0;
    ll P = 419;
    ll P2 = 193;
    for (H h : childHashes) {
        ans1 += (h.F*P)%mod;
        ans2 += (h.S*P2)%mod2;
        P = (P*73)%mod;
        P2 = (P2*31)%mod2;
        ans1%=mod;
        ans2%=mod2;
        ans1 = (ans1 + depth) % mod;
        ans2 = (ans2 + 2*depth) % mod;
    }
    H hsh = {ans1,ans2};
    return {hsh, depth};
}

void run() {
    int n; cin >> n;
    vector<vi> adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    auto p1 = test(adj, 0, -1);
    vector<vi> adj2(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj2[a].pb(b);
        adj2[b].pb(a);
    }
    auto p2 = test(adj2,0,-1);
    print(((p1.F==p2.F) ? "YES" : "NO"));

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