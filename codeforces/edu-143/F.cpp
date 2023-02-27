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
Distances from s to all other nodes in unweighted graph.
Returns -1 for any node not connected to s.
O(n+m)
*/
vi distances(int s, vector<vi>&adj) {
    int n = adj.size();
    vi dist(n, -1);
    vector<bool> visited(n,false);
    dist[s] = 0;
    visited[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int x : adj[t]) {
            if (visited[x]) continue;
            dist[x] = dist[t]+1;
            visited[x] = true;
            q.push(x);
        }
    }
    return dist;
}

void run() {
    int n; cin >> n; int m = n-1;
    VVI adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    int k; cin >> k;
    vector<int> chips(k); rep(i,0,k) {
        cin >> chips[i]; --chips[i];
    }
    VVI childs;
    vi parent;
    tie(childs,parent) = rootTree(adj, 0);
    vi dists = distances(0, childs);
    vi nodes(n); rep(i,0,n)nodes[i]=i;
    sort(all(nodes),[&](int a, int b) {
        return dists[a] > dists[b];
    });
    int best = 0;
    ll lo = 1, hi = n*(ll)k;
    while (lo <= hi) {
        ll moves = (lo+hi)/2;
        dbg("test", moves);
        bool fail = false;
        // store {number of free spaces incl+below, req distance or -1 if white}
        vector<pii> dp(n, {1,-1});
        rep(i,0,k) dp[chips[i]] = {0,moves/k + ((i < moves%k) ? 1 : 0)};
        dbg(dp);
        for (int x : nodes) {
            if (dp[x].F!=0) {
                // empty space
                for (int c : childs[x]) {
                    dp[x].F = max(dp[x].F, 1+dp[c].F);
                }
            } else {
                // nonempty space -> try to move down, move up if fail
                if (dp[x].S>0) {
                    bool sc = false;
                    for (int c : childs[x]) {
                        if (dp[c].F >= dp[x].S) sc = true;
                    }
                    if (!sc) {
                        if (x == 0) { fail = true; break; }
                        if (dp[parent[x]].S != -1) { fail = true; break; }
                        dp[parent[x]] = {0, dp[x].S-1};
                    }
                }
            }
        }
        dbg("result", moves, fail);
        dbg(dp);
        if (fail) {
            hi = moves-1;
        } else {
            best = moves;
            lo = moves+1;
        }
    }
    print(best);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}