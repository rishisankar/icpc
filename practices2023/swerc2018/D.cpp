#include <bits/stdc++.h>
using namespace std;

#define int long long
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
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

void run() {
    int x,y; cin >> x >> y;
    int n; cin >> n;
    vector<vi> pts(x);
    rep(i,0,n) {
        int a,b; cin >> a >> b;
        pts[a].pb(b);
    }
    rep(i,0,x) sort(all(pts[i]));
    vector<pii> invs;
    rep(i,0,x) {
        if (sz(pts[i]) > 0) {
            invs.pb({pts[i].front(), pts[i].back()});
        }
    }
    sort(all(invs));
    stack<pii> invs_stk;
    for (int i = sz(invs)-1; i >= 0; --i) invs_stk.push(invs[i]);
    int invs_above = 0, invs_below = sz(invs);
    int cost_above = 0, cost_below = 0, cost_in = 0;
    for (auto p : invs) {
        cost_below += (p.S + 1) * 2;
    }
    priority_queue<pii, vector<pii>, greater<pii>> invs_in; // store y,x
    int bst_cost = LLONG_MAX;
    rep(l, 0, y) {
        cost_below -= 2 * invs_below;
        cost_above += 2 * invs_above;
        while (!invs_in.empty() && invs_in.top().F < l) {
            auto p = invs_in.top(); invs_in.pop();
            invs_above++;
            cost_above += 2 * (l - p.S); 
            cost_in -= 2*(p.F - p.S);
        }
        while (!invs_stk.empty() && invs_stk.top().F == l) {
            auto p = invs_stk.top(); invs_stk.pop();
            cost_below -= 2 * (p.S - p.F);
            cost_in += 2*(p.S-p.F);
            invs_in.push({p.S,p.F});
            invs_below--;
        }
        int cost = cost_above + cost_below + cost_in;
        dbg(cost, cost_above, cost_below, cost_in);
        bst_cost = min(bst_cost, cost);
    }
    dbg(bst_cost);
    print(bst_cost + x - 1);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}