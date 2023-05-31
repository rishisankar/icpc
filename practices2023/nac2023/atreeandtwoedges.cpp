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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}

    bool on_path(int u, int v, int x) {
        return (lca(x,u) == lca(u,v) && lca(x,v) == x) || (lca(x,v) == lca(u,v) && lca(x,u) == x);
    }

    /*
    check if paths from u->v and a->b on tree are disjoint
    */
    bool paths_disjoint(int u, int v, int a, int b) {
        return !(on_path(a,b,lca(u,v)) || on_path(u,v,lca(a,b)));
    }

    /*
    check if paths a->b, c->d, e->f are all pairwise disjoint
    */
    bool pd3(int a, int b, int c, int d, int e, int f) {
        return paths_disjoint(a,b,c,d) && paths_disjoint(a,b,e,f) && paths_disjoint(c,d,e,f);
    }
};

void run() {
    int n, q; cin >> n >> q;
    VPII edges;
    rep(i,0,n+1) {
        int a,b; cin >> a >> b; --a; --b;
        edges.pb({a,b});
    }
    UF dsu(n);
    VPII extra;
    VVI adj(n);
    for (auto& [a,b] : edges) {
        if (!dsu.sameSet(a,b)) {
            adj[a].pb(b); adj[b].pb(a);
            dsu.join(a,b);
        } else {
            extra.pb({a,b});
        }
    }
    auto [a,b] = extra[0];
    auto [c,d] = extra[1];
    LCA l(adj);
    rep(Q,0,q) {
        int u,v; cin >> u >> v; --u; --v;
        int ans = 1;
        ans += l.paths_disjoint(u,b,a,v);
        ans += l.paths_disjoint(u,a,b,v);
        ans += l.paths_disjoint(u,d,c,v);
        ans += l.paths_disjoint(u,c,d,v);
        ans += l.pd3(u,a,b,c,d,v);
        ans += l.pd3(u,b,a,c,d,v);
        ans += l.pd3(u,a,b,d,c,v);
        ans += l.pd3(u,b,a,d,c,v);
        ans += l.pd3(u,c,d,a,b,v);
        ans += l.pd3(u,d,c,a,b,v);
        ans += l.pd3(u,c,d,b,a,v);
        ans += l.pd3(u,d,c,b,a,v);
        print(ans);
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