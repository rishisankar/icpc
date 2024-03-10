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
const int B = 30;
#else
#define dbg(...)
const int B = 205;
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

bool run(int r, int c, string nutS, vector<string> rows) {
    bitset<B> nut(nutS);
    vector<vector<bool>> valid(r, VB(c));
    // dbg(nut.to_string());
    rep(i,0,r) {
        string s = rows[i]; s += s; bitset<B> bolt(s);
        rep(j,0,c) {
            if ((bolt ^ (nut<<j)) == (bolt | (nut<<j))) {
                valid[i][j] = 1;
            }
        }
    }
    // dbg(valid);

    stack<pii> s;
    vector<VB> vis(r,VB(c));
    rep(i,0,c) {
        if (valid[0][i]) s.push({0,i});
        vis[0][i] = 1;
    }
    while (!s.empty()) {
        pii t = s.top();
        s.pop();
        
        vector<pii> adjs;
        // rotations
        pii r1 = {t.F, (t.S+1)%c};
        pii r2 = {t.F, (t.S+c-1)%c};
        adjs.pb(r1);
        adjs.pb(r2);
        // go up a row
        if (t.F>0) adjs.pb({t.F-1,t.S});
        // or down
        if (t.F < r-1) adjs.pb({t.F+1,t.S});

        for (pii p : adjs) {
            if (!valid[p.F][p.S]) continue;
            if (vis[p.F][p.S]) continue;
            vis[p.F][p.S] = 1;
            s.push(p);
        }
    }
    rep(i,0,c) if (vis[r-1][i]) return true;

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);

    int r,c; cin >> r >> c;
    string nutS; cin >> nutS;
    vector<string> maze(r); rep(i,0,r) cin >> maze[i];
    if (run(r,c,nutS,maze)) {
        print("Y");
        return 0;
    }
    reverse(all(nutS));
    if (run(r,c,nutS,maze)) {
        print("Y");
        return 0;
    }
    print("N");


}