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
 
const ll mod = 1000000007;
vector<unsigned long long> fac;
vector<ll> invs;
VVLL chz;
/* Iterative Function to calculate (x^y)%p
in O(log y) */
unsigned long long power(unsigned long long x,
                                  int y, int p)
{
    unsigned long long res = 1; // Initialize result
 
    x = x % p; // Update x if it is more than or
    // equal to p
 
    while (y > 0)
    {
     
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;
 
        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}
 
// Returns n^(-1) mod p
unsigned long long modInverse(unsigned long long n, 
                                            int p)
{
    return power(n, p - 2, p);
}
 
// Returns nCr % p using Fermat's little
// theorem.
unsigned long long nCrModPFermat(unsigned long long n,
                                 int r, int p)
{
    // If n<r, then nCr should return 0
    if (n < r)
        return 0;
    // Base case
    if (r == 0)
        return 1;
 
    return (fac[n] * invs[r] % p
            * invs[n - r] % p)
           % p; 
    // return (fac[n] * modInverse(fac[r], p) % p
    //         * modInverse(fac[n - r], p) % p)
    //        % p;
}
 
 
/*

dp[i][j] = ways of getting a sum of j using letters i..F

dp2[i][j] = ways of getting sum of j using only letter i

 --> j = 5, ct = 8

*/

/*
number of ways of getting sum of j using letter i
*/
ll solve(char letter, int ct, int sm) {
    if (letter == 'F') {
        if (sm != 0) return 0;
        return 1;
    }
    if (letter == '*') {
        if (sm > 0) return 0;
        if (sm < -ct) return 0;
        sm=-sm;
        return chz[ct][sm];
    }
    if (letter == 'A') {
        ll x = solve('*', ct, sm);
        ll rst = ct + sm;
        REP(i, rst) {
            x *= 2;
            x%=mod;
        }
        return x;
    } else {
        ll res = 0;
        for (int np = 0; np <= ct; ++np) {
            ll x = solve('*', ct-np, sm-np);
            x = (x * chz[ct][np]);
            res = (res+x)%mod;
        }
        return res;
    }
}

void run() {
    int n; cin >> n;
    unordered_map<char, int> cts;
    cts['A'] = cts['D'] = cts['F'] = 0;
    string s; cin >> s;
    REP(i,n) {
        if (s[i] == 'B' || s[i] == 'C') ++cts['D'];
        else ++cts[s[i]];
    }
    vector<char> chars = {'F','D','A'};
    // dp[i][j] = ways of getting a sum of j using letters i..F
    // dp2[i][j] = ways of getting a sum of j using letters i
    vector<vector<ll>> dp(3, VLL(10001));
    vector<vector<ll>> dp2(3, VLL(10001));

    for (int i = 0; i < 3; ++i) {
        for (int s = -n; s <= n; ++s) {
            dp2[i][5000+s] = solve(chars[i], cts[chars[i]], s);
        }
    }

    for (int s = -n; s <= n; ++s) {
        dp[0][5000+s] = 0;
    }
    dp[0][5000] = 1;
    
    for (int i = 1; i < 3; ++i) {
        for (int s = -n; s <= n; ++s) {
            dp[i][5000+s] = 0;
            for (int cs = -n; cs <= n; ++cs) {
                int psm = s - cs;
                if (psm > n | psm < -n) continue;
                dp[i][5000+s] += (dp2[i][5000+cs] * dp[i-1][5000+psm])%mod;
                dp[i][5000+s]%=mod;
            }
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        res = (res + dp[2][5000+i]) % mod;
    }
    print(res);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;

    fac.resize(10001);
    fac[0] = 1;
    for (int i = 1; i <= 10000; i++)
        fac[i] = (fac[i - 1] * i) % mod;
    


    invs.resize(5001);
    for (int i = 0; i <= 5000; ++i) {
        invs[i] = modInverse(fac[i], mod);
    }

    chz.resize(5001, VLL(5001));
    for (int i = 0; i <= 5000; ++i) {
        for (int j = 0; j <= 5000; ++j) {
            chz[i][j] = nCrModPFermat(i,j,mod);
        }
    }

    ll t=1;
    REP(tests,t) run();
}