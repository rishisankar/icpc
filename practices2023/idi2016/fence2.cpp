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

inline pll rf(pll p1) {
    ll g = __gcd(p1.F,p1.S);
    p1.F/=g; p1.S/=g;
    return p1;
}

const int N = 10000;
void run() {
    int k,n; cin >> k >> n;
    VLL v(k); INP(v,k); 
    // VLL v;
    // rep(i,0,k) {
    //     v.pb((rand()%N)+1);
    // }
    // dbg(v);

    ll sm = 0;
    rep(i,0,k) sm += v[i];
    vector<pll> items;
    unordered_set<ll> s; for (ll l : v) s.insert(l);
    dbg(sm);
    set<pll> fracs;
    for (ll p : s) {
        for (ll q = 1; q <= N; ++q) {
            if (p*2*n < sm*q) continue;
            if (p*n > sm*q) continue;
            fracs.insert(rf({p,q}));
        }
    }
    for (pll p : fracs) items.pb(p);
    dbg(items.size());
    sort(all(items), [&](pll& p1, pll& p2) {
        return p1.F*p2.S < p2.F*p1.S;
    });
    dbg(items);

    int bst = INT_MAX;
    int lo = 0;
    int hi = items.size()-1;
    while (lo <= hi) {
        int mid = (lo+hi)/2;
        int p = items[mid].F;
        int q = items[mid].S;
        dbg("test",p,q);
        int pcs = 0;
        int c = 0;
        int lw = 0;
        for (ll x : v) {
            if (x*q >= p) {
                dbg("pass", p,q,x);
                ll ct = x*q/p;
                pcs += x*q/p;
                if ((x*q)%p == 0) {
                    c += ct-1;
                    lw++;
                } else {
                    c += ct;
                }
            }
        }
        dbg(pcs,c);
        if (pcs-lw <= n && n <= pcs) {
            bst = c;
            lo = mid+1;
        } else if (pcs > n) {
            lo = mid+1;
        } else {
            hi = mid-1;
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