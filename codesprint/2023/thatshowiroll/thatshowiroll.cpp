#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("popcnt")

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

typedef tuple<int,int,int,int,int,int> T;

void run() {
    int n; cin >> n;
    vector<int> cts(27);
    rep(i,0,n) {
        string s; cin >> s;
        cts[26] |= (1 << (s[0]-'a'));
        if (sz(s)>1) cts[s[0]-'a'] |= (1 << (s[1]-'a'));
    }
    int bs = 0;
    double bst = -1;
    T bt;
    rep(l1, 0, 26) {
        bs ^= (1<<l1);
        rep(l2, l1+1, 26) {
            bs ^= (1<<l2);
            rep(l3, l2+1, 26) {
                bs ^= (1<<l3);
                rep(l4, l3+1, 26) {
                    bs ^= (1<<l4);
                    rep(l5, l4+1, 26) {
                        bs ^= (1<<l5);
                        rep(l6, l5+1, 26) {
                            bs ^= (1<<l6);
                            double val = __builtin_popcount(cts[26]&bs) / 6.0;
                            int c1 = __builtin_popcount(cts[l1]&bs);
                            int c2 = __builtin_popcount(cts[l2]&bs);
                            int c3 = __builtin_popcount(cts[l3]&bs);
                            int c4 = __builtin_popcount(cts[l4]&bs);
                            int c5 = __builtin_popcount(cts[l5]&bs);
                            int c6 = __builtin_popcount(cts[l6]&bs);
                            int c = 0;
                            if (c1>3) c += c1+c1-6;
                            if (c2>3) c += c2+c2-6;
                            if (c3>3) c += c3+c3-6;
                            if (c4>3) c += c4+c4-6;
                            if (c5>3) c += c5+c5-6;
                            if (c6>3) c += c6+c6-6;
                            val += c/36.0;
                            if (val > bst) {
                                bst = val;
                                bt = {l1,l2,l3,l4,l5,l6};
                            }
                            bs ^= (1<<l6);
                        }
                        bs ^= (1<<l5);
                    }
                    bs ^= (1<<l4);
                }
                bs ^= (1<<l3);
            }
            bs ^= (1<<l2);
        }
        bs ^= (1<<l1);
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