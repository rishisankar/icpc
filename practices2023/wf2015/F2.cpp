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
    int r,c; cin >> r >> c;
    vector<string> grid(r);
    rep(i,0,r) cin >> grid[i];
    string tgt; cin >> tgt; tgt += '*';
    vector<vector<pii>> coords(256);
    vector<vector<vector<pii>>> adj(r, vector<vector<pii>>(c));
    rep(i,0,r) {
        rep(j,0,c) {
            for (auto dir : dirs) {
                int nx = i+dir.F, ny = j+dir.S;
                while (nx >= 0 && ny >= 0 && nx < r && ny < c) {
                    if (grid[nx][ny] != grid[i][j]) {
                        adj[i][j].pb({nx,ny});
                        break;
                    }
                    nx+=dir.F; ny +=dir.S;
                }
            }
        }
    }

    unordered_set<char> options;
    options.insert('*');
    options.insert('-');
    for (char C = '0'; C <= '9'; ++C) {
        options.insert(C);
    }
    for (char C = 'A'; C <= 'Z'; ++C) {
        options.insert(C);
    }

    vector<vector<vector<vector<pair<pii,int>>>>> dists(r, vector<vector<vector<pair<pii,int>>>>(c, vector<vector<pair<pii,int>>>(256)));
    rep(i,0,r) {
        rep(j,0,c) {
            for (char cc : options) {
                // populate dists
                queue<pair<pii,int>> q;
                vector<vector<bool>> vis(r, vector<bool>(c));
                q.push({{i,j},0});
                vis[i][j] = 1;
                while (!q.empty()) {
                    auto t = q.front(); q.pop();
                    if (grid[t.F.F][t.F.S] == cc) {
                        dists[i][j][grid[t.F.F][t.F.S]].pb(t);
                    } else {
                        for (pii p : adj[t.F.F][t.F.S]) {
                            if (vis[p.F][p.S]) continue;
                            q.push({p, t.S+1});
                            vis[p.F][p.S] = 1;
                        }
                    }
                }
            }
        }
    }


    // dists[i][j][L] = {}
    // vector<vector<vector<vector<pair<pii,int>>>>> dists(r, vector<vector<vector<pair<pii,int>>>>(c, vector<vector<pair<pii,int>>>(256)));
    // rep(i,0,r) {
    //     rep(j,0,c) {
    //         // populate dists
    //         queue<pair<pii,int>> q;
    //         vector<vector<bool>> vis(r, vector<bool>(c));
    //         q.push({{i,j},0});
    //         vis[i][j] = 1;
    //         while (!q.empty()) {
    //             auto t = q.front(); q.pop();
    //             dists[i][j][grid[t.F.F][t.F.S]].pb(t);
    //             for (pii p : adj[t.F.F][t.F.S]) {
    //                 if (vis[p.F][p.S]) continue;
    //                 q.push({p, t.S+1});
    //                 vis[p.F][p.S] = 1;
    //             }
    //         }
    //     }
    // }

    // map<pii,int> costs;
    // costs[{0,0}] = 0;

    // rep(i,0,sz(tgt)) {
    //     map<pii,int> c2;
    //     for (auto p : costs) {
    //         for (auto dst : dists[p.F.F][p.F.S][tgt[i]]) {
    //             auto it = c2.find({dst.F});
    //             if (it == c2.end()) {
    //                 c2[dst.F] = p.S + dst.S;
    //             } else {
    //                 it->S = min(it->S, p.S + dst.S);
    //             }
    //         }
    //     }
    //     swap(costs, c2);
    // }
    // int bst = INT_MAX;
    // for (auto p : costs) bst = min(bst, p.S);
    // print(sz(tgt) + bst);

    unordered_map<int,int> costs;
    costs[0] = 0;

    rep(i,0,sz(tgt)) {
        unordered_map<int,int> c2;
        for (auto p : costs) {
            int R = p.F / c, C = p.F % c;
            for (auto dst : dists[R][C][tgt[i]]) {
                int idx = dst.F.F * c + dst.F.S;
                auto it = c2.find({idx});
                if (it == c2.end()) {
                    c2[idx] = p.S + dst.S;
                } else {
                    it->S = min(it->S, p.S + dst.S);
                }
            }
        }
        swap(costs, c2);
    }
    int bst = INT_MAX;
    for (auto p : costs) bst = min(bst, p.S);
    print(sz(tgt) + bst);
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