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

vector<pii> eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges);
    vector<pii> ret, s = {{src,-1}};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		pii x = s.back();
        int y, e, &it = its[x.F], end = sz(gr[x.F]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x.F][it++];
		if (!eu[e]) {
			D[x.F]--, D[y]++;
			eu[e] = 1; s.push_back({y,e});
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

/*
Find all connected components in a undirected graph
(returns vector of nodes in each component)
Example: cses/graphs/building_roads
*/
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
    int n,m,k; cin >> n >> m >> k;
    VVI adj(n);
    vector<pii> origEdges;
    vi deg(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
        deg[a]++;
        deg[b]++;
        origEdges.pb({min(a,b), max(a,b)});
    }
    VVI comps = components(adj);
    vi compId(n);
    rep(i,0,sz(comps)) for (int x : comps[i]) compId[x] = i;
    vector<vector<pii>> edgesByComp(sz(comps));
    for (auto p : origEdges) {
        edgesByComp[compId[p.F]].pb(p);
    }
    dbg(comps);
    int mn = 0;
    for (auto &c : comps) {
        if (sz(c) == 1) continue;
        int od = 0;
        for (int x : c) {
            if (deg[x] & 1) ++od;
        }
        dbg(od);
        if (od == 0) mn += 1;
        else mn += od/2;
    }
    if (k < mn || k > m) {
        print("Impossible");
        return;
    }

    int excess = k - mn;

    dbg(mn,excess);
    print("Possible");
    
    rep(cid, 0, sz(comps)) {
        auto c = comps[cid];
        if (sz(c) == 1) continue;
        unordered_map<int,int> zz;
        vi zzr;
        for (int x : c) {
            zz[x] = sz(zz);
            zzr.pb(x+1);
        }
        int od = 0;
        int podd = -1;
        vector<pii> added;
        vector<pii> edg;
        for (auto p : edgesByComp[cid]) {
            edg.pb({min(zz[p.F], zz[p.S]), max(zz[p.F],zz[p.S])});
        }
        for (int x : c) {
            if (deg[x] & 1) {
                ++od;
                int xx = zz[x];
                if (podd != -1) {
                    pii nw = {min(xx, podd), max(xx,podd)};
                    podd = -1;
                    added.pb(nw);
                } else {
                    podd = xx;
                }
            }
        }

        int n_ed = 0;
        vector<vector<pii>> gr(sz(c));
        vector<pii> edges;
        for (auto p : added) {
            dbg("added",p);
            edges.pb(p);
            gr[p.F].pb({p.S,n_ed});
            gr[p.S].pb({p.F,n_ed++});
        }
        for (auto p : edg) {
            edges.pb(p);
            dbg("orig",p);
            gr[p.F].pb({p.S,n_ed});
            gr[p.S].pb({p.F,n_ed++});
        }

        dbg(gr);
        dbg(edges);

        vector<pii> ew = eulerWalk(gr, n_ed, 1);
        dbg(ew);

        vector<vi> paths;
        vi cur;
        cur.pb(ew[0].F);
        rep(i,1,sz(ew)) {
            if (ew[i].S < sz(added)) {
                // fake edge, end path
                if (sz(cur) > 1) {
                    paths.pb(cur);
                }
                cur.clear();
                cur.pb(ew[i].F);
            } else {
                cur.pb(ew[i].F);
            }
        }
        if (sz(cur) > 1) paths.pb(cur);
        dbg(paths);
        if (sz(paths) > 1 && paths[0][0] == paths.back().back()) {
            rep(i,1,sz(paths[0])) {
                paths.back().pb(paths[0][i]);
            }
            paths.erase(paths.begin());
        }
        dbg(paths);

        for (vi &path : paths) {
            int poss = sz(path) - 2;
            int amt = min(excess, poss);
            excess -= amt;
            int j = 0;
            rep(i,0,amt) {
                print(zzr[path[j]], zzr[path[j+1]]);
                j++;
            }
            cout << zzr[path[j]];
            for (j++; j < sz(path); ++j) {
                cout << ' ' << zzr[path[j]];
            }
            cout << '\n';
        }
        
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