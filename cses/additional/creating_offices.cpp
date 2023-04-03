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
similar concept to xenia and tree
greedily pick leaf furthest away from arbitrary root (i.e. sort by depth; decreasing order)
then get rid of that leaf --> its parent could become a leaf
in this order, color node IF distance from already colored nodes >= d
return all colored nodes
*/

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
	vi depth, time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : depth(sz(C)), time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
        depth[v] = (par == -1 ? 0 : 1+depth[par]);
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
	int dist(int a, int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

/*
Build centroid tree from tree (adj). Store adjacency list in centroid_tree, parent 
pointers in par, root of tree in r (par[r] = -1).
Time: O(nlogn)

Tested on https://codeforces.com/problemset/problem/342/E
*/
void centroidDecomposition(VVI& adj, VVI& centroid_tree, VI& par, int& r) {
    int n = sz(adj);
    VB proc(n,0); // already processed (ie already found as a centroid)
    VI st_sz(n); // subtree size container
    function<void(int,int)> subtree_sz = [&](int t, int par) {
        st_sz[t] = 1;
        for (int x : adj[t]) {
            if (x != par && !proc[x]) {
                subtree_sz(x,t);
                st_sz[t] += st_sz[x];
            }
        }
    };
    function<int(int)> find_centroid = [&](int t) {
        subtree_sz(t,-1);
        int siz = st_sz[t];
        int prev = -1, cur = t;
        while (true) {
            int tv = -1;
            for (int x : adj[cur]) {
                if (x != prev && !proc[x]) {
                    if (st_sz[x] > siz/2) {
                        tv = x; break;
                    }
                }
            }
            if (tv != -1) {
                prev = cur;
                cur = tv;
            } else return cur;
        }
    };
    centroid_tree.resize(n);
    par.resize(n,-1);
    function<int(int)> build_ct = [&](int t) {
        int c = find_centroid(t);
        proc[c] = true;
        for (int x : adj[c]) {
            if (!proc[x]) {
                int cc = build_ct(x);
                centroid_tree[cc].pb(c);
                centroid_tree[c].pb(cc);
                par[cc] = c;
            }
        }
        return c;
    };
    r = build_ct(0);
}

ll inf = 1LL << 32;
void run() {
    int n,d; cin >> n >> d;
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    LCA lca(adj);
    VVI ct; VI par; int r;
    centroidDecomposition(adj, ct, par, r);
    VLL dist(n,inf); // dist[i] stores dist to colored node in subtree rooted at i
    vi order(n); iota(all(order), 0);
    sort(all(order),[&](int& u, int& v) {
        return lca.depth[u] > lca.depth[v];
    });
    int cur;
    vi ans;
    for (int x : order) {
        ll bst = inf;
        cur = x;
        while (cur != -1) {
            bst = min(bst, (ll)dist[cur]+lca.dist(x,cur));
            cur = par[cur];
        }
        if (bst >= d) {
            ans.pb(x);
            cur = x;
            while (cur != -1) {
                dist[cur] = min(dist[cur], (ll)lca.dist(x,cur));
                cur = par[cur];
            }
        }
    }
    print(sz(ans));
    for (int i : ans) cout << (i+1) << ' ';
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
