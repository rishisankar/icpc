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
    int n; cin >> n;
    VVB pfx(26, VB(26));
    rep(i,0,n) {
        string s; cin >> s;
        int a1 = s[0] - 'a';
        pfx[a1][a1] = true;
        if (sz(s)>1) pfx[a1][s[1]-'a'] = true;
    }
    tuple<int,int,int,int,int,int> bt;
    double bst = -1;
    rep(l1, 0, 26) {
        rep(l2, l1+1, 26) {
            rep(l3, l2+1, 26) {
                rep(l4, l3+1, 26) {
                    rep(l5, l4+1, 26) {
                        rep(l6, l5+1, 26) {
                            int x = 0;
                            double ans = 0;
                            x += pfx[l1][l1];
                            x += pfx[l2][l2];
                            x += pfx[l3][l3];
                            x += pfx[l4][l4];
                            x += pfx[l5][l5];
                            x += pfx[l6][l6];
                            int y = pfx[l1][l2] + pfx[l1][l3] + pfx[l1][l4] + pfx[l1][l5] + pfx[l1][l6];
                            if (y>3) ans += 2*y-6;
                            y = pfx[l2][l1] + pfx[l2][l3] + pfx[l2][l4] + pfx[l2][l5] + pfx[l2][l6];
                            if (y>3) ans += 2*y-6;
                            y = pfx[l3][l1] + pfx[l3][l2] + pfx[l3][l4] + pfx[l3][l5] + pfx[l3][l6];
                            if (y>3) ans += 2*y-6;
                            y = pfx[l4][l1] + pfx[l4][l2] + pfx[l4][l3] + pfx[l4][l5] + pfx[l4][l6];
                            if (y>3) ans += 2*y-6;
                            y = pfx[l5][l1] + pfx[l5][l2] + pfx[l5][l3] + pfx[l5][l4] + pfx[l5][l6];
                            if (y>3) ans += 2*y-6;
                            y = pfx[l6][l1] + pfx[l6][l2] + pfx[l6][l3] + pfx[l6][l4] + pfx[l6][l5];
                            if (y>3) ans += 2*y-6;
                            ans = ans/36.0 + x/6.0;
                            if (ans > bst) {
                                bst = ans;
                                bt = {l1,l2,l3,l4,l5,l6};
                            }
                        }
                    }
                }
            }
        }
    }
    cout << ((char)(get<0>(bt)+'a')) 
         << ((char)(get<1>(bt)+'a'))
         << ((char)(get<2>(bt)+'a'))
         << ((char)(get<3>(bt)+'a'))
         << ((char)(get<4>(bt)+'a'))
         << ((char)(get<5>(bt)+'a'))
         << '\n';
    cout << setprecision(20) << bst << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    rep(tests,0,t) run();
}