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

void run() {
    int n,d; cin >> n >> d;
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    VI par(n,-1);
    VI nc(n,0);
    VI dist(n,0);
    stack<int> s;
    s.push(0);
    while (!s.empty()) {
        int t = s.top(); s.pop();
        for (int x : adj[t]) if (x != par[t]) {
            nc[t]++;
            par[x] = t;
            dist[x] = dist[t]+1;
            s.push(x);
        }
    }
    // dbg(par);
    // dbg(nc);
    // dbg(dist);
    set<pii> leafs;
    rep(i,0,n) {
        if (nc[i] == 0) leafs.insert({dist[i],i});
    }
    VI cd(n,-1);
    vi ans;
    while(!leafs.empty()) {
        pii t = *(leafs.rbegin());
        leafs.erase(prev(leafs.end()));
        if (cd[t.S]>=0) continue;
        ans.pb(t.S);
        queue<pii> q;
        cd[t.S] = d-1;
        if (par[t.S]!=-1) {
            nc[par[t.S]]--;
            if (nc[par[t.S]] == 0) leafs.insert({dist[par[t.S]], par[t.S]});
        }
        q.push({t.S,d-1});
        while (!q.empty()) {
            pii tp = q.front(); q.pop();
            if (tp.S > 0) { // can clear neighbors
                for (int x : adj[tp.F]) {
                    if (cd[x]<tp.S-1) {
                        cd[x] = tp.S-1;
                        if (par[x]!=-1) {
                            nc[par[x]]--;
                            if (nc[par[x]] == 0) leafs.insert({dist[par[x]], par[x]});
                        }
                        q.push({x,tp.S-1});
                    }
                }
            }
        }
    }
    print(sz(ans));
    for (int i : ans) cout << (i+1) << ' ';
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