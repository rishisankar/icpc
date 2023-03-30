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

const ld inf = 1LL << 32;
map<pii, int> par;
void floydWarshall(vector<vector<ld>>& m) {
	int n = sz(m);
	rep(i,0,n) m[i][i] = min(m[i][i], 0.0L);
	rep(k,0,n) rep(i,0,n) rep(j,0,n)
		if (m[i][k] != inf && m[k][j] != inf) {
			auto newDist = max(m[i][k] + m[k][j], -inf);
            if (newDist < m[i][j]) {
                m[i][j] = newDist;
                if (k != i && k != j) par[{i,j}] = k;
            }
		}
}

void bp(vi& path, int a, int b) {
    if (a == b) {
        path.pb(a);
    } else if (!par.count({a,b})) {
        path.pb(a); path.pb(b);
    } else {
        int k = par[{a,b}];
        bp(path, a, k);
        path.pop_back();
        bp(path, k, b);
    }
}

inline ld euc(ld x1, ld y1, ld z1, ld x2, ld y2, ld z2) {
    return sqrtl((x1-x2)*(x1-x2)*25 + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

void run() {
    int n,m; cin >> n >> m;
    vector<pair<ll,pll>> locs(n);
    rep(i,0,n) {
        cin >> locs[i].F >> locs[i].S.F >> locs[i].S.S;
    }
    vector<vector<ld>> adjm(n, vector<ld>(n, inf));
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        string s; cin >> s;
        ld dis = euc(locs[a].F, locs[a].S.F, locs[a].S.S, locs[b].F, locs[b].S.F, locs[b].S.S);
        if (s == "walking" || s == "stairs") {
            adjm[a][b] = min(adjm[a][b], dis);
            adjm[b][a] = min(adjm[b][a], dis);
        } else if (s == "lift") {
            if (a == 0 && b == 2) dbg(adjm[a][b]);
            adjm[a][b] = min(adjm[a][b], 1.0L);
            adjm[b][a] = min(adjm[b][a], 1.0L);
            if (a == 0 && b == 2)dbg("l",adjm[a][b]);
        } else {
            // escalator
            adjm[a][b] = min(adjm[a][b], 1.0L);
            adjm[b][a] = min(adjm[b][a], 3*dis);
        }
    }
    floydWarshall(adjm);
    int Q; cin >> Q;
    rep(q,0,Q) {
        int a,b; cin >> a >> b;
        vi path;
        bp(path, a, b);
        for (int i : path) cout << i << " ";
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