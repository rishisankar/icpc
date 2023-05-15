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
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(VA_ARGS)
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

ll fastpow(ll b, ll e, ll m) {
    ll ans = 1;
    while(e) {
        if(e&1) {
            ans *= b;
            ans %= m;
        }
        b *= b;
        b %= m;
        e >>= 1;
    }
    return ans;
}

ll invert(ll b, ll m) {
    return fastpow(b, m-2, m);
}

#define vd VLL
#define MOD 13

// returns -1 if no solution
// x will store arbitrary solution to Ax = b
int solveLinear(vector<vd>& A, vd &b, vd& x) {
    int n = sz(A), m = sz(x), rank = 0, br, bc;
    vi col(m); iota(all(col), 0);
    rep(i, 0, n) {
        ll v, bv = 0;
        rep(r,i,n)rep(c,i,m) {
            if((v = A[r][c]) != 0) {
                br = r, bc = c, bv = v;
            }
        }
        if(bv == 0) {
            rep(j,i,n) if(b[j] != 0) return -1;
            break;
        }
        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        rep(j,0,n) swap(A[j][i], A[j][bc]);
        bv = invert(A[i][i], MOD);
        rep(j,i+1,n) {
            ll fac = (A[j][i] * bv)%MOD;
            b[j] -= fac*b[i];
            b[j] %= MOD;
            if(b[j] < 0) b[j] += MOD;
            rep(k,i+1,m) {
                A[j][k] -= fac*A[i][k];
                A[j][k] %= MOD;
                if(A[j][k] < 0) A[j][k] += MOD;
            }
        }
        rank++;
    }
    x.assign(m, 0);
    for(int i = rank; i--;) {
        b[i] *= invert(A[i][i], MOD);
        b[i]%=MOD;
        x[col[i]] = b[i];
        rep(j,0,i) {
            b[j] -= A[j][i] * b[i];
            b[j] %= MOD;
            if(b[j] < 0) b[j] += MOD;
        }
    }
    return rank;
}



const long long INF = 10000000000000000LL;
void dijkstra(int s, vector<long long> & d, vector<vector<pair<int,long long>>> &adj) {
    int n = adj.size();
    d.assign(n, INF);

    d[s] = 0;
    using pii = pair<long long, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        long long d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            long long len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}

void run() {
    map<pii, int> nm;
    int n,a,r,t; cin >> n >> a >> r >> t;
    --a; --r;
    vd d(t);
    VVI trip(t);
    rep(i,0,t) {
        cin >> d[i];
        int k; cin >> k;
        vi z(k); rep(j,0,k) {
            cin >> z[j]; z[j]--;
        }
        rep(j,0,k-1) {
            pii pr = {z[j], z[j+1]};
            if (pr.F > pr.S) swap(pr.F,pr.S);
            if (!nm.count(pr)) nm[pr] = sz(nm);
            trip[i].pb(nm[pr]);
        }
    }
    vd sol(sz(nm));
    vector<vd> A(t, vd(sz(nm)));
    rep(i,0,t) {
      for (int x : trip[i]) {
        A[i][x]++;
        A[i][x]%=13;
      }
    }
    assert(solveLinear(A, d, sol) != -1);
    vector<vector<pair<int,long long>>> adj(n);
    for (auto edge : nm) {
        adj[edge.F.F].pb({edge.F.S, sol[edge.S]});
        adj[edge.F.S].pb({edge.F.F, sol[edge.S]});
    }
    VLL dij; dijkstra(a,dij,adj);
    print(dij[r]);
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