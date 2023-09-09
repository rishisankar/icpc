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

vector<int> tin, low;
int timer;
void dfs(int t, int p, VVI& adj, unordered_set<int>& ap) {
    tin[t] = low[t] = timer++;
    int ct = 0;
    for (int x : adj[t]) {
        if (x==p) continue;
        if (tin[x] == -1) {
            // dfs to children (they compute low first)
            dfs(x,t,adj,ap);
            low[t] = min(low[t], low[x]);
            // if a child depends only on t
            if (low[x] >= tin[t] && p!=-1) ap.insert(t);
            ++ct;
        } else {
            // back-edge to ancestor in DFS tree
            low[t] = min(low[t], tin[x]);
        }
    }
    if (p == -1 && ct >= 2) {
        // root node: articulation if multiple children
        ap.insert(t);
    }
}

unordered_set<int> articulationPoints(VVI& adj) {
    int n = adj.size();
    tin.assign(n,-1);
    low.assign(n,0);
    timer = 0;
    unordered_set<int> ap;
    rep(i,0,n) {
        if (tin[i] == -1) {
            dfs(i,-1,adj,ap);
        }
    }
    return ap;
}



int n,m;
map<pii, vector<pii>> adj;
VVB grid;

inline void addj(int i, int j, int ni, int nj) {
    if (ni < 0 || nj < 0 || ni >= n || nj >= 2*m) return;
    if (grid[i][j] || grid[ni][nj]) return;
    adj[{i,j}].pb({ni,nj});
}

// {top, left, bottom, right}
pair<pii,pii> edge_touch(int i, int j) {
    pair<pii,pii> ans = {{0,0},{0,0}};
    if (i == 0 && (j%4 != 3)) ans.F.F++;
    if ((i%2 == 0 && j == 0) || (i%2 == 1 && (j==0||j==1))) ans.F.S++;
    if (i==n-1) {
        if (i%2 == 0) {
            if (j%4 != 2) ans.S.F++;
        } else {
            if (j%4 != 0) ans.S.F++;
        }
    }
    if (((i%2 == 0 && m%2 == 1) || (i%2 == 1 && m%2 == 0)) && j == 2*m-1) ans.S.S++;
    else if (((i%2 == 0 && m%2 == 0) || (i%2 == 1 && m%2 == 1)) && (j == 2*m-1 || j == 2*m-2)) ans.S.S++;
    return ans;
}

inline void fail() {
    print("NO MINIMAL CORRIDOR");
}

void run() {
    dbg("test");
    cin >> n >> m;
    adj.clear();
    grid.resize(n, VB(2*m, 0));
    rep(i,0,n) {
        string s; cin >> s;
        rep(j,0,2*m) {
            grid[i][j] = (s[j] == '1');
        }
    }
    
    rep(i,0,n) {
        rep(j,0,2*m) {
            int k = j/2;
            if ((i+k)%2 == 0 && j%2 == 0) {
                // a11
                addj(i,j,i,j+1);
                addj(i,j,i-1,j+1);
                addj(i,j,i,j-2);
                addj(i,j,i,j-1);
                addj(i,j,i+1,j);
            } else if ((i+k)%2 == 0 && j%2 == 1) {
                // b11
                addj(i,j,i,j-1);
                addj(i,j,i+1,j-1);
                addj(i,j,i,j+1);
                addj(i,j,i,j+2);
                addj(i,j,i-1,j);
            } else if ((i+k)%2 == 1 && j%2 == 0) {
                // a12
                addj(i,j,i-1,j);
                addj(i,j,i-1,j+1);
                addj(i,j,i,j-1);
                addj(i,j,i,j+1);
                addj(i,j,i,j+2);
            } else {
                addj(i,j,i,j-1);
                addj(i,j,i,j-2);
                addj(i,j,i+1,j-1);
                addj(i,j,i+1,j);
                addj(i,j,i,j+1);
            }
        }
    }
    // rep(i,0,n) {
    //     rep(j,0,2*m) {
    //         dbg(mp(i,j),adj[{i,j}]);
    //     }
    // }
    VVI vis(n, VI(2*m,-1));
    int cc = 0;

    rep(i,0,n) {
        rep(j,0,2*m) {
            if (vis[i][j] != -1 || grid[i][j]) continue;
            stack<pii> s;
            s.push({i,j});
            vis[i][j] = cc;
            int cct = 0;
            pair<pii,pii> zz = {{0,0},{0,0}};
            while (!s.empty()) {
                pii t = s.top(); s.pop();
                ++cct;
                pair<pii,pii> et = edge_touch(t.F,t.S);
                zz.F.F += et.F.F;
                zz.F.S += et.F.S;
                zz.S.F += et.S.F;
                zz.S.S += et.S.S;
                if (et.S.S > 0) dbg(t);
                for (pii& x : adj[t]) {
                    if (vis[x.F][x.S] == -1) {
                        vis[x.F][x.S] = cc;
                        s.push({x.F,x.S});
                    }
                }
            }
            if (zz.F.F > 0 && zz.F.S > 0 && zz.S.F > 0 && zz.S.S > 0) {
                dbg(cc, cct, "found corridor");
                dbg(zz);
                map<pii,int> nm;
                vector<pii> revnm;
                VVI apadj(cct);
                rep(i,0,n) {
                    rep(j,0,2*m) {
                        if (vis[i][j] == cc) {
                            if (!nm.count({i,j})) {
                                nm[{i,j}] = sz(nm);
                                revnm.pb({i,j});
                            }
                        }
                    }
                }
                rep(i,0,n) {
                    rep(j,0,2*m) {
                        if (vis[i][j] == cc) {
                            int x = nm[{i,j}];
                            for (pii y : adj[{i,j}]) {
                                apadj[x].pb(nm[y]);
                            }
                        }
                    }
                }
                unordered_set<int> aps = articulationPoints(apadj);
                VB is_ap(cct);
                for (int ap : aps) is_ap[ap] = 1;
                rep(ap,0,cct) {
                    if (is_ap[ap]) continue;
                    pii act = revnm[ap];
                    pair<pii,pii> et = edge_touch(act.F,act.S);
                    pair<pii,pii> result = {{zz.F.F-et.F.F,zz.F.S-et.F.S},{zz.S.F-et.S.F,zz.S.S-et.S.S}};
                    if (result.F.F > 0 && result.F.S > 0 && result.S.F > 0 && result.S.S > 0) {
                        dbg(act);
                        dbg(et);
                        dbg(result);
                        fail();return;
                    }
                }
                print(cct);
                return;
            }
            ++cc;
        }
    }
    fail();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    rep(tests,0,t) run();
}