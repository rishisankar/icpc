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
at least one of n,m must be divisible by 3 (assume n wlog)
possible small fillings: 2x3, 5x9

(1) m=1: impossible
(2) m even: doable (use many 2x3s)
(3) m odd, n even: fill first three cols with 2x3s repeatedly, remaining cols reduce to (2)
(4) m odd, n odd, n >= 9, m >= 5: 9x5, 9x(m-5) by case (2), (n-9)xm by case (3)
(5) n = 3, m odd: impossible (think abt where to place top left corner tromino)

GGIIFGGII
GMMIFFGIN
QQMTTQQNN
QVXTUQWXX
VVXXUUWWX
*/

VVI sol;
int cur = 0;

void printSol(VVI& ans) {
    int n = sz(ans), m = sz(ans[0]);
    int k = n*m/3;
    VVI adj(k);
    rep(i,0,n) {
        rep(j,0,m) {
            for (pii d : dirs) {
                int nx = i+d.F; int ny = j+d.S;
                if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                    if (ans[nx][ny] != ans[i][j]) {
                        adj[ans[nx][ny]].pb(ans[i][j]);
                        adj[ans[i][j]].pb(ans[nx][ny]);
                    }
                }
            }
        }
    }
    vector<int> colors(k,-1);
    rep(i,0,k) {
        unordered_set<int> neighbor_colors;
        for (int x : adj[i]) {
            if (colors[x]!=-1) neighbor_colors.insert(colors[x]);
        }
        rep(j,0,26) {
            if (!neighbor_colors.count(j)) {
                colors[i] = j;
                break;
            }
        }
    }
    vector<vector<char>> newSol(n, vector<char>(m));
    rep(i,0,n) {
        rep(j,0,m) {
            newSol[i][j] = ('A' + colors[ans[i][j]]);
        }
    }
    rep(i,0,n) {
        rep(j,0,m) {
            cout << newSol[i][j];
        }
        cout << '\n';
    }
}

void solve95(int xi, int yi) {
    VS v{"GGAAFBBII", 
         "GMMAFFBIN", 
         "CCMTTQQNN", 
         "CVDTUQWXX", 
         "VVDDUUWWX"};
    VVI ans(9,VI(5));
    map<char,int> mz;
    rep(i,0,9) {
        rep(j,0,5) {
            char c = v[j][i];
            if (!mz.count(c)) mz[c] = sz(mz);
            ans[i][j] = mz[c];
        }
    }
    rep(i,0,9) {
        rep(j,0,5) {
            sol[xi+i][yi+j] = cur + ans[i][j];
        }
    }
    cur += sz(mz);
}

// solve region starting at (xi,yi) of size nxm (assume case 2)
void solve2(int xi, int yi, int n, int m) {
    rep(i,0,m/2) {
        rep(j,0,n/3) {
            // x,y of cur 3x2
            int nx = xi + 3*j;
            int ny = yi + 2*i;
            sol[nx][ny] = sol[nx+1][ny] = sol[nx][ny+1] = cur++;
            sol[nx+2][ny] = sol[nx+1][ny+1] = sol[nx+2][ny+1] = cur++;
        }
    }
}

// solve region starting at (xi,yi) of size nxm (assume case 3)
void solve3(int xi, int yi, int n, int m) {
    rep(i,0,n/2) {
        int nx = xi + 2*i;
        sol[nx][yi] = sol[nx][yi+1] = sol[nx+1][yi] = cur++;
        sol[nx+1][yi+1] = sol[nx+1][yi+2] = sol[nx][yi+2] = cur++;
    }
    solve2(xi, yi+3, n, m-3);
}

void run() {
    int n,m; cin >> n >> m;
    bool tp = false;
    if (n%3 != 0) {
        swap(n,m);
        tp = true;
    }
    if (n%3 != 0 || m == 1 || (n == 3 && (m&1))) {
        // base + (1) + (5)
        print("NO");
        return;
    }
    cur = 0;
    sol.assign(n, VI(m,-1));
    if (m%2 == 0) solve2(0,0,n,m);
    else if (n%2 == 0) solve3(0,0,n,m);
    else {
        if (m < 5) {
            print("NO");
            return;
        }
        solve95(0,0);
        solve2(0,5,9,m-5);
        solve3(9,0,n-9,m);
    }
    VVI ans;
    if (tp) {
        ans.resize(m, VI(n));
        rep(i,0,n) {
            rep(j,0,m) {
                ans[j][i] = sol[i][j];
            }
        }
    } else ans = sol;
    print("YES");
    printSol(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}