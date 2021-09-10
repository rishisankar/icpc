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
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

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

void run() {
    int ww, wb, bw, bb, L;
    cin >> ww >> wb >> bw >> bb >> L;
    int wwt[5][5][12];
    int wbt[5][5][12];
    int bwt[5][5][12];
    int bbt[5][5][12];
    fill(&wwt[0][0][0], &wwt[0][0][0] + 300, -1);
    fill(&wbt[0][0][0], &wbt[0][0][0] + 300, -1);
    fill(&bwt[0][0][0], &bwt[0][0][0] + 300, -1);
    fill(&bbt[0][0][0], &bbt[0][0][0] + 300, -1);
    REP(i, ww) {
        int fl, fu; cin >> fl >> fu; --fl; --fu;
        REP(j, 12) { int x; cin >> x;
            wwt[fl][fu][j] = x;
        }
    }
    REP(i, wb) {
        int fl, fu; cin >> fl >> fu; --fl; --fu;
        REP(j, 12) { int x; cin >> x;
            wbt[fl][fu][j] = x;
        }
    }
    REP(i, bw) {
        int fl, fu; cin >> fl >> fu; --fl; --fu;
        REP(j, 12) { int x; cin >> x;
            bwt[fl][fu][j] = x;
        }
    }
    REP(i, bb) {
        int fl, fu; cin >> fl >> fu; --fl; --fu;
        REP(j, 12) { int x; cin >> x;
            bbt[fl][fu][j] = x;
        }
    }

    VI keys(L);
    REP(i, L) { cin >> keys[i]; }


    VVI dp(L+1, VI(5, INT_MAX));
    REP(i,5) {
        dp[0][i] = 0;
        dp[1][i] = 0;
    }

    unordered_set<int> blacks;
    blacks.insert(2);
    for (int i = 5; i <= 88;) {
        blacks.insert(i);
        i+=2; if (i>88) break;
        blacks.insert(i);
        i+=3; if (i>88) break;
        blacks.insert(i);
        i+=2; if (i>88) break;
        blacks.insert(i);
        i+=2; if (i>88) break;
        blacks.insert(i);
        i+=3; if (i>88) break;
    }
    vector<int> blv;
    for (int i : blacks) {
        blv.push_back(i);
    }
    sort(all(blv));
    for (int i : blv) {
        cerr << i << " ";
    }
    cerr << '\n';

    for (int i = 2; i <= L; ++i) {
        bool pb = (blacks.count(keys[i-2]) == 1);
        bool nb = (blacks.count(keys[i-1]) == 1);
        bool rev = false;
        if (keys[i-2] > keys[i-1]) {
            swap(pb, nb);
            rev = true;
        }
        int steps = abs(keys[i-2] - keys[i-1]) - 1;
        dbg(i, pb, nb, steps);
        if (steps == -1) {
            REP(j, 5) {
                dp[i][j] = dp[i-1][j];
            }
        } else {
            REP(j, 5) { // new finger
                REP(k, 5) { // old finger
                    if (dp[i-1][k] == INT_MAX) continue;
                    int cost = 0;
                    int cj = j;
                    int ck = k;
                    if (rev) swap(cj, ck);
                    if (pb && nb) cost = bbt[ck][cj][steps];
                    else if (pb && !nb) cost = bwt[ck][cj][steps];
                    else if (!pb && nb) cost = wbt[ck][cj][steps];
                    else  cost = wwt[ck][cj][steps];
                    if (cost == -1) continue;
                    dp[i][j] = min(dp[i][j], dp[i-1][k] + cost);
                }
            }
        }
    }

    int bst = INT_MAX;
    REP(i, 5) {
        bst = min(bst, dp[L][i]);
    }

    printVV(dp);

    print(bst);

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