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

ll solve(int n, int m, VI& marks, unordered_map<int,int>& ms, int bits, VLL& dp) {
    if (dp[bits] != -1) {
        return dp[bits];
    }

    ll best = LLONG_MAX;

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            int r;
            if (j != n) {
                r = marks[j] - marks[i];
            } else {
                r = 2*m;
            }
            if (marks[i] - r >= 0) continue;
            unordered_set<int> kill;
            kill.insert(i);
            bool failed = false;
            for (int k = marks[i]+r; k < m; k+=r) {
                if (ms.count(k)) {
                    kill.insert(ms[k]);
                } else {
                    failed = true;
                    break;
                }
            }
            if (failed) continue;


            int newbits = bits;
            for (int i = 0; i < n; ++i) {
                if (kill.count(i) && (((bits >> i) & 1) == 0)) {
                    int mask = 1 << i;
                    newbits = newbits ^ mask;
                }
            }
            if (newbits != bits) {
                best = min(best, 1 + solve(n,m,marks,ms,newbits,dp));
            }
        }
    }

    return dp[bits] = best;

}

void run(int m) {
    int n ; cin >> n;

    VI marks(n);
    INP(marks, n);
    sort(all(marks));
    unordered_map<int, int> ms;
    for (int i = 0; i < n; ++i) {
        ms[marks[i]] = i;
    }
    // 0 = usable, 1 = not usable; rightmost bit = mark 0
    VLL dp((1 << n), -1);
    dp[(1<<n) - 1] = 0;

    ll x = solve(n,m,marks,ms,0, dp);
    print(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    int m;
    while (cin >> m) {
        run(m);
    }
}