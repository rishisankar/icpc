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
Approach: reduce to 2-coloring a graph based on constraints

For each node, we need an edge from it to any node that is larger and appears btwn the
first node being pushed and popped.

DSU to store nodes that are connected already, as well as second DSU to compute next largest
    - DSU needs to figure out max elt of set

see two-stack-sorting tests/ for previous impls / tests
*/

struct UF {
	vi e,mx;
	UF(int n) : e(n, -1), mx(n) {
        iota(all(mx),0);
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
    int smax(int x) { return mx[find(x)]; }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
        int amx = mx[a], bmx = mx[b];
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
        mx[a] = max(amx,bmx);
		return true;
	}
};

/*
example:
1 4 0 6 3 5 2 (v)
2 0 6 4 1 5 3 (tms)
*/

void run() {
    int n; cin >> n;
    vi v(n);
    vi tms(n);
    rep(i,0,n) {
        cin >> v[i]; --v[i];
        tms[v[i]] = i;
    }
    UF nge(n+1); // one larger to accommodate no greater elt
    UF mgd(n); // already merged larger elts (so we can avoid adding edges to all)
    int clt = -1; // clear time of element i
    VVI adj(n);
    rep(i,0,n) {
        int p = tms[i]; 
        clt = max(clt, p);
        // invariant: max of (p+1)s set is larger than i ==> allows finding next greatest elt
        nge.join(p, p+1);
        int cur = nge.smax(p), prev = -1;
        while (cur <= clt) {
            adj[p].pb(cur);
            adj[cur].pb(p);
            dbg(p,cur);
            if (prev != -1) mgd.join(prev,cur);
            prev = cur;
            cur = mgd.smax(cur); // jump alr merged elts
            cur = nge.smax(cur+1); // go to next greater
        }
    }
    // graph 2 coloring
    vi colors(n,-1);
    function<bool(int,int)> dfs = [&](int t, int c) {
        if (colors[t] != -1) return colors[t] == c;
        colors[t] = c;
        for (int x : adj[t]) {
            if (!dfs(x,(c^1))) return false;
        }
        return true;
    };
    rep(i,0,n) {
        if (colors[i] == -1 && !dfs(i,0)) {
            print("IMPOSSIBLE");
            return;
        }
    }
    for (int i : colors) cout << (i+1) << ' ';
    cout << "\n";
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