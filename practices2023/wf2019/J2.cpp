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
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(_VA_ARGS_)
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
pll sc[501];

void run() {
    int p,h; cin >> p >> h;
    vector<vector<ll>> nums(p, vector<ll>(h+1, LLONG_MAX));
    vector<ll> sums(p);

    unordered_set<ll> crit;
    rep(i,0,p) {
        ll sum = 0;
        rep(j,0,h) {
            cin >> nums[i][j];
            sum += nums[i][j];
            crit.insert(nums[i][j]);
        }
        nums[i][h] = 0;
        sort(all(nums[i]));
        sums[i] = sum;
    }
    rep(i, 0, p) {
        rep(j, 0, i) {
            vector<ll> &a = nums[i];
            vector<ll> &b = nums[j];
            int f = h; // first pointer
            int s = h; // second pointer
            ll diff = sums[i]-sums[j];
            // positive: j winning; negative: i winning; 0: tie
            ll cur = mod, nxt;
            ll trans = 0;
            while(f || s) {
                // dbg(a, b, cur);
                nxt = max(a[f], b[s]);
                ll d = cur-nxt;
                if(trans == 0 || d == 0) {}
                else {
                    if(diff == 0) {
                        crit.insert(cur-1);
                    } else if(diff > 0 && trans < 0) {
                        ll t = -trans;
                        ll steps = (diff+t-1)/t;
                        if(steps <= d) {
                            crit.insert(cur-steps);
                        }
                    } else if(diff < 0 && trans > 0) {
                        ll t = -diff;
                        ll steps = (t+trans-1)/trans;
                        if(steps <= d) {
                            crit.insert(cur-steps);
                        }
                    }
                }
                diff += trans*d;
                // cleanup
                cur = nxt;
                if(a[f] == b[s]) {
                    f--;
                    s--;
                } else if(a[f] > b[s]) {
                    f--;
                    trans--;
                } else {
                    s--;
                    trans++;
                }
            }
        }
    }
    VLL ans(p,LLONG_MAX);
    for(ll x: crit) {
        // dbg(x);
        rep(i,0,p) sc[i] = {0,i};
        rep(i,0,p) {
            rep(j,1,h+1) {
                sc[i].F += min(nums[i][j], x);
            }
        }
        sort(begin(sc), begin(sc)+p);
        for (int i = p-1; i >= 0; --i) {
            ll r = i+1;
            if (i < p-1 && sc[i+1].F == sc[i].F) r = sc[i+1].S;
            ans[sc[i].S] = min(ans[sc[i].S], r);
            sc[i].S = r;
        }
    }
    rep(i,0,p) print(ans[i]);
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