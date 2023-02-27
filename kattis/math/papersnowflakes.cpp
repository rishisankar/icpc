#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define REP(i, j) FOR(i, 0, j)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}

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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
typedef pair<ll,ll> pll;
void run() {
    int n, m; cin >> n >> m;
    ll L; cin >> L;
    vector<ll> f(n);
    rep(i,0,n) cin >> f[i];
    vector<ll> cuts(m);
    rep(i,0,m) {
        cin >> cuts[i];
    }
    vector<pll> invs;
    invs.PB({0,L-f[0]});
    rep(i,0,n-1) {
        pll bk = invs.back();
        if (i%2 == 0) {
            invs.PB({bk.S-(f[i]-f[i+1]), bk.S});
        } else {
            invs.PB({bk.F, bk.F+(f[i]-f[i+1])});
        }
    }
    ll totInvLen = 0;
    for (pll p : invs) totInvLen += p.S-p.F;
    if (n%2 == 0) {
        invs.PB({invs.back().F,invs.back().F+(L-totInvLen)});
    } else {
        invs.PB({invs.back().S-(L-totInvLen),invs.back().S});
    }
    dbg(invs);
    vector<pair<ll,bool>> pts;
    for (pll p : invs) {
        pts.PB({p.F,true});
        pts.PB({p.S,false});
    }
    sort(all(pts));
    int ind = 0;
    int op = 0;
    ll prev = pts[0].F;
    rep(i,0,m) {
        ll c = cuts[i];
        if (c <= pts[0].F) cout << "0 ";
        else {
            ll ans = op*(c-prev);
            while (ind < pts.size() && pts[ind].F <= c) {
                if (pts[ind].S) {
                    ++op;
                    ans += (c-pts[ind].F);
                } else {
                    --op;
                    ans -= (c-pts[ind].F);
                }
                ++ind;
            }
            cout << ans << " ";
            prev = c;
        }
    }
    if (cuts.back() >= pts.back().F) {
        cout << "0\n";
        return;
    }
    ll c = pts.back().F;
    ll ans = op*(c-prev);
    while (ind < pts.size() && pts[ind].F <= c) {
        if (pts[ind].S) {
            ++op;
            ans += (c-pts[ind].F);
        } else {
            --op;
            ans -= (c-pts[ind].F);
        }
        ++ind;
    }
    cout << ans << '\n';
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}