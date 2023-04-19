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

inline int geti(int x) {
    return 2*(x+180);
}

void run() {
    int n; cin >> n;
    VB lgt(721, false);
    VPII v(n);
    rep(i,0,n) cin >> v[i].F >> v[i].S;
    rep(i,0,n) {
        int a = v[i].S, b = v[(i+1)%n].S;
        if (a>b) swap(a,b);
        int d1 = b-a, d2 = 360+a-b;
        int i1 = geti(a), i2 = geti(b);
        if (d1 > d2) {
            // fill everything from b-a (wrap around)
            rep(j,0,i1+1) lgt[j] = true;
            rep(j,i2,720) lgt[j] = true;
        } else if (d1 < d2) {
            rep(j,i1,i2+1) lgt[j] = true;
        } else {
            print("yes");
            return;
        }
    }
    rep(i,0,720) {
        if (!lgt[i]) {
            int val = -180 + i/2;
            cout << "no ";
            if (val < 0) {
                cout << "-";
                val=abs(val);
                if (i&1)--val;
            }
            cout << val;
            if (i&1) {
                cout << ".5";
            } else cout << ".0";
            cout << "\n";
            return;
        }
    }
    print("yes");
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