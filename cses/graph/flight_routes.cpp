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

typedef pair<ll,int> pli ;
void run() {
    int n,m,k; cin >> n >> m >> k;
    vector<vector<pair<int,ll>>> adj(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        ll x; cin >> x;
        adj[a].pb({b,x});
    }
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    vector<priority_queue<ll>> routeCosts(n);
    pq.push({0,0});
    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int t = top.S; ll c = top.F;
        if (routeCosts[t].size() >= k && routeCosts[t].top() < c) continue;
        for (pair<int,ll> p : adj[t]) {
            ll dst = p.S + c;
            if (routeCosts[p.F].size() < k) {
                // route works
                routeCosts[p.F].push(dst);
                pq.push({dst, p.F});
            } else if (routeCosts[p.F].top() > dst) {
                routeCosts[p.F].pop();
                routeCosts[p.F].push(dst);
                pq.push({dst,p.F});
            }
        }
    }
    vector<ll> ans;
    while (!routeCosts[n-1].empty()) {
        ans.pb(routeCosts[n-1].top());
        routeCosts[n-1].pop();
    }
    reverse(all(ans));
    rep(i,0,k) cout << ans[i] << ' ';
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