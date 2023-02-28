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

/* cost of killing everything to the left */
VLL cost(VLL& v) {
    int n = v.size();
    VLL dp(n); // dp[i] represents cost of exploding i and clearing everything to the left
    VLL pf(n,0);
    pf[0] = v[0]; rep(i,1,n) pf[i] = pf[i-1]+v[i];
    VLL pf2(n+5,0); rep(i,1,n+5) pf2[i] = pf2[i-1]+i;
    stack<int> s;
    vector<int> prev(n,-1);
    VLL vp(n);
    rep(i,0,n) vp[i] = v[i]-i;
    rep(i,0,n) {
        while (!s.empty() && vp[s.top()] >= vp[i]) s.pop();
        if (!s.empty()) prev[i] = s.top();
        s.push(i);
    }
    dbg(prev);
    rep(i,0,n) {
        if (i == 0) { dp[i] = 0; continue; }
        if (v[i] == 0) { dp[i] = pf[i-1]; continue; }
        if (prev[i] == -1) {
            ll numClear = min((ll)i, v[i]-1);
            dbg("c1",i,numClear);
            dp[i] = pf[i-1] - numClear*v[i] + (numClear)*(numClear+1)/2;
        } else {
            int j = prev[i];
            dp[i] = pf[i-1] - pf[j] - (i-j-1)*(v[i]-i) - (pf2[i-1]-pf2[j]) + dp[j];
            dbg("c2",i,j,dp[i]);
        }
    }
    return dp;
}

void run() {
    int n; cin >> n; VLL v(n); INP(v,n);
    VLL dl = cost(v);
    reverse(all(v));
    VLL dr = cost(v);
    reverse(all(dr));
    dbg(dl);
    dbg(dr);
    reverse(all(v));
    dbg(v);
    ll best = LLONG_MAX;
    rep(i,0,n) {
        best = min(best, v[i] + dl[i] + dr[i]);
    }
    print(best);
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