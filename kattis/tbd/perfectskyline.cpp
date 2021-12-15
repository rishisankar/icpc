#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; print(args...); }

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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

/*
dp[subset of blocks][first x buildings] = {prev mask, new blocks..}
00000 <- rightmost = 0th block, 1 = included in subset

dp[S][i]:
  for each subset of S:
    if ! sums up to building i: continue;
    if dp[complement][i-1]: update soln :)

empty = not processed;
-2 if no prev (first building)
-1 if no soln

return dp[111][n];
*/

vector<vector<vector<ll>>> dp;
int N, S;
vector<ll> blocks;
vector<ll> buildings;

void solve(int mask, int x) {
    //print("trying", mask, x);
    if (dp[mask][x].size() > 0) {
        // cout << "already processed, exiting early\n";
        return;
    }
    if (x == 0) {
        dp[mask][x].push_back(-2);
        return;
    }
    int Z = __builtin_popcountll(mask);
    int tt = 1 << Z;
    //print("t2", mask, x, tt, Z);
    for (int i = 0; i < tt; ++i) {
        dp[mask][x].clear();
        dp[mask][x].push_back(-1);
        ll sm = 0;
        int ct = 0;
        string nm = "";
        //if (x == 3)print("starting", i);
        for (int j = 0; j < N; ++j) {
            if ((mask >> j) & 1 == 1) {
                if ((i >> ct) & 1 == 1) {
                    // cout << "using block " << j << " " << blocks[j] << "\n";
                    sm += blocks[j];
                    nm += '0';
                    dp[mask][x].push_back(j);
                } else {
                    nm += '1';
                }
                ++ct;
            } else {
                nm += '0';
            }
        }
        //if (x == 3)print("sum", sm, buildings[x-1]);
        if (sm != buildings[x-1]) {
            continue;
        }
        reverse(all(nm));
        int nmask = stoi(nm, 0, 2);
        solve(nmask, x-1);
        if (dp[nmask][x-1][0] == -1) continue;
        dp[mask][x][0] = nmask;
        // cout << "found soln for " << mask << " " << x << '\n';
        // print(dp[mask][x][0], mask, x, nmask);
        return;
    }
    // print("t3", mask, x);
}

void run() {
    cin >> N >> S;
    blocks.resize(N);
    buildings.resize(S);
    INP(blocks, N);
    INP(buildings, S);
    reverse(all(buildings));
    dp.resize((1<<N), vector<vector<ll>>(S+1));
    //dp[0][0].push_back(-2);
    solve((1<<N)-1, S);

    // for (int i = 0; i < (1<<N); ++i) {
    //     for (int j = 0; j <= S; ++j) {
    //         cout << "(" << i << "," << j << "):";
    //         for (int x : dp[i][j]) cout << " " << x;
    //         cout << "\n";
    //     }
    // }

    int curmask = (1<<N)-1;
    if (dp[curmask][S][0] == -1) {
        print(-1);
        return;
    }
    for (int i = S; i > 0; --i) {
        cout << dp[curmask][i].size() -1;
        for (int j = 1; j < dp[curmask][i].size(); ++j) {
            cout << ' ' << dp[curmask][i][j]+1;
        }
        cout << '\n';
        curmask = dp[curmask][i][0];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}