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

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

/*
Root a tree at node r. Returns {childs, parent}. O(n)
*/
pair<vector<vi>,vi> rootTree(vector<vi>& adj, int r) {
    int n = adj.size();
    vector<vi> childs(n);
    vi parent(n);
    vector<bool> visited(n,false);
    stack<int> s;
    s.push(r);
    visited[r] = true;
    parent[r] = -1;
    while (!s.empty()) {
        int t = s.top();
        s.pop();
        for (int x : adj[t]) {
            if (visited[x]) continue;
            parent[x] = t;
            childs[t].push_back(x);
            visited[x] = true;
            s.push(x);
        }
    }
    return {childs,parent};
}

vector<vi> nodesPerDepth(int r, VVI& chd) {
    int n = sz(chd);
    vector<vi> ans(n);
    stack<pii> s;
    s.push({r,0});
    while (!s.empty()) {
        pii t = s.top();
        s.pop();
        ans[t.S].pb(t.F);
        for (int x : chd[t.F]) s.push({x, t.S+1});
    }
    return ans;
}

void fail() {
    print("N");
    exit(0);
}

void run() {
    int n; cin >> n;
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int m; cin >> m;
    VVI adj2(m);
    rep(i,0,m-1) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj2[a].pb(b);
        adj2[b].pb(a);
    }
    if (m > n) fail();

    // pick root of t2 to be the node that gives fewest options for root of t1
    // vector<int> deg_counts(n);
    // rep(i,0,n) deg_counts[sz(adj[i])]++;
    // int bestDeg = -1, numChoices = 1000, t2root = -1;
    // rep(i,0,m) {
    //     int di = sz(adj2[i]);
    //     if (deg_counts[di] > 0 && deg_counts[di] < numChoices) {
    //         numChoices = deg_counts[di];
    //         bestDeg = di;
    //         t2root = i;
    //     }
    // }
    // if (bestDeg == -1) fail();
    // vector<int> rootChoices;
    // rep(i,0,n) {
    //     if (sz(adj[i]) == bestDeg) {
    //         rootChoices.pb(i);
    //     }
    // }
    // dbg(rootChoices);
    // dbg(bestDeg);

    int maxDeg = -1, t2root = -1;
    rep(i,0,m) {
        if (sz(adj2[i]) > maxDeg) {
            maxDeg = sz(adj2[i]);
            t2root = i;
        }
    }
    vector<int> rootChoices;
    rep(i,0,n) {
        if (sz(adj[i]) >= sz(adj2[t2root])) {
            rootChoices.pb(i);
        }
    }
    if (sz(rootChoices) == 0) fail();

    dbg(maxDeg);
    dbg(t2root);

    // iso table (0 = unknown, 1 = not iso, 2 = iso) [t1 root][t1 parent or n for none][t2 root]
    vector<vector<vector<uint8_t>>> iso(n, vector<vector<uint8_t>>(n+1, vector<uint8_t>(n)));

    auto [ch2, par2] = rootTree(adj2, t2root);
    VVI npd2 = nodesPerDepth(t2root, ch2);


    for (int root : rootChoices) {
        auto [ch1, par1] = rootTree(adj, root);
        VVI npd1 = nodesPerDepth(root, ch1);
        bool invalid = false;
        rep(i,0,m) {
            if (sz(npd1[i]) < sz(npd2[i])) {
                invalid = true; break;
            }
        }
        if (invalid) continue;
        for (int depth = m-1; depth >= 0; --depth) {
            for (int t1n : npd1[depth]) {
                int t1p = (depth == 0 ? n : par1[t1n]);
                for (int t2n : npd2[depth]) {
                    // dbg(t1n,t1p,t2n);
                    if (iso[t1n][t1p][t2n] != 0) continue; // computed before
                    if (sz(ch2[t2n]) == 0) {
                        // t2n is a leaf, t1n is def iso
                        iso[t1n][t1p][t2n] = 2;
                        continue;
                    }
                    // bipartite matching on iso subtrees
                    int nST2 = sz(ch2[t2n]);
                    int nST1 = sz(ch1[t1n]);
                    vector<vi> gr(nST2);
                    vi btoa(nST1,-1);
                    rep(i,0,nST1) {
                        int chT1 = ch1[t1n][i];
                        rep(j,0,nST2) {
                            int chT2 = ch2[t2n][j];
                            if (iso[chT1][t1n][chT2] == 2) {
                                gr[j].pb(i);
                            }
                        }
                    }
                    if (hopcroftKarp(gr,btoa) == nST2) {
                        // match successful --> ios
                        iso[t1n][t1p][t2n] = 2;
                    } else {
                        iso[t1n][t1p][t2n] = 1;
                    }
                }
            }
        }
    }

    // dbg("end");

    rep(i,0,n) {
        if (iso[i][n][t2root] == 2) {
            dbg(i,t2root);
            print("Y");
            return;
        }
    }
    fail();

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