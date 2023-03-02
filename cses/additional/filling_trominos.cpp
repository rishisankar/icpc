// fails!

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

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

const pii fail = {-1,-1};
const pii unsolved = {-2,-2};
const pii nopar = {-3,-3};
// stores parent dp state
vector<vector<pii>> dp(105, vector<pii>(105, unsolved));
vector<pii> dirs;
void printSol(int n, int m, VVI& sol) {
    int k = n*m/3;
    VVI adj(k);
    rep(i,0,n) {
        rep(j,0,m) {
            for (pii d : dirs) {
                int nx = i+d.F; int ny = j+d.S;
                if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                    if (sol[nx][ny] != sol[i][j]) {
                        adj[sol[nx][ny]].pb(sol[i][j]);
                        adj[sol[i][j]].pb(sol[nx][ny]);
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
            newSol[i][j] = ('A' + colors[sol[i][j]]);
        }
    }
    rep(i,0,n) {
        rep(j,0,m) {
            cout << newSol[i][j];
        }
        cout << '\n';
    }

}

void makeSol(int n, int m, VVI& sol, int val) {
    if (dp[n][m] == nopar) {
        // 2x3 or 3x2 case
        if (n == 2 && m == 3) {
            sol[0][0] = sol[1][0] = sol[1][1] = val;
            sol[0][1] = sol[0][2] = sol[1][2] = val+1;
        } else {
            sol[0][0] = sol[1][0] = sol[0][1] = val;
            sol[2][0] = sol[2][1] = sol[1][1] = val+1;
        }
        return;
    }
    if (dp[n][m] == mp(n-2,m)) {
        int rects = m/3;
        rep(i,0,rects) {
            sol[n-1][i*3] = sol[n-1][i*3+1] = sol[n-2][i*3] = val;
            sol[n-1][i*3+2] = sol[n-2][i*3+1] = sol[n-2][i*3+2] = val+1;
            val+=2;
        }
    } else if (dp[n][m] == mp(n-3,m)) {
        int rects = m/2;
        rep(i,0,rects) {
            sol[n-1][i*2] = sol[n-1][i*2+1] = sol[n-2][i*2] = val;
            sol[n-2][i*2+1] = sol[n-3][i*2] = sol[n-3][i*2+1] = val+1;
            val+=2;
        }
    } else if (dp[n][m] == mp(n,m-3)) {
        int rects = n/2;
        rep(i,0,rects) {
            sol[i*2][m-1] = sol[i*2+1][m-1] = sol[i*2][m-2] = val;
            sol[i*2+1][m-2] = sol[i*2][m-3] = sol[i*2+1][m-3] = val+1;
            val+=2;
        }
    } else { // n, m-2
        int rects = n/3;
        rep(i,0,rects) {
            sol[i*3][m-1] = sol[i*3+1][m-1] = sol[i*3][m-2] = val;
            sol[i*3+2][m-1] = sol[i*3+1][m-2] = sol[i*3+2][m-2] = val+1;
            val+=2;
        }
    }
    makeSol(dp[n][m].F, dp[n][m].S, sol, val);
}

bool solve(int n, int m) {
    if (dp[n][m] != unsolved) return dp[n][m] != fail;
    if (n > 2 && m%3==0 && solve(n-2,m)) {
        dp[n][m] = {n-2,m};
        return true;
    }
    if (n > 3 && m%2==0 && solve(n-3,m)) {
        dp[n][m] = {n-3,m};
        return true;
    }
    if (m > 3 && n%2==0 && solve(n,m-3)) {
        dp[n][m] = {n,m-3};
        return true;
    }
    if (m > 2 && n%3==0 && solve(n,m-2)) {
        dp[n][m] = {n,m-2};
        return true;
    }
    dp[n][m] = fail;
    return false;
}

void run() {
    dp[2][3] = dp[3][2] = nopar;
    int t; cin >> t;
    rep(i,0,t) {
        int n,m;
        cin >> n >> m;
        dbg(n,m);
        if (solve(n,m)) {
            print("YES");
            // VVI v(n, VI(m,0));
            // makeSol(n,m,v,0);
            // printSol(n,m,v);
        } else print("NO");
        cout.flush();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    dirs.pb({-1,0});
    dirs.pb({1,0});
    dirs.pb({0,-1});
    dirs.pb({0,1});
    ll t=1;
    rep(tests,0,t) run();
}