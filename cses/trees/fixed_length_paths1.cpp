// too slow :(

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
Centroid decomposition on a tree (can find 1-2 centroids; if 2 the centroids are connected)
1 vs 2 centroids depends on parity o fthe 
Centroid means all subtrees have at most floor(n/2) nodes.
Returns 1-2 nodes [0-n) representing the centroids
https://codeforces.com/blog/entry/57593
tested on cses/trees/finding_a_centroid, cses/additional/tree_isomorphism2
*/
vector<int> findCentroids(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> centroid;
    vector<int> siz(n); // stores size of each subtree
    function<void (int,int)> dfs = [&](int u, int prev) {
        if (centroid.size()>0) return;
        siz[u] = 1;
        bool is_centroid = true;
        for (auto v : g[u]) if (v!=prev) {
            dfs(v,u);
            siz[u] += siz[v]; // update siz from children subtrees
            if (siz[v] > n/2) is_centroid = false; // subtree too big
        }
        if (n-siz[u] > n/2) is_centroid = false; // consider subtree going through parent
        if (is_centroid) centroid.push_back(u);
    };
    dfs(0,-1);
    return centroid;
}
/*
Root a tree at node r. Returns {childs, parent}. O(n)
*/
pair<vector<vi>,vi> rootTree(vector<vi>& adj, int r) {
    int n = adj.size();
    vector<vi> childs(n);
    vi parent(n);
    vector<bool> visited(n,false);
    stack<int> s;
    s.push(r);
    visited[r] = true;
    parent[r] = -1;
    while (!s.empty()) {
        int t = s.top();
        s.pop();
        for (int x : adj[t]) {
            if (visited[x]) continue;
            parent[x] = t;
            childs[t].push_back(x);
            visited[x] = true;
            s.push(x);
        }
    }
    return {childs,parent};
}

ll ans = 0;
int k;

void dfs(int x, vi& nmap, int& n_st, vi& d, VVI& chd, unordered_map<ll,ll>& cts, VI& par) {
    nmap[x] = n_st++;
    d[x] = 1+d[par[x]];
    if (d[x] <= k) {
        ans += cts[k-d[x]];
    }
    for (int cd : chd[x]) dfs(cd,nmap,n_st,d,chd,cts,par);
}

void dfs2(int x, unordered_map<ll,ll>& cts, VI& par, int c, VVI& nadj, vi& d, vi& nmap, VVI& chd) {
    if (d[x] <= k) cts[d[x]]++;
    if (par[x] != c) {
        int a = nmap[x], b = nmap[par[x]];
        nadj[a].pb(b); nadj[b].pb(a);
    }
    for (int cd : chd[x]) dfs2(cd,cts,par,c,nadj,d,nmap,chd);
}

void solve(VVI& adj) {
    int n = adj.size();
    if (n <= 1) return;
    if (n == 2) { if (k==1)++ans; return; }
    int c = findCentroids(adj)[0];
    VVI chd; VI par; tie(chd,par) = rootTree(adj,c);
    unordered_map<ll,ll> cts;
    cts[0] = 1;
    vi d(n); d[c] = 0;
    vector<int> nmap(n);
    rep(i,0,chd[c].size()) {
        int n_st = 0;
        dfs(chd[c][i],nmap,n_st,d,chd,cts,par);
        VVI nadj(n_st);
        dfs2(chd[c][i],cts,par,c,nadj,d,nmap,chd);
        solve(nadj);
    }
}

void run() {
    int n; cin >> n >> k;
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    solve(adj);
    print(ans);
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