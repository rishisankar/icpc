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

int K;

struct RollbackUF {
    int nc; // # comps
	vi e; vector<pii> st;
	RollbackUF(int n) : nc(n), e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;) {
			e[st[i].first] = st[i].second;
        }
        nc += (time()-t)/2;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
        --nc;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
    int comps() { return nc; }
};

vi dynacon(int n, vector<pii> G, vector<pii> events) {
    int n_ev = sz(events), m = sz(G);
    // make edges have a<b property (for map)
    rep(i,0,m) if (G[i].F > G[i].S) swap(G[i].F,G[i].S);
    rep(i,0,n_ev) if (events[i].F > events[i].S) swap(events[i].F,events[i].S);
    // figure out how long each event is "alive" for
    vector<pair<pii,pii>> alive; // first pii = edge, second pii [t,s] = active from time t to time s
    map<pii, int> active; // active edges
    rep(i,0,m) active[G[i]] = 0;
    rep(i,0,n_ev) {
        auto it = active.find(events[i]);
        if (it != active.end()) { // edge exists --> del
            alive.pb({events[i], {it->S,i}});
            active.erase(it);
        } else {
            active[events[i]] = i+1;
        }
    }
    // remaining edges
    for (auto p : active) alive.pb({p.F, {p.S, n_ev}});
    // construct segtree
    vector<vector<pii>> st(4*n_ev+8); // segtree over [0 ... n_ev]
    function<void(int,int,int,int,int,pii)> addST = [&](int v, int lo, int hi, int l, int r, pii ed) {
        if (r < lo || l > hi) return;
        if (l <= lo && hi <= r) {
            st[v].pb(ed);
            return;
        }
        int mid = (lo+hi)/2;
        addST(2*v,lo,mid,l,r,ed);
        addST(2*v+1,mid+1,hi,l,r,ed);
    };
    rep(i,0,sz(alive)) addST(1,0,n_ev,alive[i].S.F,alive[i].S.S,alive[i].F);
    // run dfs to compute answers
    vi ans(n_ev+1); // +1 to store # comps before first event
    RollbackUF dsu(n);
    function<void(int,int,int)> dfs = [&](int v, int lo, int hi) {
        // add all edges
        int tm = dsu.time();
        for (pii ed : st[v]) {
            dsu.join(ed.F, ed.S);
        }
        if (lo==hi) {
            ans[lo] = (dsu.find(0) == dsu.find(2*K) ? 0 : (dsu.find(0) == dsu.find(2*K+1) ? 1 : 2));//dsu.comps();
        } else {
            int mid = (lo+hi)/2;
            dfs(2*v,lo,mid);
            dfs(2*v+1,mid+1,hi);
        }
        dsu.rollback(tm);
    };
    dfs(1,0,n_ev);
    return ans;
}

void run() {
    int n,m,k,t; cin >> n >> m >> k >> t; K = k-1;
    vector<pair<pii, bool>> edges;
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        string s; cin >> s;
        edges.pb({{a,b},s=="imposter"});
    }
    // edges 2*n, 2*n+1 = C,I
    vector<pii> G;
    rep(i,t,m) {
        if (edges[i].S) {
            G.pb({2*edges[i].F.F, 2*edges[i].F.S+1});
            G.pb({2*edges[i].F.F+1, 2*edges[i].F.S});
        } else {
            G.pb({2*edges[i].F.F, 2*edges[i].F.S});
            G.pb({2*edges[i].F.F+1, 2*edges[i].F.S+1});
        }
    }
    vector<pii> events;
    rep(i,0,m-t) {
        if (edges[i].S) {
            events.pb({2*edges[i].F.F, 2*edges[i].F.S+1});
            events.pb({2*edges[i].F.F+1, 2*edges[i].F.S});
        } else {
            events.pb({2*edges[i].F.F, 2*edges[i].F.S});
            events.pb({2*edges[i].F.F+1, 2*edges[i].F.S+1});
        }
        int j = i+t;
        if (edges[j].S) {
            events.pb({2*edges[j].F.F, 2*edges[j].F.S+1});
            events.pb({2*edges[j].F.F+1, 2*edges[j].F.S});
        } else {
            events.pb({2*edges[j].F.F, 2*edges[j].F.S});
            events.pb({2*edges[j].F.F+1, 2*edges[j].F.S+1});
        }
    }
    dbg(sz(events));
    vi ans = dynacon(2*n,G,events);
    dbg(sz(ans));
    dbg(ans);
    int res = 1;
    for (int i = 0; i < sz(ans); i += 4) {
        if (ans[i] != 2) {
            print(res, ans[i] == 1 ? "imposter" : "crewmate");
            return;
        }
        ++res;
    }
    print(-1);

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