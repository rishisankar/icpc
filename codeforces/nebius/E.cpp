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
start node of mask is always first set bit
cyc[mask]: is there a cycle for this mask
path[mask][end]: is there a path for this mask with given end node

cyc[mask]: for each end node, if path + conn(start,end) then cycle

path[mask][end]: for each node end is connected to, if in mask + connected to end + path[mask-end][c] then path

validate cycle: if anything is not connected to the cycle, fail
*/

VVB adjm;
VVI adj;


/*
Computes hamiltonian path and cycle (undirected, unweighted graph)
- For a given mask, fix start S as the rightmost 1 bit set; find hamiltonian path/cycle using all set bits
- cyc[mask]: stores last node in cycle starting from S (can use path to reconstruct), or -1 if no cycle
- path[mask][end]: stores previous node in hamiltonian path from S to end (-1 if no path, -2 if no prev i.e. S=end)
Time: O(2^N * N^2)

Note: mask uses ints ==> N < 31 (complexity too slow otherwise anyway)
Example: https://codeforces.com/contest/1804/problem/E
*/
pair<VVI, VI> hamiltonian(VVI& adj, VVB& adjm) {
    int n = adj.size();
    vector<int> masks;
    rep(i,0,(1<<n)) {
        masks.pb(i);
    }
    sort(all(masks), [&](int a, int b) {
        return __builtin_popcount(a) < __builtin_popcount(b);
    });
    VVI path((1<<n), VI(n,-1));
    VI cyc((1<<n), -1);
    for (int mask : masks) {
        if (mask == 0) continue;
        int s = -1; // can change if need to fix root
        rep(i,0,n) {
            if ((mask >> i)&1) {
                s = i;
                break;
            }
        }
        int siz = __builtin_popcount(mask);
        if (siz == 1) {
            path[mask][s] = -2;
            continue;
        }
        rep(end,s+1,n) {
            if (((mask >> end)&1) == 0) continue;
            if (siz == 2) path[mask][end] = (adjm[s][end] ? s : -1);
            else {
                for (int a : adj[end]) { // find node to be second last in path
                    if (a == s) continue;
                    if (((mask >> a)&1) && path[(mask ^ (1<<end))][a] != -1) {
                        path[mask][end] = a;
                        break;
                    }
                }
            }
        }
        // siz >= 2 can have cycle, so check:
        rep(end,s+1,n) {
            if (((mask >> end)&1) == 0 || !adjm[s][end]) continue;
            if (path[mask][end] != -1) {
                cyc[mask] = end;
                break;
            }
        }
    }
    return {path, cyc};
}

/*
Recover a hamiltonian path from precomputed path array (given mask, end node)
Assumes path[mask][end] != -1
To recover a cycle: recoverPath(path, mask, cyc[mask]); (then append start if you want)
*/
VI recoverPath(VVI& path, int mask, int E) {
    VI res;
    res.pb(E);
    int cur = path[mask][E];
    mask ^= (1<<E);
    while (cur != -2) {
        res.pb(cur);
        cur = path[mask][cur];
        mask ^= (1 << res.back()); // update mask to remove cur
    }
    reverse(all(res)); // optional
    return res;
}

void run() {
    int n,m; cin >> n >> m;
    adj.resize(n);
    adjm.resize(n,VB(n,false));
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj[a].pb(b); adj[b].pb(a);
        adjm[a][b] = adjm[b][a] = true;
    }
    VVI path; VI cyc;
    tie(path,cyc) = hamiltonian(adj,adjm);
    rep(mask,0,(1<<n)) {
        if (cyc[mask] == -1) continue;
        vi elts;
        rep(i,0,n) {
            if ((mask >> i)&1) elts.pb(i);
        }
        // test if neighbors are connected to cycle
        VI ass(n,-1);
        bool valid = true;
        rep(i,0,n) {
            if ((mask >> i)&1) continue;
            for (int j : elts) {
                if (adjm[i][j]) {
                    ass[i] = j;
                    break;
                }
            }
            if (ass[i] == -1) {
                valid = false;
                break;
            }
        }
        if (valid) {
            print("Yes");
            VI hamilton_path = recoverPath(path, mask, cyc[mask]);
            int hpsz = hamilton_path.size();
            rep(i,0,hpsz) {
                ass[hamilton_path[i]] = hamilton_path[(i+1)%hpsz];
            }
            for (int i : ass) {
                cout << (i+1) << ' ';
            }
            cout << '\n';
            return;
        }
    }
    print("No");
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