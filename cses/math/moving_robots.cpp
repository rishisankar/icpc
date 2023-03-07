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

inline void simulate(vector<vector<ld>>& state) {
    vector<vector<ld>> ns(8,vector<ld>(8,0)); 
    rep(i,0,8) {
        rep(j,0,8) {
            int n_st = 0;
            for (pii p : dirs) {
                int ni = i+p.F; int nj = j+p.S;
                if (ni < 0 || nj < 0 || ni >= 8 || nj >= 8) continue;
                ++n_st;
            }
            for (pii p : dirs) {
                int ni = i+p.F; int nj = j+p.S;
                if (ni < 0 || nj < 0 || ni >= 8 || nj >= 8) continue;
                ns[ni][nj] += state[i][j]/n_st;
            }
        }
    }
    state = ns;
}

void run() {
    int k; cin >> k;
    vector<vector<ld>> p_empty(8, vector<ld>(8,1)); // p_empty = P(r1 not there) * ...
    rep(i,0,8) {
        rep(j,0,8) {
            // simulate for robot starting at (i,j)
            vector<vector<ld>> rob(8, vector<ld>(8,0));
            rob[i][j] = 1;
            rep(l,0,k) simulate(rob);
            // if (i==0 && j == 0) {
            //     dbg(rob);
            // }
            rep(a,0,8) {
                rep(b,0,8) {
                    p_empty[a][b] *= (1-rob[a][b]);
                }
            }
        }
    }
    ld sm = 0;
    rep(i,0,8) {
        rep(j,0,8) {
            sm += p_empty[i][j];
        }
    }

    ll pv = sm;
    cout << pv << ".";
    sm-=pv;
    ll a2 = round(sm*1000000);
    string s = to_string(a2);
    rep(i,0,6-s.size()) cout << "0";
    cout << s << '\n';

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