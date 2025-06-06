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

template<typename T> inline T ceildiv(T a, T b) {return (a+b-1)/b;}

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
typedef pair<ull, ull> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

int n;
string s;

vector<pair<bool, pair<pii, pll>>> words;
vector<ull> wordlens;
vector<ll> spfx;
vector<map<pll, ll>> states;

// query word0 on [l,r)
ll strsum(int l, int r) {
    if (l == 0) {
        return spfx[r-1];
    } else {
        return (spfx[r-1] - spfx[l-1] + mod + mod) % mod;
    }
}

ll query(int word, ull l, ull r);
ll query_(int word, ull l, ull r) {
    if (words[word].F) {
        // APP
        int x = words[word].S.F.F, y = words[word].S.F.S;
        ll ans = 0;
        if (l < wordlens[x]) {
            ans += query(x, l, min(r, wordlens[x]));
        }
        if (r > wordlens[x]) {
            ull lb = 0;
            if (l > wordlens[x]) lb = l - wordlens[x];
            ans += query(y, lb, r - wordlens[x]);
        }
        return ans % mod;
    } else {
        // SUB
        int x = words[word].S.F.F;
        ull lo = words[word].S.S.F, hi = words[word].S.S.S;
        return query(x, l + lo, r + lo);
    }
}

ll query(int word, ull l, ull r) {
    if (word == 0) return strsum(l,r);
    auto it = states[word].find({l,r});
    if (it != states[word].end()) return it->second;
    return states[word][{l,r}] = query_(word,l,r);
}

void run() {
    cin >> n;
    cin >> s;
    words.resize(n);
    states.resize(n);
    spfx.resize(sz(s));
    wordlens.resize(n);
    wordlens[0] = sz(s);
    spfx[0] = s[0];
    rep(i,1,sz(s)) {
        spfx[i] = (spfx[i-1] + s[i]) % mod;
    }
    rep(i,1,n) {
        string wd; cin >> wd;
        if (wd == "SUB") {
            int x;
            ull lo, hi;
            cin >> x >> lo >> hi;
            words[i].F = false;
            words[i].S.F.F = x;
            words[i].S.S.F = lo;
            words[i].S.S.S = hi;
            wordlens[i] = hi - lo;
        } else {
            int x,y; cin >> x >> y;
            words[i].F = true;
            words[i].S.F.F = x;
            words[i].S.F.S = y;
            wordlens[i] = wordlens[x] + wordlens[y];
        }
    }
    print(query(n-1, 0, wordlens[n-1]));
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