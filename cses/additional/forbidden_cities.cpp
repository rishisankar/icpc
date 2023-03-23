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

vi num, st;
vector<vector<pii>> ed;
int Time;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, e, y, top = me;
	for (auto pa : ed[at]) if (pa.second != par) {
		tie(y, e) = pa;
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { f(vi{e}); }
		}
	}
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}

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
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

/*
approach:

construct block cut tree
- if c is not an articulation point, route exists
- a=b,b=c,c=a edge cases
- if a,b are in same component (vertex check), route exists
- check if path from BCC for a,b crosses node for articulation point c
*/
void run() {
    int n,m,q; cin >> n >> m >> q;
    int eid = 0; ed.resize(n);
    VPII edges;
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        ed[a].emplace_back(b, eid);
        ed[b].emplace_back(a, eid++);
        edges.pb({a,b});
    }
    int n_bcc = 0;
    vi ap;
    vector<unordered_set<int>> node_bcc(n);
    bicomps([&](const vi& edgelist) {
        for (int id : edgelist) {
            node_bcc[edges[id].F].insert(n_bcc);
            node_bcc[edges[id].S].insert(n_bcc);
        }
        ++n_bcc;
    });
    vector<int> comp_id(n);
    rep(i,0,n) {
        if (node_bcc[i].size() > 1) {
            ap.pb(i);
        }
        comp_id[i] = *(node_bcc[i].begin());
    }
    dbg(comp_id);
    dbg(ap);
    int n_ap = sz(ap);
    // construct block-cut tree. nodes [0,n_bcc) correspond to bcc nodes, nodes [n_bcc,n_bcc+n_ap) for artic pts
    unordered_map<int,int> apnm;
    rep(i,0,n_ap) {
        apnm[ap[i]] = n_bcc+i;
    }
    VVI bct(n_bcc+n_ap);
    for (int a : ap) {
        int nd = apnm[a];
        for (int bc : node_bcc[a]) {
            bct[nd].pb(bc);
            bct[bc].pb(nd);
        }
    }
    LCA lca(bct);
    // answer queries
    VB ansv(q);
    rep(i,0,q) {
        int a,b,c; cin >> a >> b >> c; --a; --b; --c;
        if (a==b) ansv[i] = (a!=c);
        else if (a==c || b == c) ansv[i] = 0;
        else if (!apnm.count(c)) ansv[i] = 1;
        else {
            c = apnm[c];
            a = comp_id[a];
            b = comp_id[b];
            /*
            goal: check if c is btwn a,b in tree
            do this with lca:
            - if lca(a,b) = a (WLOG): c is btwn if lca(b,c) = c, lca(a,c) = a
            - if lca(a,b) = x: c is btwn if (lca(a,c)==c && lca(b,c) == x) or vice versa
            */
            int L = lca.lca(a,b);
            if (L == a) {
                ansv[i] = !(lca.lca(b,c) == c && lca.lca(a,c) == a);
            } else if (L == b) {
                ansv[i] = !(lca.lca(a,c) == c && lca.lca(b,c) == b);
            } else {
                ansv[i] = !((lca.lca(a,c) == c && lca.lca(b,c) == L) || (lca.lca(b,c) == c && lca.lca(a,c) == L));
            }
        }
    }

    dbg(ansv);
    for (bool b : ansv) {
        print(b ? "YES" : "NO");
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