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

ll solve(string& s, int m, char targ) {
    ll n2 = m/4; ll mc =0;
    vector<bool> ass(m,false);
    rep(i,0,m-1) {
        if (n2 == 0) break;
        if (ass[i] || ass[i+1]) continue;
        if (targ == '1') {
            if (s[i]==targ && s[i+1] == targ) {
                ass[i]=ass[i+1]=true;
                n2--; ++mc;
            }
        } else {
            if ((s[i]-'0') + (s[i+1]-'0') < 2) {
                ass[i]=ass[i+1]=true;
                n2--;
            }
        }
    }
    if (targ == '1') return mc; else return n2;

    // if (targ == '0') {
    //     rep(i,0,m-1) {
    //         if (n2 == 0) break;
    //         if (ass[i] || ass[i+1]) continue;
    //         if (s[i] == '0' || s[i+1] == '0') {
    //             ass[i]=ass[i+1]=true;
    //             ++mc; n2--;
    //         }
    //     }
    //     mc = m/4 - mc;
    // }
    // dbg(mc, sm-mc);
    return mc;
}

void run() {
    ll n,m; cin >> n >> m;
    ll ans1 = 0;
    ll ans2 = 0;
    rep(T,0,n) {
        string s; cin >> s;
        ll sm0 = 0, sm1 = 0;
        rep(i,0,m) {
            if (s[i] =='1')++sm1;
            else ++sm0;
        }
        ll mc1 = solve(s,m,'1');
        ll mc2 = solve(s,m,'0');
        dbg(mc1,mc2);
        ans1 += sm1 - mc1;
        ans2 += sm1 - mc2;
    }
    print(ans1, ans2);
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