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

// complexity: O(m^2*n + Tm), can do TlogB instead of Tm with convex hull trick

void run() {
    int m,n; cin >> m >> n;
    ll a; cin >> a;
    vector<VVI> adj(n, VVI(m));
    VVB sc(m-1, VB(m));
    vector<VVI> d(m, VVI(n, VI(m,-1))); // # station changes, cur position
    rep(i,0,n) {
        int k; cin >> k;
        vi v(k); rep(j,0,k) { cin >> v[j]; -- v[j]; }
        rep(j,0,k) {
            if (j<k-1)adj[i][v[j]].pb(v[j+1]);
            if (j>0)adj[i][v[j]].pb(v[j-1]);
        }
    }
    queue<pair<int, pii>> q;
    rep(i,0,n) {
        d[0][i][0] = 0;
        q.push({0,{i,0}});
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        for (int x : adj[p.S.F][p.S.S]) {
            if (d[p.F][p.S.F][x] == -1) {
                d[p.F][p.S.F][x] = d[p.F][p.S.F][p.S.S]+1;
                q.push({p.F,{p.S.F,x}});
            }
        }
        if (p.F<m-1 && !sc[p.F][p.S.S]) {
            sc[p.F][p.S.S] = 1;
            rep(i,0,n) {
                if (d[p.F+1][i][p.S.S] == -1) {
                    d[p.F+1][i][p.S.S] = d[p.F][p.S.F][p.S.S];
                    q.push({p.F+1,{i,p.S.S}});
                }
            }
        }
    }
    VLL mina(m, -1);
    rep(i,0,m) {
        rep(j,0,n) {
            if (d[i][j][m-1] != -1) {
                if (mina[i] == -1 || mina[i] > d[i][j][m-1]) mina[i] = d[i][j][m-1];
            }
        }
    }
    rep(i,0,m) if (mina[i]!=-1) mina[i]*=a;
    int t; cin >> t;
    rep(i,0,t) {
        ll b; cin >> b;
        ll bst = LLONG_MAX;
        rep(j,0,m) {
            if (mina[j]!=-1) {
                bst=min(bst,mina[j]+j*b);
            }
        }
        print(bst);
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