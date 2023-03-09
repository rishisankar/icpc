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


vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

vi topoSort(const vector<unordered_set<int>>& gr) {
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

vector<pii> edgesInReverseTopo(vector<unordered_set<int>>& radj) {
    int n = radj.size();
    vi ts = topoSort(radj);
    vector<pii> edges;
    for (int i : ts) {
        for (int j : radj[i]) edges.pb({j,i});
    }
    return edges;
}

vector<vector<pair<int,int>>> quers; //quers[i] = all queries asking what can reach i
vector<bool> Qans;

vi countReachablePairs(int n, int m, vector<pii>& dg) {
  vector<ull> mask(n);
  vector<int> ans(n,0);
  for (int l = 0; l < n; l += 64) {
    // process 64 at a time via bitmask: 
    int r = min(n, l + 64);
    rep(i,0,n) mask[i] = 0;
    for (int i = l; i < r; ++i) mask[i] = (1ull << (i-l));
    for (pii edge : dg) {
        mask[edge.F]|=mask[edge.S];
    }
    // for each of the n nodes, figure out how many of [l,r) is reachable
    rep(i,l,r) {
        for (auto p : quers[i]) {
            Qans[p.S] = ((mask[p.F] >> (i-l)) & 1);
        }
    }
    // rep(i,0,n)ans[i]+=__builtin_popcountll(mask[i]);
  }
  return ans;
}

void run() {
    int n,m,q; cin >> n >> m >> q; Qans.resize(q);
    VVI adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
    }
    scc(adj, [&](vi& v) {});
    vector<unordered_set<int>> condensation_graphr(ncomps);
    rep(i,0,n) {
        for (int x : adj[i]) {
            if (comp[i] != comp[x]) condensation_graphr[comp[x]].insert(comp[i]);
        }
    }
    vector<pii> dg = edgesInReverseTopo(condensation_graphr);
    quers.resize(ncomps);
    rep(i,0,q) {
        int a,b; cin >> a >> b; a=comp[a-1]; b=comp[b-1];
        if (a==b) Qans[i]=true;
        else {
            quers[b].pb({a,i});
        }
    }
    countReachablePairs(ncomps, dg.size(), dg);

    rep(i,0,q) {
        if (Qans[i]) print("YES"); else print("NO");
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