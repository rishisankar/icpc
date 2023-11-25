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


// O( (m+n) log n )
// define VLL d, VI p; (don't size)
// d gives distances to each point, p gives parent in path
// from cp-algorithms.com

const ll INF = 10000000000000000LL;
void dijkstra(int s, vector<ll>& d, vector<vector<pair<int,ll>>>& adj) {
    int n = adj.size();
    d.assign(n, INF);

    d[s] = 0;
    using pii = pair<ll, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        ll d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            ll len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}

void run() {
    int n,k,m; cin >> n >> k >> m;
    int T, w; cin >> T >> w;
    VB bad(n);
    rep(i,0,k) {
        int x; cin >> x; bad[x-1] = 1;
    }
    vector<vector<pair<int,ll>>> adj(n);
    vector<vector<pair<int,ll>>> adj_nos(n);
    rep(i,0,m) {
        int a,b; ll d; cin >> a >> b >> d;
        --a; --b;
        adj[a].pb({b, d});
        adj[b].pb({a, d});
        if (!bad[a]) adj_nos[a].pb({b,d});
        if (!bad[b]) adj_nos[b].pb({a,d});
    }
    vector<ll> d, dnos;
    dijkstra(0, dnos, adj_nos);
    dijkstra(n-1, d, adj);
    if (d[0] <= T * w) {
        print("No horse needed!");
        return;
    }
    
    ld lo = 0, mx = 1000000000000000.L, hi = mx, bst = hi;
    rep(B,0,150) {
        ld mid = (lo+hi)/2;
        bool valid = 0;
        if (dnos[n-1] != INF) {
            if (dnos[n-1] / mid <= T) valid = 1;
        }
        rep(i,0,n) {
            // spot where horse is snatched
            if (!bad[i] || dnos[i] == INF) continue;
            ld timeTaken = d[i] / (ld)w + dnos[i] / mid;
            if (timeTaken <= T) valid = 1;
        }
        if (valid) {
            bst = mid;
            hi = mid;
        } else {
            lo = mid;
        }
    }
    if (bst == mx) {
        print("Impossible");
    } else {
        print(bst);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    cout.setf(ios::fixed);
    cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}