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

struct custom_hash { // https://codeforces.com/blog/entry/62393
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

int n,k;
vi nxt;
VVI radj;
vector<vi> tbl;
vi cycdist, cycpar, tree_pref, tree_ans;

vector<vi> treeJump(vi& P){
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
	vector<vi> jmp(d, P);
	rep(i,1,d) rep(j,0,sz(P))
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps){
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}

struct cycle {
    unordered_map<int,int> ord;
    int csiz;
    vi pref;
    vi vals;//copy of cyc
    cycle(vi& cyc) : csiz(sz(cyc)) {
        rep(i,0,csiz) ord[cyc[i]] = i;
        pref.resize(csiz);
        rep(i,0,csiz)vals.pb(cyc[i]);
    }
    // dist = # nodes to paint
    void add_to_cycle(int node, int dist) {
        dist = min(dist, csiz);
        node = ord[node];
        dbg("add to cycle", node, dist);
        int last = node + dist - 1;
        if (last >= csiz) {
            add_inv(node,csiz-1);
            add_inv(0,last%csiz);
        } else {
            add_inv(node, last);
        }
    }
    void add_inv(int n1, int n2) {
        dbg("add_inv",n1,n2);
        pref[n1]++;
        if (n2 != csiz-1) pref[n2+1]--;
    }
    void solve() {
        dbg("cyc solve", csiz);
        dbg(pref);
        dbg(vals);
        rep(i,1,csiz) pref[i] = pref[i-1] + pref[i];
        rep(i,0,csiz) tree_ans[vals[i]] = pref[i];
    }
};

unordered_map<int,cycle*> cycles;
vector<cycle*> all_cycles;
vi cycle_nodes;

// dist = # nodes to paint
void add_to_tree(int node, int dist) {
    dist = min(dist, cycdist[node]);
    if (dist == 0) return; // nothing to do
    tree_pref[node]++;
    int kill = jmp(tbl, node, dist);
    if (cycdist[kill] != 0) tree_pref[kill]--;
}

void tree_pref_dfs(int node) {
    for (int x : radj[node]) {
        tree_pref_dfs(x);
        tree_ans[node] += tree_ans[x];
    }
    tree_ans[node] += tree_pref[node];
}

void compute_tree_pref() {
    for (int c : cycle_nodes) {
        for (int x : radj[c]) {
            if (cycdist[x] != 0) {
                tree_pref_dfs(x);
            }
        }
    }
}

void proc_node(int node) {
    add_to_tree(node, k+1);
    if (cycdist[node] <= k) {
        cycles[cycpar[node]]->add_to_cycle(cycpar[node], k-cycdist[node]+1);
    }
}

void run() {
    cin >> n >> k;
    nxt.resize(n);
    radj.resize(n);
    rep(i,0,n) { cin >> nxt[i]; --nxt[i]; radj[nxt[i]].pb(i); }
    tbl = treeJump(nxt);
    cycdist.assign(n,-1); // 0 if in cycle, otherwise steps to get to cycle
    cycpar.assign(n,-1); // parent node that's in a cycle
    tree_pref.resize(n);
    tree_ans.resize(n);
    queue<pii> dist_queue;
    vi vis(n); // 0 = unvis, 1 = vis in this iter, 2 = vis prev
    rep(i,0,n) {
        if (vis[i]) continue;
        unordered_set<int> needs_upd;
        int x = i;
        while (!vis[x]) {
            vis[x] = 1;
            needs_upd.insert(x);
            x = nxt[x];
        }
        if (vis[x] == 1) {
            // found cycle
            vi cyc;
            cyc.pb(x);
            int y = nxt[x];
            while (y != x) {
                cyc.pb(y);
                y = nxt[y];
            }
            dbg("cycle", cyc);
            cycle* new_cyc = new cycle(cyc);
            all_cycles.pb(new_cyc);
            for (int z : cyc) {
                cycles[z] = new_cyc;
                cycdist[z] = 0;
                dist_queue.push({z,z});
                cycpar[z] = z;
                cycle_nodes.pb(z);
            }
        }
        for (int z : needs_upd) vis[z] = 2;
    }
    while (!dist_queue.empty()) {
        pii qtop = dist_queue.front(); dist_queue.pop();
        cycdist[qtop.F] = (qtop.F == qtop.S ? 0 : 1+cycdist[qtop.S]);
        cycpar[qtop.F] = (qtop.F == qtop.S ? qtop.S : cycpar[qtop.S]);
        for (int x : radj[qtop.F]) {
            if (cycdist[x] != 0) {
                dist_queue.push({x,qtop.F});
            }
        }
    }
    dbg(cycdist);
    dbg(cycpar);
    rep(i,0,n) proc_node(i);
    compute_tree_pref();
    for (cycle* ucyc : all_cycles) ucyc->solve();
    dbg(tree_ans);
    for (int i : tree_ans)print(i);
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