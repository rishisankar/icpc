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

int n;

// ans[a][b] = time they arrive at b, assuming start at a
VVLL gam(VLL& tran, VLL& d) {
    VVLL ans(n, VLL(n));
    for (int l = 1; l < n; ++l) {
        rep(s, 0, n) {
            ans[s][(s+l)%n] = ans[s][(s+l-1)%n] + tran[(s+l-1)%n] + d[(s+l-1)%n];
        }
    }
    return ans;
}

bool overlap(int a, int b, VVLL& adj, VVLL& bdj) {
    return false;
}

void run() {
    cin >> n;
    VLL d(n); INP(d,n);
    VLL tt(n),at(n),it(n);
    INP(tt,n); INP(at,n); INP(it,n);
    VVLL tadj = gam(tt,d), aadj = gam(at,d), iadj = gam(it,d);
    rep(t,0,n) {
        rep(a,0,n) {
            rep(i,0,n) {
                if (t == a || t == i || a == i) continue;
                if (overlap(t,a,tadj,aadj)) continue;
                if (overlap(t,i,tadj,iadj)) continue;
                if (overlap(a,i,aadj,iadj)) continue;
                print(t+1,a+1,i+1);
                return;
            }
        }
    }
    print("impossible");
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