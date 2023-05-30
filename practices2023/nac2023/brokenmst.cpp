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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

void run() {
    int n,m; cin >> n >> m;
    vector<pair<ll,pii>> edges(m);
    rep(i,0,m) {
        cin >> edges[i].S.F >> edges[i].S.S >> edges[i].F;
        --edges[i].S.F; --edges[i].S.S;
    }
    vector<int> tree_edges(m); iota(all(tree_edges),0);
    sort(all(tree_edges), [&](int e1, int e2) {
        return edges[e1].F < edges[e2].F || (edges[e1].F==edges[e2].F && e1 < e2);
    });
    UF t1(n);
    vector<bool> seen(n-1);
    vector<int> shared_edges, orig_edges;
    unordered_set<int> new_edges;
    for (int e : tree_edges) {
        auto [a,b] = edges[e].S;
        if (!t1.sameSet(a,b)) {
            t1.join(a,b);
            if (e < n-1) {
                shared_edges.pb(e); seen[e] = 1;
            }
            else new_edges.insert(e);
        }
    }
    rep(i,0,n-1) if (!seen[i]) orig_edges.pb(i);
    print(sz(orig_edges));
    rep(i,0,sz(orig_edges)) {
        vi ord;
        rep(j,0,sz(orig_edges)) if (j!=i) ord.pb(orig_edges[j]);
        for (int k : shared_edges) ord.pb(k);
        for (int k : new_edges) ord.pb(k);
        UF dsu(n);
        int ne = -1;
        for (int e : ord) {
            auto [a,b] = edges[e].S;
            if (!dsu.sameSet(a,b)) {
                dsu.join(a,b);
                if (new_edges.count(e)) {
                    assert(ne == -1);
                    ne = e;
                }
            }
        }
        assert(ne!=-1);
        print(orig_edges[i]+1, ne+1);
        orig_edges[i] = ne;
        new_edges.erase(new_edges.find(ne));
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