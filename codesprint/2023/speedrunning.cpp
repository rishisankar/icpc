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

void run() {
    int n; string s;
    cin >> n >> s;
    VVI dp(n, VI(3,-1));
    for (int i = n-1; i >= 0; i--) {
        rep(j,0,3) {
            if (i == n-1) dp[i][j] = 0;
            else {
                if (s[i] == '.') {
                    int rs = dp[i+1][j];
                    if (rs==-2) dp[i][j]=rs;
                    else dp[i][j] = (j == 0 ? 1 : 2) + rs;
                } else if (s[i] == 'S') {
                    if (j == 0) dp[i][j] = -2;
                    else {
                        int rs = dp[i+1][j-1];
                        if (rs == -2) dp[i][j]=rs;
                        else dp[i][j] = (j-1 == 0 ? 1 : 2) + rs;
                    }
                } else {
                    int rz1 = dp[i+1][j], rz2 = -2;
                    if (rz1 != -2) rz1 += (j == 0 ? 1 : 2);
                    if (j != 2) {
                        rz2 = dp[i+1][j+1];
                        if (rz2 != -2) rz2 += 2;
                    }
                    if (rz1 == -2) dp[i][j] = rz2;
                    else if (rz2 == -2) dp[i][j] = rz1;
                    else dp[i][j] = min(rz1, rz2);
                }
            }
        }
    }
    set<int> st;
    rep(i,0,3) st.insert(dp[0][i]);
    if (st.count(-2))st.erase(st.find(-2));
    if (sz(st) == 0) print(-1);
    else print(*(st.begin()));
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