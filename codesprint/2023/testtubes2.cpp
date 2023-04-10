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

bool cp(vi& s1, vi& s2) {
    return sz(s1) > sz(s2) || (sz(s1)==sz(s2) && s1.front()<s2.front());
}

void run() {
    int n; cin >> n;
    string a,b; cin >> a >> b;
    vector<int> s1,s2,s3;
    s1.pb(-1);
    s2.pb(-2);
    s3.pb(-3);
    rep(i,0,sz(a)) {
        if (i != 0 && a[i] == a[i-1])continue;
        if (a[i] == '1') s1.pb(1); else s1.pb(2);
    }
    rep(i,0,sz(b)) {
        if (i != 0 && b[i] == b[i-1])continue;
        if (b[i] == '1') s2.pb(1); else s2.pb(2);
    }
    int ct = 0;
    while (s1.back() == s2.back()) {
        if (sz(s1) > sz(s2)) swap(s1,s2);
        s2.pop_back();
        ++ct;
    }
    if (sz(s1) == 2 && sz(s2) == 2) {
        print(ct);
        return;
    }
    if (s1[1] == s2[1]) {
         print(ct + 2 + sz(s1)-2 + sz(s2)-2);
    } else {
        print(ct + 1 + sz(s1)-2 + sz(s2)-2);
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