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
typedef pair<ld,ld> pld;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

// O( (m+n) log n )
// define VLL d, VI p; (don't size)
// d gives distances to each point, p gives parent in path
// from cp-algorithms.com

const ld INF = 10000000000000000.L;
void dijkstra(int s, vector<ld>& d, vector<int>& p, vector<vector<pair<int,ld>>>& adj) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    using pii = pair<ld, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        ld d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            ld len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}


void run() {
    int n,t; cin >> n >> t;
    int xh,yh,xe,ye; cin >> xh >> yh >> xe >> ye;
    vector<pii> p(n);
    rep(i,0,n) cin >> p[i].F >> p[i].S;
    vector<ld> D; VI P;
    vector<vector<pair<int,ld>>> adj(n+2);
    rep(i,0,n) {
        adj[n].pb({i, min(llabs(xh-p[i].F), llabs(yh-p[i].S))});
    }
    ld dx = llabs(xe-xh);
    ld dy = llabs(ye-yh);
    adj[n].pb({n+1, sqrt(dx*dx+dy*dy)});
    rep(i,0,n) {
        adj[i].pb({n+1, min(llabs(xe-p[i].F), llabs(ye-p[i].S)) + t});
        rep(j,0,n) {
            adj[i].pb({j,t});
        }
    }
    dijkstra(n, D,P,adj);
    print(D[n+1]);
    VI path = restore_path(n,n+1, P);
    // dbg(path);
    vector<pair<int, pld>> z;
    rep(i,0,sz(path)-1) {
        if (path[i] == n) {
            if (path[i+1] == n+1) {
                z.pb({0, {xe,ye}});
            } else if (path[i+1] == n) continue;
            else {
                int j = path[i+1];
                if (llabs(xh-p[j].F) < llabs(yh-p[j].S)) z.pb({0, {p[j].F, yh}});
                else z.pb({0, {xh, p[j].S}});
            }
        } else if (path[i] == n+1) {
            break;
        } else {
            int j = path[i];
            if (path[i+1] == n) {
                // impossible
            } else if (path[i+1] == n+1) {
                pld plp;
                if (llabs(xe-p[j].F) < llabs(ye-p[j].S)) plp = {p[j].F, ye};
                else plp = {xe, p[j].S};
                z.pb({j+1, {plp}});
                z.pb({0,{xe,ye}});
            } else {
                z.pb({j+1, {p[j].F, p[path[i+1]].S}});
            }
        }
    }
    print(sz(z));
    for (auto x : z) {
        print(x.F, x.S.F, x.S.S);
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