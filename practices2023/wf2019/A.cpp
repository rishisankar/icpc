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

struct custom_hash { // https://codeforces.com/blog/entry/62393
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
    vector<set<pll>> ct, cb;
    vector<pair<ll,pll>> top(n), bot(n);
    rep(i,0,n) top[i].S.S = bot[i].S.S = i+1;
    rep(i,0,n) cin >> top[i].F;
    rep(i,0,n) cin >> top[i].S.F;
    rep(i,0,n) cin >> bot[i].F;
    rep(i,0,n) cin >> bot[i].S.F;
    sort(all(top));
    sort(all(bot));
    ll curt = -1, curb = -1;
    for (auto p : top) {
        if (curt != p.F) {
            ct.resize(sz(ct)+1);
            curt = p.F;
        }
        ct.back().insert(p.S);
    }
    for (auto p : bot) {
        if (curb != p.F) {
            cb.resize(sz(cb)+1);
            curb = p.F;
        }
        cb.back().insert(p.S);
    }
    // dbg(ct.size(), cb.size());
    // for (auto& s : ct) {
    //     dbg("S", sz(s));
    //     for (pll x : s) cerr << x << ' ';
    //     cerr << endl;
    // }
    // for (auto& s : cb) {
    //     dbg("S", sz(s));
    //     for (pll x : s) cerr << x << ' ';
    //     cerr << endl;
    // }
    curt = 0, curb = 0;
    vi atop, abot;
    rep(i,0,n) {
        if (sz(ct[curt])==0)++curt;
        if (sz(cb[curb])==0)++curb;
        bool tbig = (sz(ct[curt]) > sz(cb[curb]));
        auto& pbig = (tbig ? ct[curt] : cb[curb]);
        auto& psmall = (tbig ? cb[curb] : ct[curt]);
        auto node = psmall.begin();
        // dbg(i, tbig, *node);
        set<pll>::iterator it;
        if (tbig) {
            it = pbig.lower_bound({node->F, n+5});
            if (it == pbig.end()) {
                print("impossible");
                return;
            }
        } else {
            it = pbig.lower_bound({node->F, -5});
            if (it == pbig.begin()) {
                print("impossible");
                return;
            }
            advance(it,-1);
        }
        if (tbig) {
            atop.pb(it->S);
            abot.pb(node->S);
        } else {
            abot.pb(it->S);
            atop.pb(node->S);   
        }
        pbig.erase(it); psmall.erase(node);
    }
    // dbg(atop);
    // dbg(abot);
    for (int i : atop) cout << i << ' ';
    cout << '\n';
    for (int i : abot) cout << i << ' ';
    cout << '\n';
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