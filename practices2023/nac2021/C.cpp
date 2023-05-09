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

const pii dir[4] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
int n, m;
bool fits(int k, vector<vi> &grid, int target) {
    dbg("fits",k);
    bool done = false;
    vector<vi> setup(n+2, vi(m+2, 0));
    rep(i, k, n+1) {
        rep(j, k, m+1) {
            if(grid[i][j] - grid[i-k][j] - grid[i][j-k] + grid[i-k][j-k] == 0) {
                dbg("found");
                // start dfsing
                stack<pii> dfs;
                bool visited[n+1][m+1]{};
                visited[i][j] = 1;
                dfs.push({i, j});
                while(!dfs.empty()) {
                    tie(i, j) = dfs.top();
                    dfs.pop();
                    dbg("f1");
                    setup[i-k+1][j-k+1]++;
                    setup[i-k+1][j+1]--;
                    setup[i+1][j-k+1]--;
                    setup[i+1][j+1]++;
                    dbg("f2");
                    for(auto [x,y]: dir) {
                        int ni = i+x, nj = j+y;
                        if(ni <= 0 || ni > n) continue;
                        if(nj <= 0 || nj > m) continue;
                        if(visited[ni][nj]) continue;
                        if (ni-k<0 || nj-k<0)continue;
                        if(grid[ni][nj] - grid[ni-k][nj] - grid[ni][nj-k] + grid[ni-k][nj-k] != 0) continue;
                        visited[ni][nj] = 1;
                        dfs.push({ni, nj});
                    }
                }
                done = true;
                break;
            }
            if (done)break;
        }
        if(done) break;
    }
    dbg("p1 done");
    if (!done) return false;
    vector<vi> pre(n+2, vi(m+2, 0));
    rep(i,0,n+2) pre[i][0] = setup[i][0];
    rep(i,0,m+2) pre[0][i] = setup[0][i];
    rep(i, 1, n+2) {
        rep(j, 1, m+2) {
            pre[i][j] = setup[i][j] - pre[i-1][j-1] + pre[i][j-1] + pre[i-1][j];
        }
    }
    rep(i, 1, n+1) {
        rep(j, 1, m+1) {
            if(pre[i][j] >= 1) target--;
        }
    }
    dbg(pre);
    dbg(target);
    return target==0;
}

void solve() {
    int k;
    cin >> n >> m >> k;
    vector<vi> grid(n, vi(m, 0));
    rep(_, 0, k) {
        int  i, j;
        cin >> i >> j;
        grid[i-1][j-1] = 1;
    }
    vector<vi> pre(n+1, vi(m+1, 0));
    rep(i, 0, n) {
        rep(j, 0, m) {
            pre[i+1][j+1] = grid[i][j] + pre[i+1][j] + pre[i][j+1] - pre[i][j];
        }
    }
    int lo = 0, hi = min(n, m)+1;
    dbg("hi");
    while(lo < hi) {
        int mid = (lo+hi+1)/2;
        if(fits(mid, pre, n*m-k)) lo = mid;
        else hi = mid-1;
    }
    if(lo == 0) {
        cout << -1 << endl;
    } else {
        cout << lo << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}