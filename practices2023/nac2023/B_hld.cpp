// tles lol
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

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, depth, rt, pos;
	Node *tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		  rt(N),pos(N),tree(new Node(0, N)){ dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		for (int& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree->add(l, r, val); });
	}
	int queryPath(int u, int v) { // Modify depending on problem
		int res = -1e9;
		process(u, v, [&](int l, int r) {
				res = max(res, tree->query(l, r));
		});
		return res;
	}
	int querySubtree(int v) { // modifySubtree is similar
        return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
	void modifySubree(int v, int val) { // modifySubtree is similar
		return tree->set(pos[v] + VALS_EDGES, pos[v] + siz[v], val);
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
    HLD<false> h(adj);
    rep(Q,0,q) {
        int u,v; cin >> u >> v; --u; --v;
        int ans = 1;
        h.modifySubree(0,0);
        h.modifyPath(u,a,1);
        h.modifyPath(b,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,b,1);
        h.modifyPath(a,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,c,1);
        h.modifyPath(d,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,d,1);
        h.modifyPath(c,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        // last case
        h.modifyPath(u,a,1);
        h.modifyPath(b,c,1);
        h.modifyPath(d,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,a,1);
        h.modifyPath(b,d,1);
        h.modifyPath(c,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,b,1);
        h.modifyPath(a,c,1);
        h.modifyPath(d,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,b,1);
        h.modifyPath(a,d,1);
        h.modifyPath(c,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,c,1);
        h.modifyPath(d,a,1);
        h.modifyPath(b,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,c,1);
        h.modifyPath(d,b,1);
        h.modifyPath(a,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,d,1);
        h.modifyPath(c,a,1);
        h.modifyPath(b,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
        h.modifyPath(u,d,1);
        h.modifyPath(c,b,1);
        h.modifyPath(a,v,1);
        if (h.querySubtree(0) == 1) ++ans;
        h.modifySubree(0,0);
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