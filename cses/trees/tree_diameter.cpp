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
Compute diameter of tree by calling dfs on a root node
(Returns # nodes in longest path, if you want # edges, subtract 1)
get<1>(dfs(r)) = diameter, get<3>/get<4> are the end nodes for the diameter.
Time: O(n)
*/

typedef tuple<int,int,int,int,int> TD;

// returns {longest path touching i, longest diam found, root of longest path touching i, r1 of diam, r2 of diam}
TD dfs(int i, int p, VVI& adj) {
    int bestDiam = 1, bestR1 = i, bestR2 = i;
    priority_queue<pii,vector<pii>,greater<pii>> nums; // store top two longest paths
    for (int j : adj[i]) if (j!=p) {
        TD soln = dfs(j,i,adj);
        if (get<1>(soln) > bestDiam) {
            bestDiam = get<1>(soln);
            bestR1 = get<3>(soln);
            bestR2 = get<4>(soln);
        }
        if (get<0>(soln) + 1 > bestDiam) {
            bestDiam = get<0>(soln) + 1;
            bestR1 = get<2>(soln);
            bestR2 = i;
        }
        pii res = {get<0>(soln), get<2>(soln)};
        if (nums.size()==2 && res.F > nums.top().F) nums.pop();
        if (nums.size()<2) nums.push(res);
    }
    if (nums.size() == 2) {
        pii p1 = nums.top(); nums.pop();
        pii p2 = nums.top();
        int newDiam = p1.F + p2.F + 1;
        if (newDiam > bestDiam) {
            bestDiam = newDiam, bestR1 = p1.S, bestR2 = p2.S;
        }
    }
    if (nums.empty()) return {1,1,i,i,i};
    else return {1+nums.top().F, bestDiam, nums.top().S, bestR1, bestR2};
}

void run() {
    int n; cin >> n;
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b); adj[b].pb(a);
    }
    TD ans = dfs(0,-1,adj);
    print(get<1>(ans)-1);
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