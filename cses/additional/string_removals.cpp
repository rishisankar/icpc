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

aba: "", a,b,ab,ba,aa,aba
dp[0] = 1
dp[1] = 2
dp[2] = 4
dp[3] = 8 - dp("") = 7


https://www.geeksforgeeks.org/count-distinct-subsequences/

dp[i] = # of distinct subsequences of first i chars

dp[i] = 2*dp[i-1] - dp({prev occurrence of v[i]} - 1)

- for each subsequence of first i-1 chars, can either include or not include v[i] ==> 2*dp[i-1]
- each thing in dp({prev occurrence of v[i]} - 1) yielded a new subsequence by including v[i] (in prev occ)
    these are exactly the repeated terms when we add v[i] now instead

*/

void run() {
    string s; cin >> s;
    int n = sz(s);
    VLL dp(n+1);
    dp[0] = 1;
    vi last(26, -1);
    rep(i,0,n) {
        dp[i+1] = 2*dp[i];
        if (last[s[i]-'a'] != -1) dp[i+1] -= dp[last[s[i]-'a']];
        last[s[i]-'a'] = i;
        dp[i+1] = (dp[i+1]+mod)%mod;
    }
    print((dp[n]+mod-1)%mod); // subtract 1 to ignore empty string
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