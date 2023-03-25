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

ll gid(vi& state) {
    ll z = 0, c = 1;
    rep(i,0,9) {
        z += state[i] * c;
        c *= 9;
    }
    return z;
}

bool check(vi& v) {
    rep(i,0,9) if (v[i] != i+1) return false;
    return true;
}

void run() {
    vector<int> initial;
    rep(i,0,3) {
        rep(j,0,3) {
            int x; cin >> x;
            initial.pb(x);
        }
    }
    if (check(initial)) {
        print(0);
        return;
    }
    unordered_set<ll> vis;
    vis.insert(gid(initial));
    queue<pair<vi,int>> s;
    s.push({initial,0});
    while (!s.empty()) {
        pair<vi,int> tt = s.front();
        vi t = tt.F;
        s.pop();
        // try swapping various pairs
        rep(i,0,9) {
            int x = i/3, y = i%3;
            if (x < 2) {
                vi sr(t);
                swap(sr[i], sr[(x+1)*3+y]);
                ll z = gid(sr);
                if (!vis.count(z)) {
                    if (check(sr)) {
                        print(tt.S+1);
                        return;
                    }
                    vis.insert(z);
                    s.push({sr,tt.S+1});
                }
            }
            if (y < 2) {
                vi sr(t);
                swap(sr[i], sr[i+1]);
                ll z = gid(sr);
                if (!vis.count(z)) {
                    if (check(sr)) {
                        print(tt.S+1);
                        return;
                    }
                    vis.insert(z);
                    s.push({sr,tt.S+1});
                }
            }
        }
    }
    dbg("fail");
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