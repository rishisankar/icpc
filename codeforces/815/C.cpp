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

vector<vector<pii>> L;

void run() {
    int n,m; cin >> n >> m;
    vector<vector<bool>> g(n,VB(m));
    int ct = 0;
    rep(i,0,n) {
        string s; cin >> s;
        rep(j,0,m) {
            g[i][j] = (s[j] == '1');
            if (g[i][j])++ct;
        }
    }
    if (ct == 0) {
        print(0);
        return;
    }
    // check min # u can remove in first move
    int bst = 3;
    rep(i,0,n) {
        rep(j,0,m) {
            if (!g[i][j]) continue;
            int amt = 4;
            for (VPII v : L) {
                bool val = true;
                int cz = 0;
                for (pii d : v) {
                    int nx = i+d.F; int ny = j+d.S;
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
                        val = false; break;
                    }
                    if (g[nx][ny])++cz;
                }
                if (!val) continue;
                amt = min(amt,cz);
            }
            dbg(i,j,amt);
            bst = min(bst,amt);
        }
    }
    dbg(bst);
    print(ct - bst + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);

    vector<pii> L1{{1,0},{1,1},{0,0}};
    vector<pii> L2{{1,0},{1,-1},{0,0}};
    vector<pii> L3{{-1,0},{-1,1},{0,0}};
    vector<pii> L4{{-1,0},{-1,-1},{0,0}};
    vector<pii> L5{{0,1},{1,1},{0,0}};
    vector<pii> L6{{0,1},{-1,1},{0,0}};
    vector<pii> L7{{0,-1},{1,-1},{0,0}};
    vector<pii> L8{{0,-1},{-1,-1},{0,0}};
    vector<pii> V1{{0,1},{1,0},{0,0}};
    vector<pii> V2{{0,1},{-1,0},{0,0}};
    vector<pii> V3{{0,-1},{1,0},{0,0}};
    vector<pii> V4{{0,-1},{-1,0},{0,0}};

    L = {L1,L2,L3,L4,L5,L6,L7,L8,V1,V2,V3,V4};

    ll t; cin >> t;
    rep(tests,0,t) run();
}