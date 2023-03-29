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

Patterns (WLOG assume that we are going from top left to bottom right. also assume n<=m)

N=1: possible only for x1 = 1, x2 = M
N=2:
    2x2: possible unless diagonal (1,1)->(2,2)
    2x3: start at (1,1): possible unless even MD away
         start at (1,2): only possible to corner on same side
    2x4: start at (1,1): possible unless even MD away

...


General approach:
- in at least one dimension, the two points have different values.
- fill up to the smaller dimension to reduce the square size
- recurse (can use dp maybe, but many states)

Can BF solve after a certain point: maybe 10x50?


To store states for DP:
- note that after first iter, at least one point is on an edge!
==> 50^5 ~ 300 million, maybe possible
- after second iter, both points are on edge
==> 50^4 ~ 6 million, def possible

==> algorithm:
    - solve for all 50^4 states where both points are on the edge
        - note cases: points are on same edge, opposite edge, adjacent edge
    - for each testcase:
        - for each cut location: (how to fill initial rectangle for both start/end, skip if alr on edge):
            check if state solvable, if so done
        if fail, print no

*/

VVB vis;
int ct;
int N,M;
pii S,E;

bool chk(int d, int x, int y);

inline bool is_dead_end(int x, int y) {
    int nv = 0;
    rep(i,0,4) {
        int nx = x+dirs[i].F, ny = y+dirs[i].S;
        if (vis[nx][ny])++nv;
    }
    return nv>=3;
}

// find path. d = current path iter, (x,y) = current.
inline bool chk_(int& d, int& x, int& y) {  
    if (d == N*M-1) {
        if (mp(x,y) == E) return 1;
        else return 0;
    } else if (mp(x,y) == E) {
        return 0;
    }
    int dir = -1;
    // check if any dirs are dead ends
    rep(i,0,4) {
        int nx = x+dirs[i].F, ny = y+dirs[i].S;
        if (vis[nx][ny]) continue;
        if (mp(nx,ny) == E) continue; // dest can be dead end
        if (is_dead_end(nx,ny)) {
            if (dir != -1) return 0; // multiple dead ends
            else dir = i;
        }
    }
    // if no dead end, can go in any dir
    int rlb = (dir == -1 ? 0 : dir);
    int rub = (dir == -1 ? 4 : dir+1);
    rep(i,rlb,rub) {
        // try each valid direction
        auto dir = dirs[i];
        int nx = x+dir.F, ny = y+dir.S;
        if (vis[nx][ny]) continue;
        int nnx = nx+dir.F, nny = ny+dir.S;
        /*
        // this optimization only works if starting at edge of grid?
        if (vis[nnx][nny]) {
            int vc = 0;
            int lb = (i < 2 ? 2 : 0);
            int ub = (i < 2 ? 4 : 2);
            rep(j,lb,ub) {
                int xp = nx+dirs[j].F, yp = ny+dirs[j].S;
                if (!vis[xp][yp]) ++vc;
            }
            if (vc == 2) continue;
        }
        */
        if (chk(d+1,nx,ny)) return 1;
    }
    return 0;
}

bool chk(int d, int x, int y) {
    vis[x][y] = true;
    bool ans = chk_(d,x,y);
    vis[x][y] = false;
    return ans;
}

bool test(int n, int m, int y1, int x1, int y2, int x2) {
    ct = 0; N = n; M = m; S = {y1,x1}; E = {y2,x2};
    vis.assign(n+2, VB(m+2,0));
    rep(i,0,n+2) vis[i][0] = vis[i][m+1] = 1;
    rep(i,0,m+2) vis[0][i] = vis[n+1][i] = 1;
    bool valid = chk(0, y1, x1);
    return valid;
}

void run() {
    int MAX_D; cin >> MAX_D;
    for (int n = 1; n <= MAX_D; ++n) {
        for (int m = n; m <= MAX_D; ++m) {
            print("(N,M)",n,m);
            for (int y1 = 1; y1 <= n; ++y1) {
                for (int x1 = 1; x1 <= m; ++x1) {
                    for (int y2 = y1; y2 <= n; ++y2) {
                        for (int x2 = x1; x2 <= m; ++x2) {
                            if (x1==x2 && y1==y2) continue;
                            bool val = test(n,m,y1,x1,y2,x2);
                            dbg(n,m,y1,x1,y2,x2,val);
                        }
                    }
                }
            }
            cout << endl;
        }
    }
    // int t; cin >> t;
    // rep(T,0,t) {
    //     int n,m,y1,x1,y2,x2; cin >> n >> m >> y1 >> x1 >> y2 >> x2;
    //     print(test(n,m,y1,x1,y2,x2));
    // }
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
