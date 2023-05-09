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
if >2 special, delete node
if == 2 special, delete node and connect nodes that are connected by special (unless invalid)
if 0 special, np

if 1 special, merge? idk
*/

void dfs_cyc(int t, VVI& adj, VI& colors, VI& par, VI& cyc) {
    if (cyc.size()>0)return;// once cycle found, done
    colors[t] = 1;
    for (int x : adj[t]) {
        if (colors[x] == 2) continue;
        if (colors[x] == 1 && par[t] != x) {
            // cycle found
            int cur = t;
            while (cur != x) {
                cyc.pb(cur);
                cur=par[cur];
            }
            cyc.pb(x);
            cyc.pb(t);
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

/*
for any node:
- if it doesn't have exactly 0 or 2 special, delete it + all edges
    - cascade effect?
- for nodes connected to a special edge, delete the non special edges (do this first)

if a node ever has no 
*/


void run() {
    int n,m,k; cin >> n >> m >> k;
    VVI adjm(n, VI(n, 0));
    vi hasSpecial(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        --a; --b;
        adjm[a][b] = adjm[b][a] = (i < k ? 2 : 1);
        if (i<k) {
            hasSpecial[a]++; hasSpecial[b]++;
        }
    }
    rep(i,0,n) {
        if (hasSpecial[i] >= 2) {
            rep(j,0,n) {
                if (adjm[i][j] == 1) {
                    adjm[i][j] = adjm[j][i] = 0;
                }
            }
        }
    }
    VI deg(n);
    rep(i,0,n) {
        rep(j,0,n) {
            if (adjm[i][j]) {
                ++deg[i];
            }
        }
    }
    dbg(deg);
    rep(i,0,n) {
        if (deg[i] != 0 && deg[i] != 2) {
            rep(j,0,n) {
                if (adjm[i][j]) {
                    adjm[i][j] = adjm[j][i] = 0;
                }
            }
        }
    }
    VVI adj(n);
    rep(i,0,n) {
        rep(j,0,n) {
            if (adjm[i][j]) {
                adj[i].pb(j);
                adj[j].pb(i);
            }
        }
    }
    dbg(adj);
    VI cyc = find_cycle(adj);
    if(sz(cyc)==0) {
        print(-1);
        return;
    }
    print(sz(cyc));
    for (int i : cyc) print(i);

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