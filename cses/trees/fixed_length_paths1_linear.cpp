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
Root a tree at node r. Returns {childs, parent}. O(n)
*/
pair<vector<vi>,vi> rootTree(vector<vi>& adj, int r) {
    int n = adj.size();
    vector<vi> childs(n);
    vi parent(n);
    vector<bool> visited(n,false);
    stack<int> s;
    s.push(r);
    visited[r] = true;
    parent[r] = -1;
    while (!s.empty()) {
        int t = s.top();
        s.pop();
        for (int x : adj[t]) {
            if (visited[x]) continue;
            parent[x] = t;
            childs[t].push_back(x);
            visited[x] = true;
            s.push(x);
        }
    }
    return {childs,parent};
}

/*
{1, 1|2, 1|2|3, 1|2|3|4}
{1, 1|2}
{add, }
*/

typedef deque<ll> di;

// prefix sum structure: [add, childs of depth 1, childs of depth 1|2, ...]
void merge(di& pf1, di& pf2) {
    if (pf2.size() > pf1.size()) swap(pf1,pf2);
    rep(i,1,pf2.size()) pf2[i] += pf2[0];
    pf1[0] += pf2.back();
    rep(i,1,pf2.size()) pf1[i] += pf2[i] - pf2.back();
}

ll get(di& pf, int m) {
    if (m <= 0) return 0;
    if (m >= pf.size())m=pf.size()-1;
    return pf[m]+pf[0];
}

void run() {
    int n,k1,k2; cin >> n >> k1; k2 = k1;
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    VVI chd; VI par;
    tie(chd,par) = rootTree(adj,0);
    VI d(n);
    function<void(int)> dfs = [&](int x) {
        d[x] = 1;
        for (int c : chd[x]) {
            dfs(c);
            d[x] = max(d[x], 1 + d[c]);
        }
    }; dfs(0);
    rep(i,0,n) {
        for (int& x : chd[i]) {
            if (d[x] > d[chd[i][0]]) swap(x,chd[i][0]);
        }
    }
    ll ans = 0;
    vector<di> pfs(n);
    function<void(int)> dfs2 = [&](int x) {
        if (chd[x].empty()) {
            pfs[x] = {0,1};
        } else {
            for (int c : chd[x]) dfs2(c);
            di& p = pfs[chd[x][0]];
            ans += get(p,k2) - get(p,k1-1);
            rep(i,1,chd[x].size()) {
                di& p2 = pfs[chd[x][i]];
                rep(k,1,p2.size()) {
                    ans += (get(p2,k)-get(p2,k-1)) * (get(p,k2-k)-get(p,k1-k-1));
                    if (k1 <= k && k <= k2) ans += get(p2,k) - get(p2,k-1); // path fully along subtree
                }
                merge(p,p2);
            }
            ll tmp = p.front(); p.pop_front();
            p.push_front(-tmp); p.push_front(tmp+1);
            swap(pfs[x],p);
        }
    }; dfs2(0);
    print(ans);
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