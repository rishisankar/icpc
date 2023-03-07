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

void dfs_cyc(int t, VVI& adj, VI& colors, VI& par, VI& cyc) {
    if (cyc.size()>0)return;// once cycle found, done
    colors[t] = 1;
    for (int x : adj[t]) {
        if (colors[x] == 2) continue;
        if (colors[x] == 1) {
            // cycle found
            int cur = t;
            while (cur != x) {
                cyc.pb(cur);
                cur=par[cur];
            }
            cyc.pb(x);
            cyc.pb(t);
            reverse(all(cyc));
            return;
        } else if (colors[x] == 0) {
            par[x] = t;
            dfs_cyc(x,adj,colors,par,cyc);
            if (cyc.size()>0)return; //if cycle found, done
        }
    }
    colors[t] = 2;
}

VI find_cycle(VVI& adj) {
    int n = adj.size();
    VI colors(n,0); // 0 = white, 1 = gray, 2 = black
    VI par(n,-1);
    VI cyc;
    rep(i,0,n) {
        if (colors[i] == 0) {
            dfs_cyc(i,adj,colors,par,cyc);
        }
    }
    return cyc;
}

void run() {
    int n,m; cin >> n >> m;
    VVI adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
    }
    VI ans = find_cycle(adj);
    if (ans.size() > 0) {
        print(ans.size());
        rep(i,0,ans.size()) {
            cout << (ans[i]+1) << " ";
        }
        cout << "\n";
    } else print("IMPOSSIBLE");
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