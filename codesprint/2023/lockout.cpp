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
1. mario can win all but the first world
2. mario can have 50% chance of winning first world, then win all but second


what is the first world mario loses for sure? 
1. none: then each world is 50/50
2. kth: then mario wins rest, prev is 50/50

consider world 1.

if coins[1] > coins[rest]:
    p(win) = 0.5

if coins[1] = coins[rest]:
    must tie first.
    50% chance of win
        - must win at least one of the remaining
            - if more than two things, guaranteed
            - if exactly two things, 50/50 tie vs win
    50% chance of lose
        - then impossible to beat luigi

if coins[1] < coins[rest]:
    give up first, win rest. p(win) = 1

strategy 1: p=0 or 1
strategy 2: 
*/

void run() {
    int n; cin >> n;
    VLL a(n), t(n), p(n);
    INP(a,n); INP(t,n); INP(p,n);
    ll sm = 0; rep(i,0,n) if (i!=p[0]-1) sm += a[i];
    if (sm>a[p[0]-1]) {
        print(1);
        rep(i,1,n) cout << p[i] << ' ';
        print(p[0]);
    } else if (sm<a[p[0]-1]) {
        print(0.5);
        rep(i,0,n) cout << p[i] << ' ';
        cout << '\n';
    } else if (sm==a[p[0]-1] && n==2) {
        print(0.25);
        rep(i,0,n) cout << p[i] << ' ';
        cout << '\n';
    } else {
        print(0.5);
        cout << p[0];
        rep(i,2,n) cout << ' ' << p[i];
        cout << ' ' << p[1] << '\n';
    }
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