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
const long long INF = 10000000000000000LL;

void run() {
    int n,m; cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n);
    rep(i,0,m) {
        int a,b; ll c; cin >> a >> b >> c;
        --a; --b;
        adj[a].pb({b,c});
        adj[b].pb({a,c});
    }
    VVLL dp(n, VLL(n, INF)); // dp[i][j] = shortest path to node j from node 0 using i edges
    dp[0][0] = 0;
    ll cb = INF;
    unordered_set<int> valm;
    rep(ne, 1, n) {
        rep(x,0,n) {
            for (auto& e : adj[x]) {
                dp[ne][e.F] = min(dp[ne][e.F], dp[ne-1][x] + e.S);
            }
        }
        if (dp[ne][n-1] < cb) cb = dp[ne][n-1];
    }
    rep(ne,1,n) {
        if (dp[ne][n-1] == cb) {
            valm.insert(ne);
        }
    }
    stack<pair<int, pll>> hull; // slope, intersection loc (frac)
    hull.push({1, {INF,1}});
    rep(ne,2,n) {
        if (dp[ne][n-1] >= dp[hull.top().F][n-1]) continue;
        while(!hull.empty()) {
            auto [k, pt] = hull.top();  // eqn: k*c + dp[k][n-1], ne*c + dp[ne][n-1]
            pll inz = {dp[k][n-1] - dp[ne][n-1], ne-k};
            if (inz.F * (__int128_t)pt.S > inz.S *(__int128_t) pt.F) hull.pop();
            else {
                hull.push({ne, inz});
                break;
            }
        }
    }
    while (!hull.empty()) {
        valm.insert(hull.top().F);
        hull.pop();
    }
    for (int i : valm) dbg(i);
    VB on_sp(n, false);
    on_sp[0] = on_sp[n-1] = 1;
    for (int k : valm) {
        stack<pii> s;
        unordered_set<int> vis;
        s.push({n-1,k});
        vis.insert(n-1);
        while (!s.empty()) {
            auto [x,ec] = s.top(); s.pop();
            if (k == 2) dbg(x+1,ec);
            for (auto& e : adj[x]) {
                if (ec > 0 && dp[ec-1][e.F] + e.S == dp[ec][x]) {
                    if (!vis.count(e.F)) {
                        vis.insert(e.F);
                        on_sp[e.F] = 1;
                        s.push({e.F,ec-1});
                        if (e.F == 6) dbg(k);
                    }
                }
            }
        }
    }
    dbg(on_sp);
    vi ans;
    rep(i,0,n) if (!on_sp[i]) ans.pb(i+1);
    print(sz(ans));
    for (int i : ans) cout << i << ' ';
    if(sz(ans)!=0) cout<<"\n";
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