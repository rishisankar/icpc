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

/*
https://www.youtube.com/watch?v=SLXGYaKx7l0 (table)
Approach:
    iterate row by row, cumulative 2d array
        for each row, maintain monotonic stack by height (increasing)
            store first index of each height also
        for each new height:
            if same as current top, do nothing
            if larger than current top, push to stack
            while smaller than current top:
                add in array the max rectangle w height corresponding to current top
                subtract overlap with max(prev, new)
                    - afterward, can safely pop from stack
            push new, use index of last popped
    finally we have cumulative array stored, per height
        note there is overcounting in the y direction, since we counted iteratively by row
        (ie a 4x3 would be counted again as a 3x3 in the prev row)
        do prefix sum twice in x dir, once in y dir to finalize cts
            ex: 00001 --> 11111 --> 54321 (indicating a 1x5 can make 5 1x1s, 4 1x2s, etc)
            similar idea for y, except only go once since there's overcounting already
*/

void run() {
    int n,m; cin >> n >> m;
    vector<string> grid(n);
    rep(i,0,n) {
        cin >> grid[i];
        grid[i] += '*';
    }
    VVLL cts(n+1, VLL(m+1)); // 1 index for convenience
    vi h(m+1);
    rep(i,0,n) {
        stack<pii> s;
        s.push({0,-1}); // index -1 has height 0 to begin
        rep(j,0,m+1) {
            h[j] = (grid[i][j] == '*' ? 0 : h[j]+1);
            if (s.top().F == h[j]) {
                // do nothing, cur top still representative of state
            } else if (s.top().F < h[j]) {
                // add to stack
                s.push({h[j], j});
            } else {
                int lc = -1; // index where node will be placed at
                while (!s.empty() && s.top().F > h[j]) {
                    auto [hgt,ind] = s.top();
                    s.pop();
                    cts[hgt][j-ind]++;
                    // subtract overlap
                    int prev_h = (s.empty() ? 0 : s.top().F);
                    cts[max(prev_h, h[j])][j-ind]--;
                    lc = ind;
                }
                s.push({h[j], lc});
            }
        }
    }
    // once, do prefix sums in y dir
    rep(j,0,m+1) {
        for (int i = n-1; i >= 0; --i) {
            cts[i][j] += cts[i+1][j];
        }
    }
    // twice, do prefix sums in x dir
    rep(k,0,2) {
        rep(i,0,n+1) {
            for (int j = m-1; j >= 0; --j) {
                cts[i][j] += cts[i][j+1];
            }
        }
    }
    rep(i,1,n+1) {
        rep(j,1,m+1) {
            cout << cts[i][j] << ' ';
        }
        cout << '\n';
    }
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