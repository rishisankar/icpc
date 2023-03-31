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
return interval of height reached for 1st time on day n
*/
pll inv(ll a, ll b, ll n) {
    if (n==1) return {0,a};
    else return {(n-1)*a - (n-2)*b+1, n*a - (n-1)*b};
}

void run() {
    int q; cin >> q;
    pll poss = {1, LLONG_MAX};
    // ll L = 1; ll R = LLONG_MAX; // interval for possible height of tree (incl)
    rep(Q,0,q) {
        int ty; cin >> ty;
        if (ty == 1) {
            ll a,b,n; cin >> a >> b >> n;
            pll rng = inv(a,b,n);
            if (rng.S < poss.F || poss.S < rng.F) {
                cout << "0 ";
            } else {
                cout << "1 ";
                // intersect
                poss.F = max(poss.F, rng.F);
                poss.S = min(poss.S, rng.S);
            }
        } else {
            ll a,b; cin >> a >> b;
            ll lo = 1, hi = poss.S / (a-b) + 4;
            ll bst = -1;
            while (lo <= hi) {
                ll md = (lo + hi) / 2;
                pll rng = inv(a,b,md);
                if (poss.S < rng.F) {
                    hi = md - 1;
                } else if (rng.S < poss.F) {
                    lo = md + 1;
                } else {
                    hi = md - 1;
                    bst = md;
                }
            }
            if (bst != -1) {
                pll rng = inv(a,b,bst+1);
                if (rng.S < poss.F || poss.S < rng.F) {
                    cout << bst << ' ';
                } else {
                    cout << "-1 ";
                }
            } else {
                cout << "-1 ";
            }
        }
    }
    cout << '\n';
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