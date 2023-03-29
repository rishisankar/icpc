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

int path[48];
bool vis[9][9] = {};

int ct = 0;
int chk(int d, int x, int y);

inline bool is_dead_end(int x, int y) {
    int nv = 0;
    rep(i,0,4) {
        int nx = x+dirs[i].F, ny = y+dirs[i].S;
        if (vis[nx][ny])++nv;
    }
    return nv>=3;
}

// ct paths. d = current path iter, (x,y) = current.
inline int chk_(int& d, int& x, int& y) {  
    if (d == 48) {
        if (x == 7 && y == 1) return 1;
        else return 0;
    } else if (x == 7 && y == 1) {
        return 0;
    }
    if (path[d] < 4) {
        // path is already determined
        auto dir = dirs[path[d]];
        int nx = x+dir.F, ny = y+dir.S;
        if (vis[nx][ny]) return 0;
        return chk(d+1,nx,ny);
    }
    int ans = 0;
    int dir = -1;
    // check if any dirs are dead ends
    rep(i,0,4) {
        int nx = x+dirs[i].F, ny = y+dirs[i].S;
        if (vis[nx][ny]) continue;
        if (nx == 7 && ny == 1) continue; // dest can be dead end
        if (is_dead_end(nx,ny)) {
            if (dir != -1) return 0; // multiple dead ends
            else dir = i;
        }
    }
    int rlb = (dir == -1 ? 0 : dir);
    int rub = (dir == -1 ? 4 : dir+1);
    rep(i,rlb,rub) {
        // try each direction
        auto dir = dirs[i];
        int nx = x+dir.F, ny = y+dir.S;
        if (vis[nx][ny]) continue;
        int nnx = nx+dir.F, nny = ny+dir.S;
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
        ans += chk(d+1,nx,ny);
    }
    return ans;
}

int chk(int d, int x, int y) {
    vis[x][y] = true;
    int ans = chk_(d,x,y);
    vis[x][y] = false;
    return ans;
}

void run() {
    map<char,int> m{{'U',0},{'D',1},{'L',2},{'R',3},{'?',4}};
    string s; cin >> s;
    rep(i,0,48) path[i] = m[s[i]];
    rep(i,0,9) vis[i][0] = vis[0][i] = vis[i][8] = vis[8][i] = 1;
    int ans = chk(0, 1, 1);
    print(ans);
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