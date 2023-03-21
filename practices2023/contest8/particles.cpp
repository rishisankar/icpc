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

/*
Nodes: 0-{n-1} ==> {a,b} = node a*n+b
Edges: {a',b',ld}
*/

struct Edge {
    int a,b;
    ld wgt;
};

ld eucdist(vector<pll>& orig, int i, int j) {
    if (i==j) return 0;
    ld dx = orig[i].F - orig[j].F;
    ld dy = orig[i].S - orig[j].S;
    return sqrt(dx*dx+dy*dy);
}

void run() {
    int n; cin >> n;
    vector<pll> origNodes;
    rep(i,0,n) {
        ll a, b; cin >> a >> b; origNodes.pb({a,b});
    }
    int m; cin >> m;
    VVI adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<Edge> edges;
    rep(i,0,n) {
        rep(j,0,n) {
            ld d_s = eucdist(origNodes,i,j);
            int N = i*n+j;
            for (int x : adj[i]) {
                // corresponds to an edge
                int Np = x*n+j;
                ld d_n = eucdist(origNodes,x,j);
                Edge e; e.a = N; e.b = Np; e.wgt=min(d_s,d_n);
                edges.pb(e);
            }
            for (int x : adj[j]) {
                int Np = i*n+x;
                ld d_n = eucdist(origNodes,i,x);
                Edge e; e.a = N; e.b = Np; e.wgt=min(d_s,d_n);
                edges.pb(e);
            }
        }
    }
    sort(all(edges), [&](Edge& e1, Edge& e2) {
        return e1.wgt >  e2.wgt;
    });
    // for (Edge e : edges) {
    //     dbg(e.a,e.b,e.wgt);
    // }
    // dbg(edges.size());
    vector<unordered_set<int>> querMap(n*n);
    int l; cin >> l;
    rep(i,0,l) {
        int a,b; cin >> a >> b; --a; --b;
        int N = a*n+b;
        int N2 = b*n+a;
        querMap[N].insert(i);
        querMap[N2].insert(i);
    }

    UF dsu(n*n);
    vector<ld> answers(l,-1);
    for (Edge e : edges) {
        int s1 = dsu.find(e.a);
        int s2 = dsu.find(e.b);
        if (s1==s2) continue; // already connected
        dsu.join(e.a, e.b);
        int sf = dsu.find(e.a);
        int so = (s1 == sf) ? s2 : s1;
        // larger set should go in sf
        if (querMap[so].size() > querMap[sf].size()) swap(querMap[so],querMap[sf]);
        for (int z : querMap[so]) {
            if (querMap[sf].count(z)) {
                answers[z] = e.wgt;
                querMap[sf].erase(querMap[sf].find(z));
            } else {
                querMap[sf].insert(z);
            }
        }
    }
    for (ld ans : answers) {
        cout << setprecision(20) << ans << '\n';
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