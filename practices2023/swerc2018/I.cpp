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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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

template<typename T> inline T ceildiv(T a, T b) {return (a+b-1)/b;}

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

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1),mp(-1,-1), mp(-1,1), mp(1,-1), mp(1,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

bool isA(vector<string> &comp) {
    int m = sz(comp), n = sz(comp[0]);
    int x = 2*n - m;
    int y = n - 2*x;
    if (x <= 0 || y <= 0) return false;
    vector<string> exp(m, string(n, '.'));
    rep(i,0,x) {
        rep(j,0,n) {
            exp[i][j] = '#';
            exp[i+x+y][j] = '#';
        }
    }
    rep(i,0,x) {
        rep(j,0,m) {
            exp[j][i] = exp[j][n-1-i] = '#';
        }
    }
    rep(i,0,m) {
        if (exp[i] != comp[i]) return false;
    }
    return true;
}

bool isB(vector<string> &comp) {
    int m = sz(comp), n = sz(comp[0]);
    int x = 2*n - m;
    int y = n - 2*x;
    if (x <= 0 || y <= 0) return false;
    vector<string> exp(m, string(n, '.'));
    rep(i,0,x) {
        rep(j,0,n) {
            exp[i][j] = '#';
            exp[i+x+y][j] = '#';
            exp[i+x+y+x+y][j] = '#';
        }
    }
    rep(i,0,x) {
        rep(j,0,m) {
            exp[j][i] = exp[j][n-1-i] = '#';
        }
    }
    rep(i,0,m) {
        if (exp[i] != comp[i]) return false;
    }
    return true;
}

bool isC(vector<string> &comp) {
    int m = sz(comp), n = sz(comp[0]);
    int x = 2*n - m;
    int y = n - 2*x;
    if (x <= 0 || y <= 0) return false;
    vector<string> exp(m, string(n, '.'));
    rep(i,0,x) {
        rep(j,0,n) {
            exp[i][j] = '#';
            exp[i+x+y+x+y][j] = '#';
        }
    }
    rep(i,0,x) {
        rep(j,0,m) {
            exp[j][i] = '#';
        }
    }
    rep(i,0,m) {
        if (exp[i] != comp[i]) return false;
    }
    return true;
}

vector<string> normalize_comp(vector<pii> &comp) {
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;
    for (auto p : comp) {
        minX = min(minX, p.F);
        maxX = max(maxX, p.F);
        minY = min(minY, p.S);
        maxY = max(maxY, p.S);
    }
    vector<string> ans(maxX - minX + 1, string(maxY - minY + 1, '.'));
    for (auto p : comp) {
        ans[p.F - minX][p.S - minY] = '#';
    }
    // dbg("COMP:");
    // for (auto s : ans) dbg(s);
    // dbg("END OF COMP");
    return ans;

}

void run() {
    int w,h; cin >> w >> h;
    vector<string> grid(h);
    rep(i,0,h) cin >> grid[i];
    vector<VB> vis(h, VB(w));
    vector<vector<pii>> comps;
    rep(i,0,h) {
        rep(j,0,w) {
            if (vis[i][j]) continue;
            if (grid[i][j] != '#') continue;
            vector<pii> comp;
            bool is_border = false;
            stack<pii> s;
            s.push({i,j});
            vis[i][j] = true;
            while (!s.empty()) {
                pii t = s.top(); s.pop();
                comp.pb(t);
                if (t.F == 0 || t.S == 0 || t.F == h-1 || t.S == w-1) is_border = true;
                for (auto dir : dirs) {
                    int nx = t.F + dir.F, ny = t.S + dir.S;
                    if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
                    if (grid[nx][ny] != '#') continue;
                    if (vis[nx][ny]) continue;
                    s.push({nx,ny});
                    vis[nx][ny] = true;
                }
            }
            if (!is_border && sz(comp) > 1)
            comps.pb(comp);
        }
    }

    int A = 0, B = 0, C = 0;
    for (auto &c : comps) {
        vector<string> nc = normalize_comp(c);
        if (isA(nc))++A;
        if (isB(nc))++B;
        if (isC(nc))++C;
    }
    print(A,B,C);
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