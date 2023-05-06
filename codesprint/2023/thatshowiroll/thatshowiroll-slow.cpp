#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define rep2(i, a, b) for(i = a; i < (b); ++i) 
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

int v[6], bt[6];

void run() {
    int n; cin >> n;
    VVB pfx(26, VB(26));
    rep(i,0,n) {
        string s; cin >> s;
        int a1 = s[0] - 'a';
        pfx[a1][a1] = true;
        if (sz(s)>1) pfx[a1][s[1]-'a'] = true;
    }
    double bst = -1;
    rep2(v[0], 0, 26) {
        rep2(v[1], v[0]+1, 26) {
            rep2(v[2], v[1]+1, 26) {
                rep2(v[3], v[2]+1, 26) {
                    rep2(v[4], v[3]+1, 26) {
                        rep2(v[5], v[4]+1, 26) {
                            int x = 0;
                            double ans = 0;
                            for (int& i : v) {
                                int y = 0;
                                for (int& j : v) {
                                    if (i==j) x+=pfx[i][j];
                                    else y+=pfx[i][j];
                                }
                                if (y>3) ans += 2*y-6;
                            }
                            ans = ans/36.0 + x/6.0;
                            if (ans > bst) {
                                bst = ans;
                                rep(i,0,6)bt[i]=v[i];
                            }
                        }
                    }
                }
            }
        }
    }
    rep(i,0,6) cout << ((char)(bt[i]+'a'));
    cout << '\n';
    cout << setprecision(20) << bst << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    rep(tests,0,t) run();
}