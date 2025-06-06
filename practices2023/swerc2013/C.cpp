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

int TC;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

void run() {
    int n,m; cin >> n >> m;
    vector<pair<pll, int>> courses(n);
    ll sm = 0;
    rep(i,0,n) {
        cin >> courses[i].F.F >> courses[i].F.S >> courses[i].S;
        courses[i].S = (courses[i].S - 1) / m + 1;
        sm += courses[i].S;
        dbg(courses[i].S);
    }
    VVB adjm(n,VB(n));
    rep(i,0,n) {
        rep(j,0,n) {
            ll x; cin >> x;
            if (i == j) continue;
            if (courses[i].F.S + x < courses[j].F.F) adjm[i][j] = 1;
        }
    }
    dbg(adjm);
    int N = n*2 + 4;
    ll lo = 1, hi = sm;
    dbg(hi);
    ll bst = hi;
    ll inf = 10*hi;
    int S = 2*n, T = 2*n+1, Sp = 2*n+2, Tp = 2*n+3;
    // for (ll md = 1; md <= hi; ++md) {
    while (lo <= hi) {
        ll md = (lo+hi)/2;
        Dinic d(N); // course gets edges 2*i, 2*i+1. Final edges: 2*n, 2*n+1 for s,t; 2*n+2, 2*n+3 for s',t'.
        rep(i,0,n) {
            d.addEdge(2*i, 2*i+1, inf);
            d.addEdge(S, 2*i, inf);
            d.addEdge(2*i+1, T, inf);
            d.addEdge(Sp, 2*i+1, courses[i].S);
            d.addEdge(2*i, Tp, courses[i].S);
            rep(j,0,n) {
                if (i == j) continue;
                if (adjm[i][j]) {
                    d.addEdge(2*i+1, 2*j, inf);
                }
            }
        }
        d.addEdge(T, S, md);
        ll ans = d.calc(Sp, Tp);
        dbg(ans, md);
        if (ans == sm) {
            bst = md;
            hi = md-1;
        } else {
            lo = md+1;
        }
    }
    cout << "Case " << TC << ": " << bst << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    for (TC = 1; TC <= t; ++TC) run();
}