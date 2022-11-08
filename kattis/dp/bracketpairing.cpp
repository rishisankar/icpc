#include <bits/stdc++.h>
using namespace std;

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
#define F first
#define S second
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

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;

string s;
int n;
vector<VVLL> dp;

ll solve(int l, int r, bool sgl) {
    if (l > r) return 1;
    if (l == r) return 0;
    if (dp[l][r][sgl] != -1) return dp[l][r][sgl];
    if (!(s[l] == '?' || s[l] == '<' || s[l] == '[' || s[l] == '{' || s[l] == '(')) return dp[l][r][sgl] = 0;
    if (!(s[r] == '?' || s[r] == '>' || s[r] == ']' || s[r] == '}' || s[r] == ')')) return dp[l][r][sgl] = 0;
    if (l == r) return dp[l][r][sgl] = 0;
    if (sgl) {
        // must be surrounded by matching...
        if (s[l] == '<' && s[r] != '?' && s[r] != '>') return dp[l][r][sgl] = 0;
        if (s[l] == '{' && s[r] != '?' && s[r] != '}') return dp[l][r][sgl] = 0;
        if (s[l] == '(' && s[r] != '?' && s[r] != ')') return dp[l][r][sgl] = 0;
        if (s[l] == '[' && s[r] != '?' && s[r] != ']') return dp[l][r][sgl] = 0;
        // if both are ?, 4 choices
        if (s[l] == '?' && s[r] == '?') return dp[l][r][sgl] = 4 * solve(l+1, r-1, false);
        else return dp[l][r][sgl] = solve(l+1, r-1, false);
    } else {
        // iter index for end of first concat
        ll res = 0;
        for (int i = l+1; i <= r; ++i) {
            res += solve(l, i, true) * solve(i+1, r, false);
        }
        return dp[l][r][sgl] = res;
    }
}

void run() {
    cin >> s;
    n = s.size();
    dp.assign(n, VVLL(n, VLL(2, -1)));

    print(solve(0, n-1, false));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}