#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)  // for compatibility with kactl
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; // for compatibility with kactl
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii; // for compatibility with kactl
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;


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

/**
 * Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/FloydWarshall.h
 * 
 * Calculates all-pairs shortest path in a directed graph that might have negative edge weights.
 * Input: adj matrix m, where m[i][j] = inf if i and j are not adjacent
 * Output: m[i][j] is set to the shortest distance between i and j; inf if no path; -inf if negative-weight cycle.
 * Time: O(N^3)
 * Example: ridehailing.cpp
 */
const ll inf = 1LL << 62;
void floydWarshall(vector<vector<ll>>& m) {
	int n = sz(m);
	FOR(i,0,n) m[i][i] = min(m[i][i], 0LL);
	FOR(k,0,n) FOR(i,0,n) FOR(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) {
			auto newDist = max(m[i][k] + m[k][j], -inf);
			m[i][j] = min(m[i][j], newDist);
		}
	FOR(k,0,n) if (m[k][k] < 0) FOR(i,0,n) FOR(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}

struct job {
    int u,v,t;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int n, m, k;
    cin >> n >> m >> k;

    VVLL matrix(n, VLL(n, inf));
    REP(i, m) {
        int u,v,w;
        cin >> u >> v >> w;
        --u; --v;
        matrix[u][v] = w;
    }
    floydWarshall(matrix);

    vector<job> jobs;
    REP(i, k) {
        int u,v,t; 
        cin >> u >> v >> t;
        job j; j.u = u-1; j.v = v-1; j.t = t;
        jobs.PB(j);
    }

    // matching using flow
    // [0,k-1]: p1, [k-(2k-1)]: p2, (2k): source, (2k+1): sink

    int K = 2*k+2;
    int s = 2*k;
    int t = 2*k+1;

    Dinic flow_graph(K);
    REP(i, k) {
        flow_graph.addEdge(s, i, 1);
        flow_graph.addEdge(k+i, t, 1);
    }
    REP(i, k) REP(j, k) {
        job j1 = jobs[i];
        job j2 = jobs[j];
        if (j1.t < j2.t) {
            if ((j1.t + matrix[j1.u][j1.v] + matrix[j1.v][j2.u]) <= j2.t) {
                flow_graph.addEdge(i, j+k, 1);
            }
        }
    }
    int f = flow_graph.calc(s, t);

    cout << (k-f) << '\n';

}