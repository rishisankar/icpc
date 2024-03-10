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

template<typename T> inline T ceildiv(T a, T b) {return (a+b-1)/b;}

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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

const ll INF = 10000000000000000LL;
void dijkstra(int s, vector<ll>& d, vector<int>& p, vector<vector<pair<int,ll>>>& adj) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

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
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

VVI components(VVI adj) {
    int n = adj.size();
    vector<bool> vis(n,false);
    VVI comps;
    rep(i,0,n) {
        if (!vis[i]) {
            vis[i] = true;
            comps.resize(comps.size()+1);
            comps.back().pb(i);
            stack<int> s;
            s.push(i);
            while (!s.empty()) {
                int t = s.top(); s.pop();
                for (int x : adj[t]) {
                    if (vis[x]) continue;
                    vis[x] = true;
                    comps.back().pb(x);
                    s.push(x);
                }
            }
        }
    }
    return comps;
}

void run() {
    int n,r; cin >> n >> r;
    int N = (1<<n);
    ll rqc = 0;
    vector<vector<pair<int,ll>>> adj(N);
    vector<pair<pii,ll>> edges;
    
    VVI adjReq(n);
    int gl = 0;

    rep(i,0,r) {
        int a,b; cin >> a >> b;
        --a; --b;
        ll x; cin >> x; rqc += x;
        edges.pb({{a,b},x});
        gl ^= (1<<a);
        gl ^= (1<<b);
        adjReq[a].pb(b);
        adjReq[b].pb(a);
    }
    VVI compsRe = components(adjReq);
    VVI compsReq;
    for (auto vec : compsRe) {
        if (sz(vec) > 1)
        compsReq.pb(vec);
    }

    int f; cin >> f;
    rep(i,0,f) {
        int a,b; cin >> a >> b; --a; --b;
        ll x; cin >> x;
        edges.pb({{a,b},x});
    }
    dbg(compsReq);

    if (r == 0) {
        print(0);
        return;
    }

    rep(i,0,N) {
        for (auto& ed : edges) {
            int a = ed.F.F, b = ed.F.S;
            ll x = ed.S;
            int msk = 0;
            msk |= (1 << a);
            msk |= (1 << b);
            int ni = i ^ msk;
            adj[i].pb({ni,x});
        }
    }

    VLL d; VI p;
    dijkstra(0, d, p, adj);

    vector<vector<ll>> adjm(n, VLL(n, LLONG_MAX));
    for (auto & ed : edges) {
        int a = ed.F.F, b = ed.F.S;
        ll x = ed.S;
        adjm[a][b] = adjm[b][a] = min(adjm[a][b], x);
    }

    vector<pair<pii,ll>> edbf;
    vector<int> edbfMask;
    rep(i,0,n) {
        rep(j,i+1,n) {
            if (adjm[i][j] != LLONG_MAX){
                edbf.pb({{i,j}, adjm[i][j]});
                edbfMask.pb((1<<i)+(1<<j));
            }
        }
    }
    ll bst = LLONG_MAX;


    dbg(compsReq);

    dbg(edbf);
    dbg(edbfMask);

    int M = sz(edbf) + 1;
    dbg(M);
    rep(i1,0,M) {
        rep(i2,min(i1+1,M-1),M) {
            rep(i3,min(i2+1,M-1),M) {
                rep(i4,min(i3+1,M-1),M) {
                    rep(i5,min(i4+1,M-1),M) {

                        UF dsu(n);
                        for (vi& v : compsReq) {
                            rep(i,1,sz(v)) {
                                dsu.join(v[0],v[i]);
                            }
                        }
                        if (i1!=M-1) dsu.join(edbf[i1].F.F, edbf[i1].F.S);
                        if (i2!=M-1) dsu.join(edbf[i2].F.F, edbf[i2].F.S);
                        if (i3!=M-1) dsu.join(edbf[i3].F.F, edbf[i3].F.S);
                        if (i4!=M-1) dsu.join(edbf[i4].F.F, edbf[i4].F.S);
                        if (i5!=M-1) dsu.join(edbf[i5].F.F, edbf[i5].F.S);
                        bool ok = 1;
                        rep(i,1,sz(compsReq)) {
                            if (!dsu.sameSet(compsReq[i][0], compsReq[0][0])) {
                                ok = 0; break;
                            }
                        }
                        if (!dsu.sameSet(compsReq[0][0], 0)) ok = 0;
                        if (!ok) continue;
                        // dbg(i1,i2,i3,i4,i5);

                        ll exc = 0;
                        int msk = gl;
                        if (i1!=M-1) {
                            exc += edbf[i1].S;
                            msk ^= edbfMask[i1];
                        }
                        if (i2!=M-1) {
                            exc += edbf[i2].S;
                            msk ^= edbfMask[i2];
                        }
                        if (i3!=M-1) {
                            exc += edbf[i3].S;
                            msk ^= edbfMask[i3];
                        }
                        if (i4!=M-1) {
                            exc += edbf[i4].S;
                            msk ^= edbfMask[i4];
                        }
                        if (i5!=M-1) {
                            exc += edbf[i5].S;
                            msk ^= edbfMask[i5];
                        }

                        exc += d[msk];

                        bst = min(bst,exc + rqc);

                    }
                }
            }
        }
    }
    print(bst);
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