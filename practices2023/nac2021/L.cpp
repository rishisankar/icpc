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


void run() {
    int n,m,d; cin >> n >> m >> d;
    vector<vector<pair<int,ll>>> adj(n), radj(n);
    rep(i,0,m) {
        int u,v; cin >> u >> v; --u; --v;
        ll c; cin >> c;
        adj[u].pb({v,c});
        radj[v].pb({u,c});
    }
    VLL pt(d); INP(pt,d); sort(all(pt));
    vector<ll> dis; vi p;
    dijkstra(0,dis,p,adj);
    unordered_set<ll> dists;
    for (ll l : dis) dists.insert(l);
    for (ll x : pt) {
        if (!dists.count(x)) {
            print(0);
            return;
        }
    }
    vi v(n); rep(i,0,n) v[i] = i;
    sort(all(v), [&](int a, int b) {
        return dis[a] < dis[b];
    });
    vi ans(n,-1); // parent if 1 path, n for first node, -1 if no path, -2 if multiple
    ans[0] = n;
    rep(zz,1,n) {
        int i = v[zz];
        for (auto ed : radj[i]) {
            if (ed.S + dis[ed.F] != dis[i]) continue; // shortest paths only
            ll d1 = dis[ed.F];
            if (ans[ed.F] == -1) continue;
            int ind = upper_bound(all(pt), d1) - pt.begin();
            if (ind != sz(pt) && pt[ind] < dis[i]) continue;
            if (ans[ed.F] == -2 || ans[i] != -1) ans[i] = -2;
            else ans[i] = ed.F;
        }
    }
    dbg(ans);
    dbg(dis);
    if (ans[n-1] == -1) {
        print (0);
    } else if (ans[n-1] == -2) {
        print(1);
    } else {
        vi nodes;
        int cur = n-1;
        while (cur != n) {
            nodes.pb(cur);
            cur = ans[cur];
        }
        reverse(all(nodes));
        print(sz(nodes));
        for (int i : nodes) print(i+1);
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