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

int n,k;
VB alive;
vi p, h;
VVI adj;
int a = 0;
int r;
const int MAXD = 50;
VLL dp(MAXD);
//111111110101010101101010
void test(int t) {
    if (t+1 == 18 || t+1 == 21) dbg("working", h[18], h[20], h[15]);
    int req = 0;
    int c = p[t], d=2;
    while (c != -1) {
        if (c > t) {
            // need to allocate on other side?
            if (h[c] < d) {

                req += (d-2>=0 ? dp[d-2] : 0) - (h[c]-2>=0 ? dp[h[c]-2] : 0);
            }
        }
        ++d; c = p[c];
    }
   bool gg=false;
    if (h[t] <= 0) ++req;
    else {
        int zz = 1;
        for (int y : adj[t]) {
            h[y] = h[t]-zz;
             gg = true;
            ++zz;
        }
    }
    if ( t+1 == 21) dbg("zz", h[18], h[20], h[15]);
    if (req + a <= k) {
        // use it!
        alive[t] = true;
        c = p[t], d = 2;
        while (c != -1) {
            if (h[c] < d) {
                h[c] = d;
            }
            ++d; c = p[c];
        }
        if (h[t] == 0) h[t] = 1;
        a += req;
        dbg(t+1, a);  
        for (int y : adj[t]) {
            if (y == 20) dbg(h[y], h[t]);
            if (y > t && !gg) h[y] = h[t]-2;
            if (y == 20) dbg(h[y], h[t]);
            test(y);
        }
    }
}

void run() {
    dp[1] = 1;
    rep(i,2,MAXD) dp[i] = dp[i-1] + dp[i-2] + 1;
    dbg(dp[35]);
    cin >> n >> k;
    p.resize(n); adj.resize(n); alive.resize(n); h.resize(n);
    INP(p,n); rep(i,0,n) if (p[i] != -1) p[i]--;
    rep(i,0,n) if (p[i] != -1) adj[p[i]].pb(i);
    rep(i,0,n) sort(all(adj[i]));
    rep(i,0,n) if (p[i] == -1) r = i;
    test(r);
    dbg(alive);
    for (bool b : alive) cout << b;
    cout << '\n';
    // rep(i,0,24) dbg(i+1,h[i]);
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