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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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
    string s; cin >> s;
    set<int> ss,sp,sb,su;
    rep(i,0,n) {
        if (s[i] == 's') ss.insert(i);
        else if (s[i] == 'p') sp.insert(i);
        else if (s[i] == 'b') sb.insert(i);
        else if (s[i] == 'u') su.insert(i);
    }
    ss.insert(n);
    sb.insert(n);
    sp.insert(n);
    su.insert(n);
    ll bst = LLONG_MAX;
    // for (int i0 : ss) {
    //     int i1 = *(sp.lower_bound(i0));
    //     int i2 = *(sb.lower_bound(i1));
    //     int i3 = *(ss.lower_bound(i2));
    //     int i4 = *(su.lower_bound(i3));
    //     if (i0==n||i1==n||i2==n||i3==n||i4==n)continue;
    //     ll ans = (i1-i0-1) + (i2-i1-1)*2 + (i3-i2-1)*2 + (i4-i3-1);
    //     dbg(i0,i1,i2,i3,i4,ans);
    //     bst=min(bst,ans);
    // }
    for (int i2 : sb) {
        int i3 = *(ss.lower_bound(i2));
        int i4 = *(su.lower_bound(i3));
        auto it1 = sp.lower_bound(i2);
        if (it1 == sp.begin()) continue;
        advance(it1,-1);
        int i1 = *it1;
        auto it0 = ss.lower_bound(i1);
        if (it0 == ss.begin()) continue;
        advance(it0,-1);
        int i0 = *it0;
        if (i0==n||i1==n||i2==n||i3==n||i4==n)continue;
        ll ans = (i1-i0-1) + (i2-i1-1)*2 + (i3-i2-1)*2 + (i4-i3-1);
        dbg(i0,i1,i2,i3,i4,ans);
        bst=min(bst,ans);
    }
    print(bst);
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