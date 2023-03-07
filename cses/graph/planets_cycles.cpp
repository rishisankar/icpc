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
VI jmp;
VI cyclen;
void dfs_cyc(int t, VI& colors) {
    int x = jmp[t];
    if (colors[x] >= 2) return;
    if (colors[x] == 1) {
        // cycle found
        int cur = x;
        int ln = 1;
        while (jmp[cur] != x) {
            colors[cur] = 3;
            cur = jmp[cur];
            ++ln;
        }
        colors[cur] = 3;
        cur = x;
        while (jmp[cur] != x) {
            cyclen[cur] = ln;
            cur = jmp[cur];
        }
        cyclen[cur] = ln;
    } else {
        colors[t] = 1;
        dfs_cyc(x,colors);
        if (colors[t] == 1) colors[t] = 2;
    }
}

void run() {
    int n; cin >> n;
    jmp.resize(n);
    cyclen.resize(n);
    vector<vi> radj(n);
    rep(i,0,n) {
        cin >> jmp[i]; --jmp[i];
        radj[jmp[i]].pb(i);
    }
    VI colors(n,0); // 0 = white, 1 = gray, 2 = black, 3 = in cycle
    rep(i,0,n) {
        if (colors[i] == 0) {
            dfs_cyc(i,colors);
        }
    }
    // dbg(colors);
    vector<pii> ans(n);
    rep(i,0,n) {
        if (colors[i] == 3) {
            stack<int> s;
            s.push(i);
            ans[i] = {i,0};
            while(!s.empty()) {
                int t = s.top();
                s.pop();
                for (int x : radj[t]) {
                    if (colors[x]==3) continue;
                    ans[x] = {i, ans[t].S+1};
                    s.push(x);
                }
            }
        }
    }
    rep(i,0,n) {
        cout << (ans[i].S+cyclen[ans[i].F]) << ' ';
    }
    cout << "\n";
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