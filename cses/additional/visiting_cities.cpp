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
Find # of shortest paths to each node (dijkstra + backtrack step) from 1. --> sp1()
Find # of shortest paths to each node from n also. spn() on reverse graph

Consider a shortest path from source 1 to end n. Any necessary city x is part of this path.
For a node x on this path:
  sp1(x) * spn(x) == sp1(n) <==> x necessary

Proof: necessary --> all paths go through x --> paths to n given by paths to x * paths from x to n
converse: if not necessary, there exists path not crossing x ==> at least 1 + sp1(x) * spn(x) sp
*/

/*
Compute number of shortest paths to each node (tested on directed graph)
Edge weights must be > 0 (if 0, could be infinite ways...)
Need both adj and reverse adj list
(in undirected graph, these are the same i think? haven't tested on undirected)
Time complexity same as dijsktra O(E log V)?

Tested on cses/additional/visiting_cities
*/
const long long INF = 10000000000000000LL;
void dijkstra(int s, vector<long long> & d, vector<int> & p, vector<vector<pair<int,long long>>> &adj) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    using pii = pair<long long, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        long long d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            long long len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}
void numShortestPaths(int s, VLL& paths, vector<vector<pair<int,ll>>>& adj, vector<vector<pair<int,ll>>>& radj, ll mod) {
    int n = adj.size();
    VLL d; VI p; dijkstra(s,d,p,adj);
    paths.assign(n,0);
    paths[s] = 1;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    rep(i,0,n) {
        if (i != s) pq.push({d[i],i});
    }
    while (!pq.empty()) {
        pair<ll,int> p = pq.top(); pq.pop();
        for (auto ed : radj[p.S]) {
            if (d[ed.F] + ed.S == p.F) {
                paths[p.S] += paths[ed.F];
                paths[p.S] %= mod;
            }
        }
    }
}

void run() {
    int n,m; cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n), radj(n);
    rep(i,0,m) {
        int a,b,c; cin >> a >> b >> c; --a; --b;
        adj[a].pb({b,c});
        radj[b].pb({a,c});
    }
    VLL sp1, spn;
    VLL sp12, spn2; // use diff mod just in case
    numShortestPaths(0,sp1, adj, radj, mod);
    numShortestPaths(n-1,spn, radj, adj, mod);
    numShortestPaths(0,sp12, adj, radj, mod+2);
    numShortestPaths(n-1,spn2, radj, adj, mod+2);
    vi nec; // necessary cities to visit
    VLL d; VI p; dijkstra(0,d,p,adj);
    vi pth = restore_path(0,n-1,p);
    for (int i : pth) {
        if ((sp1[i] * spn[i]) % mod == sp1[n-1]) {
            if ((sp12[i] * spn2[i]) % (mod+2) == sp12[n-1]) {
                nec.pb(i);
            }
        }
    }   
    sort(all(nec));
    print(sz(nec));
    for (int i : nec) cout << (i+1) << ' ';
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