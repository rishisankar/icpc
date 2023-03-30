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
const ll mod = 21092013;
int TC;
// get rid of all Us
void clnup(string& s) {
    vector<char> stf;
    rep(i,0,sz(s)) {
        if (s[i] == 'U' && sz(stf)>0) stf.pop_back();
        else if (s[i] != 'U') stf.pb(s[i]);
    }
    s = "";
    for (char c : stf) s += c;
}

void run() {
    string s1,s2; cin >> s1 >> s2;
    clnup(s1);
    dbg(s1);
    int n = sz(s2);
    VLL dp(n+1); // returns amt you can visit (ignoring Us), cur node (ignoring everything) valid
    dp[n] = 1; // for edge cases
    vi pr(n), pl(n);
    int pR = -1, pL = -1;
    for (int i = n-1; i >= 0; --i) {
        if (s2[i] == 'R') pR = i;
        else if (s2[i] == 'L') pL = i;
        pr[i] = pR; pl[i] = pL;
    }
    dbg(pr, pl);
    for (int i = n-1; i >= 0; --i) {
        dp[i] = 1; // assuming you don't traverse
        if (pl[i] != -1) { // can traverse left
            dp[i] += dp[pl[i]+1];
            dp[i] %= mod;
        }
        if (pr[i] != -1) { // can traverse right
            dp[i] += dp[pr[i]+1];
            dp[i] %= mod;
        }
    }
    dbg(dp);
    vi ui; //index of each U
    rep(i,0,n) if (s2[i] == 'U') ui.pb(i);
    ll ans = dp[0];
    rep(i,0,sz(ui)) {
        if (i >= sz(s1)) {
            // going up doesn't do anything, already at root
            break;
        }
        int up = ui[i];
        ans++; // visit the position from the U
        // assume you go up every U before and incl this one
        char rv = s1[sz(s1)-1-i];
        if (rv == 'L') {
            // assume you take U --> R
            if (pr[up] != -1) {
                ans += dp[pr[up]+1];
                ans %= mod;
            }
        } else {
            // assume you take U --> L
            if (pl[up] != -1) {
                ans += dp[pl[up]+1];
                ans %= mod;
            }
        }
    }
    cout << "Case " << (TC+1) << ": " << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    for (TC = 0; TC < t; ++TC) run();
}