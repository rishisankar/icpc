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

// range of possible sum of dists given n nodes
inline pll aran(ll n) {
    return {n-1, n*(n-1)/2};
}

const int MAXN = 1000000;

void run() {
    string s; cin >> s;
    string s1 = "", s2 = "";
    bool l = true;
    rep(i,0,sz(s)) {
        if (s[i] == '/') l^=1;
        else {
            if (l) s1+=s[i]; else s2+=s[i];
        }
    }
    ll a = stoll(s1), b = stoll(s2);
    ll lo = 1, hi = MAXN/b + 2;
    while (hi*b > MAXN)--hi;
    ll n = -1;
    while (lo <= hi) {
        ll mid = (lo+hi)/2;
        pll rn = aran(b*mid);
        ll ap = a*mid;
        if (rn.F <= ap && ap <= rn.S) {
            n = mid;
            hi = mid-1;
        } else if (ap < rn.F) {
            hi = mid-1;
        } else {
            lo = mid+1;
        }
    }
    if (n == -1) {
        print("impossible");
        return;
    }
    a *= n;
    n *= b;
    ll cur = n*(n-1)/2;
    print(n,n-1);
    for (int i = n; i >= 2; --i) {
        dbg(cur,a);
        if (cur == a) {
            print(i,i-1);
        } else if (cur-a > i-2) {
            cur -= (i-2);
            print(i,1);
        } else {
            print(i, i-1-(cur-a));
            cur = a;
        }
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