#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair

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
    
	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C), ret)) {}
	void dfs(vector<vi>& C) {
        stack<pii> st;
        st.push({0,-1});
        while (!st.empty()) {
            int v = st.top().F; int par = st.top().S;
            st.pop();
            if (par != -1) {
                path.push_back(par), ret.push_back(time[par]);
            }
            time[v] = T++;
            for (int i = C[v].size()-1; i >= 0; --i) {
                int y = C[v][i];
                if (y != par) {    
                    st.push({y,v});
                }
            }
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
};

void run() {
    int n; cin >> n;
    vector<map<int,ll>> adj(n);
    rep(i,0,n) {
        int j; ll t;
        cin >> j >> t; --j;
        if (!adj[i].count(j)) {
            adj[i][j] = adj[j][i] = t;
        } else {
            adj[i][j] = adj[j][i] = min(t, adj[i][j]);
        }
    }
    int q; cin >> q;
    vector<ll> answers(q, LLONG_MAX);
    vector<pii> queries;
    rep(i,0,q) {
        int a,b; cin >> a >> b; --a; --b;
        queries.pb({a,b});
    }
    vector<int> comp(n, -1);
    int ncomps = 0;
    rep(i,0,n) {
        if (comp[i] != -1) continue;
        comp[i] = ncomps;
        stack<int> stk;
        stk.push(i);
        while (!stk.empty()) {
            int t = stk.top(); stk.pop();
            for (pair<int,ll> p : adj[t]) {
                if (comp[p.F] == -1) {
                    comp[p.F] = ncomps;
                    stk.push(p.F);
                }
            }
        }
        ncomps++;
    }
    vector<vector<int>> compNodes(ncomps);
    rep(i,0,n) {
        compNodes[comp[i]].pb(i);
    }
    vector<vector<pair<pii,int>>> compQueries(ncomps);
    rep(i,0,q) {
        int c1 = comp[queries[i].F];
        int c2 = comp[queries[i].S];
        if (c1 != c2) answers[i] = -1;
        else compQueries[c1].pb({queries[i],i});
    }
    vector<int> nodeMapping(n);
    rep(c,0,ncomps) {
        int root = compNodes[c][0];
        int ct = 0;
        for (int x : compNodes[c]) {
            nodeMapping[x] = ct++;
        }
        pii cycEdge = {-1,-1};
        // run dfs from root to find all other nodes
        vector<vector<int>> tree_adj(ct); // for lca
        vector<vector<pair<int, ll>>> dijkstra_adj(ct); // for dijkstra
        vector<ll> root_dist(ct); // dist from root
        vector<int> parent(ct,-2);
        stack<int> s;
        s.push(root);
        root_dist[0] = 0;
        parent[0] = -1;
        while (!s.empty()) {
            int t = s.top(); s.pop();
            int tnew = nodeMapping[t];
            for (pair<int,ll> p : adj[t]) {
                int pnew = nodeMapping[p.F];
                if (pnew == parent[tnew]) continue; // ignore parent, alr processed this edge
                if (parent[pnew] != -2) {
                    // found cycle edge
                    assert(cycEdge == mp(-1,-1) || cycEdge == mp(pnew, tnew)); // should only be one cycle edge...
                    cycEdge = {tnew, pnew};
                } else {
                    parent[pnew] = tnew;
                    root_dist[pnew] = root_dist[tnew] + p.S;
                    tree_adj[tnew].pb(pnew);
                    s.push(p.F);
                }
                dijkstra_adj[pnew].pb({tnew,p.S});
                dijkstra_adj[tnew].pb({pnew,p.S});
            }
        }
        bool hasCycle = (cycEdge != mp(-1,-1));
        if (hasCycle) {
            // run dijkstra to solve each query
            vector<ll> dijkstra_dists; vector<int> dijkstra_par;
            dijkstra(cycEdge.F, dijkstra_dists, dijkstra_par, dijkstra_adj);
            for (pair<pii,int> quer : compQueries[c]) {
                answers[quer.S] = dijkstra_dists[nodeMapping[quer.F.F]] + dijkstra_dists[nodeMapping[quer.F.S]];
            }
        }
        // run lca to solve each query
        LCA lca(tree_adj);
        for (pair<pii,int> quer : compQueries[c]) {
            int node1 = nodeMapping[quer.F.F];
            int node2 = nodeMapping[quer.F.S];
            int l = lca.lca(node1, node2);
            ll ans = root_dist[node1] - 2*root_dist[l] + root_dist[node2];
            answers[quer.S] = min(answers[quer.S], ans);
        }
    }
    for (ll i : answers) {
        cout << i << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    run();
}
