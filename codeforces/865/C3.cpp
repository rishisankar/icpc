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

void run() {
    int n,m; cin >> n >> m;
    VVI adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        if (a != 0) adj[a].pb(b);
    }
    int ct = 0;
    VI comps(n);
    scc(adj, [&](vi& c) {
        for (int i : c) comps[i] = ct;
        ++ct;
    });
    VVI cg(ct), rcg(ct);
    rep(i,0,n) {
        for (int j : adj[i]) {
            if (comps[i] != comps[j]) {
                cg[comps[i]].pb(comps[j]);
                rcg[comps[j]].pb(comps[i]);
            }
        }
    }
    // check infinite case:
    rep(i,0,ct) {
        if (comps[0] == i) continue;
        if (sz(cg[i]) == 0) {
            print("INFINITE");
            return;
        }
    }
    VI lvl(ct,-1);
    lvl[comps[0]] = 0;
    queue<int> q;
    q.push(comps[0]);
    int mxl = 0;
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int x : rcg[t]) {
            if (lvl[x] == -1) {
                lvl[x] = lvl[t] + 1;
                mxl = max(mxl, lvl[x]);
                q.push(x);
            }
        }
    }
    VVI vals(mxl+1);
    VB depPrev(n, false);
    rep(i,0,n) {
        vals[lvl[comps[i]]].pb(i);
        for (int j : adj[i]) {
            if (lvl[comps[i]] != lvl[comps[j]]) depPrev[i] = true;
        }
    }
    depPrev[0] = 1;
    rep(i,0,mxl+1) {
        sort(all(vals[i]), [&](int a, int b) {
            return depPrev[a] < depPrev[b];
        });
    }
    vi seq;
    //8 7 8 6 7 8 5 6 7 8 4 5 6 7 8 3 4 5 6 7 8 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8
    function<void (int)> addSeq = [&](int lv) {
        if (lv > mxl) return;
        addSeq(lv+1);
        rep(nlv, lv, mxl+1) {
            for (int i : vals[nlv]) seq.pb(i);
            if (lv == 0) {
                int sx = sz(vals[nlv]);
                rep(j,0,sx) {
                    if (!depPrev[vals[nlv][j]]) seq.pb(vals[nlv][j]);
                }
            }
        }
    };
    addSeq(0);
    print("FINITE");
    print(sz(seq));
    for (int i : seq) cout << (i+1) << ' ';
    cout << '\n';
    dbg(lvl);
    dbg(cg);
    dbg(vals);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}