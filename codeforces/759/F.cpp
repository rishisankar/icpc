#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
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
typedef pair<ll,ll> PLL;

const ll MOD = 998244353;

/*
a1...

dp[i] = dp[i-1]*ai - dp[i-2]*min(ai,ai-1) + dp[i-3]*min(ai,..,ai-2) - dp[i-4]*min(ai,...,ai-3)...

= sum_{j=0}^{i-1}  (-1)^(j)  dp[i-1-j]   min(ai, ..., a{i-j})

last term: -1^(i-1) dp[0] 

dp[0]*min(a1...ai) + ... + (-1)^l dp[i-1]*ai 
= sum_{j=0}^{i-1} (-1)^(j)  dp[j]   min(a{j+1}, ..., a{i})

compute dp[i]

dp[i] = -dp[i-1]

1 3 5 3 7 9 9 4

when find # larger than prev, push to back of stack with val dp[i-1]*ai
when find # <= prev, combine with last k from stack


stack: {minv, term sum for that min}


dp[0] = 1
dp[1] = dp[0]v[1] = 2
dp[2] = dp[0]min(v[1],v[2]) - dp[1]v[2] = -2
dp[3] = dp[0]min(v[1..3]) - dp[1]min(v[2..3]) + dp[2]v[3] = 2

*/

void run() {
    int n; cin >> n;
    VLL v(n+1), dp(n+1);
    OREP(i,n) cin >> v[i];
    dp[0] = 1;
    dp[1] = v[1];
    stack<PLL> stk;
    stk.push({v[1], 1});
    ll fct = -1;
    for (int i = 2; i <= n; ++i) {
        // dbg("iter",i,v[i]);
        ll nt = fct * dp[i-1];
        dp[i] = -fct*dp[i-1];
        nt%=MOD;dp[i]%=MOD;
        while (!stk.empty() && stk.top().first >= v[i]) {
            // dbg("stack", stk.top().first, stk.top().second, nt);
            PLL p = stk.top();
            stk.pop();
            dp[i] -= (p.first*p.second)%MOD;
            dp[i]%=MOD;
            nt += p.second;
            nt%=MOD;
        }
        stk.push({v[i], nt});
        dp[i] += nt*v[i];
        dp[i]%=MOD;
        dp[i] *= fct;
        dp[i]%=MOD;
        fct *= -1;
    }
    dp[n]%=MOD;
    dp[n]+=MOD;
    dp[n]%=MOD;
    // printV(dp);
    print(dp[n]);
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