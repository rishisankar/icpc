// works but slow af lol

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
Iterate through each operation.
    (1) clear operation: clear corresponding stack
    (2) push operation (can push to 0): fail
    (3) push operation (can push to 1): push to that stack
    (4) push operation (can push to 2):
        if constraints define it, then follow. else choose arbitrarily
 
Verify solution at the end (auto verified?)
 
Fails at n=7
    {2, 5, 1, 7, 4, 6, 3}
    {5, 7, 2, 4, 1, 6, 3}
 
*/
 
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
 
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
 
// complement set
inline int compzl(VVI& adj, UF& dsu, int c) {
    if (sz(adj[c]) > 0) return dsu.find(adj[c][0]);
    else return -1;
}
 
void run() {
    int n; cin >> n;
    vi vz(n); INP(vz,n);
    rep(i,0,n) vz[i]--; // make 0-indexed
    vi vmap(n);
    vector<pii> vx; vx.pb({vz[0],0});
    rep(i,1,n) {
        if (vz[i] == vz[i-1]-1) {
            vmap[i] = vmap[i-1];
        } else {
            vmap[i] = sz(vx);
            vx.pb({vz[i], sz(vx)});
        }
    }
    sort(all(vx));
    vi v(sz(vx));
    rep(i,0,sz(vx)) {
        v[vx[i].S] = i;
    }
    dbg(v);
    n = sz(v);
    int cur = 0;
    VB vis(n,0);
    vector<pair<bool,int>> ops;
    rep(i,0,n) {
        ops.pb({1,v[i]});
        vis[v[i]] = 1;
        while (cur < n && vis[cur]) {
            ops.pb({0,cur++});
        }
    }
    VPII ranges(n);
    vector<int> rmqVals(2*n);
    rep(i,0,2*n) {
        // populate ranges
        if (ops[i].F) ranges[ops[i].S].F = i;
        else ranges[ops[i].S].S = i;
        // populate rmq vector (can optimize)
        rmqVals[i] = ops[i].S;
    }
    RMQ rmq(rmqVals);
    VB is1(n); // is assigned to stack 1?
    VB assgn(n);
    // constraint graph
    VVI adj(n);
    rep(i,0,n) {
        // if (ranges[i].F+1 < ranges[i].S) {
        //     int K = rmq.query(ranges[i].F+1, ranges[i].S);
        //     if (K > i) {
        //         adj[i].pb(K);
        //         adj[K].pb(i);
        //     }
        // }
        // slower version:
        int rf = ranges[i].F+1;
        while (rf < ranges[i].S) {
            int K = rmq.query(rf, ranges[i].S);
            if (K > i) {
                adj[i].pb(K);
                adj[K].pb(i);
                rf = ranges[K].F+1;
            } else break;
        }
    }
    UF dsu(n);
    rep(i,0,n) {
        for (int x : adj[i]) dsu.join(adj[i][0], x);
    }
 
    stack<int> s1,s2;
    s1.push(n); s2.push(n+1);
    rep(i,0,2*n) {
        if (ops[i].F) {
            // push operation
            int t = ops[i].S;
            if (s1.top() > s2.top()) {
                if (s2.top() > t) {
                    if (is1[dsu.find(t)]) {
                        s1.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = false;
                        assgn[t] = true;
                    } else {
                        s2.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = true;
                        assgn[t] = false;
                    }
                } else if (s1.top() > t) {
                    s1.push(t);
                    is1[dsu.find(t)] = true;
                    int cm = compzl(adj,dsu,dsu.find(t));
                    if (cm != -1) is1[cm] = false;
                    assgn[t] = true;
                } else {
                    print("IMPOSSIBLE");
                    return;
                }
            } else {
                if (s1.top() > t) {
                    if (is1[dsu.find(t)]) {
                        s1.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = false;
                        assgn[t] = true;
                    } else {
                        s2.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = true;
                        assgn[t] = false;
                    }
                } else if (s2.top() > t) {
                    s2.push(t);
                    is1[dsu.find(t)] = false;
                    int cm = compzl(adj,dsu,dsu.find(t));
                    if (cm != -1) is1[cm] = true;
                    assgn[t] = false;
                } else {
                    print("IMPOSSIBLE");
                    return;
                }
            }
        } else {
            // clear operation
            if (assgn[ops[i].S]) s1.pop(); else s2.pop();
        }
    }
    rep(i,0,sz(vmap)) cout << (assgn[v[vmap[i]]]+1) << ' ';
    cout << '\n';
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