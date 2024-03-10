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
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

void run() {
    int w,h,n; cin >> w >> h >> n;
    vector<vector<int>> l(w);
    vector<set<int>> ls(w);
    vi v(n);
    VVI rowIndices(n);
    VLL rowTime(n);
    rep(i,0,n) {
        cin >> v[i];
        int rw = sz(l[v[i]]);
        rowIndices[rw].pb(v[i]);
        l[v[i]].pb(i);
        ls[v[i]].insert(i);
    }
    dbg(l);
    int ctr = 0;
    for (int i = 0; i < n; ++i) {
        ll minTime = 0; // time must be >= minTime
        if (sz(rowIndices[i]) == 0)  break;
        if (i - h >= 0) {
            if (sz(rowIndices[i-h]) != w) {
                print(-1);
                return;
            }
            minTime = rowTime[i-h] + 1;
        }
        for (int ind : rowIndices[i]) {
            ll bt0 = minTime % n;
            ll t0;
            auto it = ls[ind].lower_bound(bt0);
            if (it != ls[ind].end()) {
                t0 = (*it);
                ls[ind].erase(it);
            } else {
                t0 = *(ls[ind].begin());
                ls[ind].erase(ls[ind].begin());
            }

            // ll t0 = l[ind][i];
            ll xm = (minTime - t0) / n;
            ll ans = xm + 5;
            for (ll xs = xm - 3; xs <= xm + 4; ++xs) {
                if (xs < 0) continue;
                if (t0 + n * xs >= minTime) {
                    ans = xs;
                    break;
                }
            }
            ctr += ans;
            rowTime[i] = max(rowTime[i], t0 + ans * n);
        }
    }
    dbg(rowTime);
    print(ctr);
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