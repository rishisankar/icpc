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

VVI components(VVI adj) {
    int n = adj.size();
    vector<bool> vis(n,false);
    VVI comps;
    rep(i,0,n) {
        if (!vis[i]) {
            vis[i] = true;
            comps.resize(comps.size()+1);
            comps.back().pb(i);
            stack<int> s;
            s.push(i);
            while (!s.empty()) {
                int t = s.top(); s.pop();
                for (int x : adj[t]) {
                    if (vis[x]) continue;
                    vis[x] = true;
                    comps.back().pb(x);
                    s.push(x);
                }
            }
        }
    }
    return comps;
}

void run() {
    int n; cin >> n;
    map<ll,int> nm;
    VPII edges;
    rep(i,0,n) {
        ll a,b; cin >> a >> b;
        if (!nm.count(a)) nm[a] = sz(nm);
        if (!nm.count(b)) nm[b] = sz(nm);
        a = nm[a];
        b = nm[b];
        edges.pb({(int)a,(int)b});
    }
    int ndz = sz(nm);
    VLL val(ndz);
    for (auto p : nm) val[p.S] = p.F;
    VVI adj(ndz);
    for (auto p : edges) {
        int a = p.F, b = p.S;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dbg(adj);
    VVI comps = components(adj);
    dbg(comps);
    vector<int> ec(sz(comps));
    VI cid(ndz);
    VI deg(ndz);
    rep(i,0,sz(comps)) for (int x : comps[i]) cid[x] = i;
    for (auto p : edges) {
        ec[cid[p.F]]++;
        deg[p.F]++; deg[p.S]++;
    }
    dbg(cid);
    dbg(deg);
    ll ans = 0;
    rep(c,0,sz(comps)) {
        if (ec[c] == sz(comps[c])) {
            for (int x : comps[c]) {
                ans += (deg[x]-1) * val[x];
            }
        } else {
            function<void(int,int)> dfs = [&](int t, int p) {
                for (int x : adj[t]) {
                    if (x != p) {
                        ans += val[t];
                        dfs(x,t);
                    }
                }
            };
            int mxx = comps[c][0];
            for (int x : comps[c]) {
                if (val[x] > val[mxx]) mxx = x;
            } 
            dfs(mxx,-1);
        }
    }
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