#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
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
#define int ll
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
typedef pair<ll, ll> PII;
typedef pair<ll, ll> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

typedef pair<ll,ll> T;  // or any other comparable type

typedef tree < T ,  null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update > pbds_tree;
const ll MAX_S = 200000;

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

inline void repl(vi& v, ll& x, ll& xp) {
    auto it = lower_bound(all(v), x);
    *it = xp;
}

void run() {
    int n; cin >> n;
    set<int> coords;
    vi v1(n),v2(n);
    INP(v1,n); INP(v2,n);
    rep(i,0,n) coords.insert(v1[i]);
    unordered_map<int,int> nm;
    for (int i : coords) nm[i] = sz(nm);
    int k = sz(coords);
    VVI p1(k), p2(k);
    rep(i,0,n) {
        v1[i] = nm[v1[i]];
        v2[i] = nm[v2[i]];
        p1[v1[i]].pb(i);
        p2[v2[i]].pb(i);
    }
    dbg(v1);
    dbg(v2);
    pbds_tree tr1, tr2;
    rep(i,0,n) {
        tr1.insert({i, v1[i]});
        tr2.insert({i, v2[i]});
    }
    ll ans = 0;
    VPII swaps;
    rep(i,0,k) {
        int vj = -1;
        int vjdir;
        VVI adj(sz(p1[i]));
        rep(j,0,sz(p1[i])) {
            int a = tr1.order_of_key({p1[i][j],i});
            int b = tr2.order_of_key({p2[i][j],i});
            ll x = llabs(a-b);
            ans += x;
            // dbg(i,j,llabs(a-b));

            // find the j that can be moved first
            if (a < b) {
                if (j == sz(p1[i])-1 || tr1.order_of_key({p1[i][j+1],i})-a > x) {
                    vj = j;   
                } else {
                    adj[j+1].pb(j);
                }
            } else {
                if (j == 0 || a-tr1.order_of_key({p1[i][j-1],i}) > x) vj = j;
                else adj[j-1].pb(j);
            }
            // if (vj == j) dbg(i,vj);
        }
        // assert(vj != -1);
        // dbg(i,vj);
        if (sz(swaps) <= MAX_S) {
            vi jord = topoSort(adj);
            // rep(j,vj,sz(p1[i])) jord.pb(j);
            // for (int j = vj-1; j >= 0; --j) jord.pb(j);
            for (int j : jord) {
                if (sz(swaps) >= MAX_S) break;
                int a = tr1.order_of_key({p1[i][j],i});
                int b = tr2.order_of_key({p2[i][j],i});
                if (a < b) {
                    rep(l, 0, b-a) {
                        if (sz(swaps) >= MAX_S) break;
                        // want to swap elements at a+l, a+l+1
                        auto it1 = tr1.find_by_order(a+l);
                        auto it2 = tr1.find_by_order(a+l+1);
                        pii e1 = *it1;
                        pii e2 = *it2;
                        tr1.erase(it1);
                        tr1.erase(tr1.find(e2));
                        swaps.pb({e1.F, e2.F});
                        repl(p1[e1.S], e1.F, e2.F);
                        repl(p1[e2.S], e2.F, e1.F);
                        tr1.insert({e2.F, e1.S});
                        tr1.insert({e1.F, e2.S});
                    }
                } else {
                    rep(l, 0, a-b) {
                        if (sz(swaps) >= MAX_S) break;
                        // want to swap elements at a-l, a-l-1
                        auto it1 = tr1.find_by_order(a-l-1);
                        auto it2 = tr1.find_by_order(a-l);
                        pii e1 = *it1;
                        pii e2 = *it2;
                        tr1.erase(it1);
                        tr1.erase(tr1.find(e2));
                        swaps.pb({e1.F, e2.F});
                        repl(p1[e1.S], e1.F, e2.F);
                        repl(p1[e2.S], e2.F, e1.F);
                        tr1.insert({e2.F, e1.S});
                        tr1.insert({e1.F, e2.S});
                    }
                }
            }
        }
        rep(j,0,sz(p1[i])) {
            tr1.erase(tr1.find({p1[i][j],i}));
            tr2.erase(tr2.find({p2[i][j],i}));
        }
    }
    print(ans);
    if (sz(swaps) < MAX_S) assert(sz(swaps) == ans);
    else assert (ans >= MAX_S);
    rep(i,0,min((ll)MAX_S, ans)) {
        assert(swaps[i].F < swaps[i].S);
        print(swaps[i].F+1, swaps[i].S+1);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}