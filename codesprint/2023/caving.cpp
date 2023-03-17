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

struct D {
    D() : sum(0), pref(0), suff(0), mx(0) {}
    ll sum;
    ll pref;
    ll suff;
    ll mx;  
};

struct Tree {
	typedef D T;
	const T unit;
	T f(T a, T b) { 
        T ans;
        ans.sum = a.sum+b.sum;
        ans.pref = max(a.pref, a.sum+b.pref);
        ans.suff = max(a.suff+b.sum, b.suff);
        ans.mx = max(max(a.mx, b.mx), a.suff + b.pref);
        return ans;
    }
	vector<T> s; int n;
	Tree(int n = 0) : s(2*n, unit), n(n) {}
	void update(int pos, ll val) {
        T x; x.sum = val; x.pref = x.suff = x.mx = max(0LL,val);
		for (s[pos += n] = x; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
    T queryAll() { return query(0, n); }
};

struct T2 {
	typedef ll T;
	static constexpr T unit = LLONG_MIN;
	T f(T a, T b) { return max(a,b); } // (any associative fn)
	vector<T> s; int n;
	T2(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
    T queryAll() { return query(0, n); }
};

vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	queue<int> q; // use priority_queue for lexic. largest ans.
	rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (int x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}

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

struct HeavyPath {
    int id;
    Tree st; // subarray across all nodes in path
    map<int,int> nodeMap;
    vector<ll> S; // sum across children paths for each node
    HeavyPath* par;
    T2 bt; // max segtree across children
    map<int,int> subtreeMap;

    HeavyPath(int id, int n, VI& nodes, int nc, VI& subtrees) : id(id), st(n), S(n,0), par(0), bt(nc) {
        int c = 0;
        for (int x : nodes) nodeMap[x] = c++;
        c = 0;
        for (int x : subtrees) subtreeMap[x] = c++;
    }
};

pair<VI,int> hld(VVI chd) {
    int n = chd.size();
    VI st_sz(n,1);
    function<void (int)> dfs1 = [&](int u) {
        for (int v : chd[u]) {
            dfs1(v);
            st_sz[u] += st_sz[v];
        }
    };
    dfs1(0);
    dbg(st_sz);
    int pc = 0;
    VI ans(n); ans[0] = pc++;
    function<void (int)> dfs2 = [&](int u) {
        for (int v : chd[u]) {
            if (st_sz[v]*2 >= st_sz[u]) {
                // heavy edge ==> color the same
                ans[v] = ans[u];
            } else {
                ans[v] = pc++;
            }
            dfs2(v);
        }
    };
    dfs2(0);
    return {ans,pc};
}

void run() {
    int n; cin >> n;
    VLL vals(n); INP(vals,n);
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    if (maxe(vals) < 0) {
        print("0 1");
        return;
    } else if (maxe(vals) == 0) {
        print("0 0");
        return;
    }
    VVI chd; VI par; tie(chd,par) = rootTree(adj,0);
    VI decomp; int np;
    tie(decomp,np) = hld(chd);
    dbg(chd);
    dbg(decomp);
    VVI paths(np);
    function<void (int)> dfs = [&](int u) {
        paths[decomp[u]].pb(u);
        for (int x : chd[u]) dfs(x);
    }; dfs(0);
    dbg(paths);
    VVI subtrees(np);
    rep(i,0,np) {
        if (paths[i].front() != 0) {
            subtrees[decomp[par[paths[i].front()]]].pb(i);
        }
    }
    dbg(subtrees);
    // topo sort subtrees by dependency graph
    VVI ts_adj(np);
    rep(i,1,n) {
        if (decomp[i] != decomp[par[i]]) {
            ts_adj[decomp[i]].pb(decomp[par[i]]);
        }
    }
    dbg(ts_adj);
    VI ts_order = topoSort(ts_adj);
    dbg(ts_order);
    // build
    vector<HeavyPath*> hps(np);
    rep(i,0,np) {
        hps[i] = new HeavyPath(i, paths[i].size(), paths[i], subtrees[i].size(), subtrees[i]);
    }
    for (int i : ts_order) {
        if (paths[i].front() != 0) {
            hps[i]->par = hps[decomp[par[paths[i].front()]]];
        }
        rep(j,0,paths[i].size()) {
            int x = paths[i][j];
            for (int y : chd[x]) {
                if (decomp[y] == i) continue; // ignore heavy edge
                D tmp = hps[decomp[y]]->st.queryAll();
                hps[i]->S[j] += max(0LL, tmp.pref);

                hps[i]->bt.update(hps[i]->subtreeMap[decomp[y]], max(tmp.mx, hps[decomp[y]]->bt.queryAll()));
            }
            hps[i]->st.update(j, vals[x]+hps[i]->S[j]);
        }
    }

    VLL ans(n+1,0);
    rep(i,0,n) {
        // query on day i
        ans[i] = max(hps[0]->bt.queryAll(), hps[0]->st.queryAll().mx);
        // update on day i: vals[i] <- 0
        vals[i] = 0;
        HeavyPath* hptr = hps[decomp[i]];
        ll oldSum = hptr->st.queryAll().pref;
        hptr->st.update(hptr->nodeMap[i], hptr->S[hptr->nodeMap[i]]);
        while (hptr->par) {
            // update st, S, bt on parent
            HeavyPath* pptr = hptr->par;
            ll tmpSum = pptr->st.queryAll().pref;
            pptr->bt.update(pptr->subtreeMap[hptr->id], max(hptr->bt.queryAll(), hptr->st.queryAll().mx));
            int branch_node = par[paths[hptr->id].front()]; // node in parent that branches to cur
            int pos = pptr->nodeMap[branch_node];
            pptr->S[pos] += max(0LL,hptr->st.queryAll().pref) - max(0LL,oldSum);
            pptr->st.update(pos, vals[branch_node] + pptr->S[pos]);
            oldSum = tmpSum;
            hptr = pptr;
        }
    }
    dbg(ans);
    ll bst = 0;
    int bsti = n;
    rep(i,0,n) {
        if (ans[i] > bst || (ans[i] >= bst && i < bsti)) {
            bst = ans[i];
            bsti = i;
        }
    }
    print(bst,bsti);
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