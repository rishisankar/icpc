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

vector<int> tin, low;
int timer;
void dfs(int t, int p, VVI& adj, unordered_set<int>& ap) {
    tin[t] = low[t] = timer++;
    int ct = 0;
    for (int x : adj[t]) {
        if (x==p) continue;
        if (tin[x] == -1) {
            // dfs to children (they compute low first)
            dfs(x,t,adj,ap);
            low[t] = min(low[t], low[x]);
            // if a child depends only on t
            if (low[x] >= tin[t] && p!=-1) ap.insert(t);
            ++ct;
        } else {
            // back-edge to ancestor in DFS tree
            low[t] = min(low[t], tin[x]);
        }
    }
    if (p == -1 && ct >= 2) {
        // root node: articulation if multiple children
        ap.insert(t);
    }
}

unordered_set<int> articulationPoints(VVI& adj) {
    int n = adj.size();
    tin.resize(n,-1);
    low.resize(n);
    timer = 0;
    unordered_set<int> ap;
    rep(i,0,n) {
        if (tin[i] == -1) {
            dfs(i,-1,adj,ap);
        }
    }
    return ap;
}

void run() {
    int n,m; cin >> n >> m;
    VVI adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    unordered_set<int> ans = articulationPoints(adj);
    print(ans.size());
    for (int i : ans) {
        cout << (i+1) << ' ';
    }
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