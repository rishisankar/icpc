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
Claim: A node is deletable iff it has a sibling that is a leaf, or (it doesn't have a sibling and) for each ancestor of it, it is max depth from it... (and is a leaf!)
*/

void run() {
    int n,k; cin >> n >> k;
    vi p(n); INP(p,n); rep(i,0,n) if (p[i] != -1) p[i]--;
    VVI adj(n); rep(i,0,n) if (p[i] != -1) adj[p[i]].pb(i);
    vector<set<pii, greater<pii>>> descDepths(n);
    rep(i,0,n) {
        int c = p[i], d = 1;
        while (c != -1) {
            descDepths[c].insert({d,i});
            ++d; c=p[c];
        }
    }
    vi lc(n); // store number of leaf children of a node
    rep(i,0,n) {
        if (p[i] != -1 && sz(adj[i]) == 0) lc[p[i]]++;
    }
    set<int, greater<int>> leafKill;
    rep(i,0,n) {
        if (lc[i] == 2) {
            for (int x : adj[i]) leafKill.insert(x);
        }
    }
    set<int, greater<int>> ancKill;
    vi num_anc(n);
    rep(i,0,n) {
        int c = p[i];
        while (c != -1) {
            ++num_anc[i];
            c = p[c];
        }
        if (p[i] == -1) num_anc[i]++;
    }
    vi max_depth_anc(n);
    rep(i,0,n) {
        if (descDepths[i].empty()) continue;
        int max_depth = descDepths[i].begin()->F;
        for (pii p : descDepths[i]) {
            if (p.F != max_depth) break;
            max_depth_anc[p.S]++;
        }
    }
    rep(i,0,n) {
        if (num_anc[i] == max_depth_anc[i]) ancKill.insert(i);
    }
    // dbg("anc kill");
    // for (int i : ancKill) dbg(i+1);
    // dbg("leaf kill");
    // for (int i : leafKill) dbg(i+1);
    VB killed(n, false);
    rep(T, 0, n-k) {
        int x;
        if (ancKill.empty()) x = *(leafKill.begin());
        else if (leafKill.empty()) x = *(ancKill.begin());
        else x = max(*(leafKill.begin()), *(ancKill.begin()));
        dbg("killing", x+1);
        killed[x] = true;
        if (ancKill.count(x)) ancKill.erase(ancKill.find(x));
        if (leafKill.count(x)) leafKill.erase(leafKill.find(x));
        lc[p[x]]--; // parent loses one leaf
        if (lc[p[x]] == 1) {
            // other is now invalidated --> remove from leaf kill
            for (int y : adj[p[x]]) {
                if (leafKill.count(y)) leafKill.erase(leafKill.find(y));
            }
        }
        // parent can become a leaf...
        int childsLeft = 0;
        for (int y : adj[p[x]]) {
            if (!killed[y]) childsLeft++;
        }
        if (childsLeft == 0 && p[p[x]] != -1) {
            lc[p[p[x]]]++;
            if (lc[p[p[x]]] == 2) {
                for (int y : adj[p[p[x]]]) {
                    leafKill.insert(y);
                }
            }
        }
        // finally, update max depth
        int c = p[x], d = 1;
        while (c != -1) {
            int md = descDepths[c].begin()->F;
            descDepths[c].erase(descDepths[c].find({d,x}));
            if (descDepths[c].size() > 0) {
                int nd = descDepths[c].begin()->F;
                if (nd < md) {
                    // max depth has changed! can propagate
                    for (pii p : descDepths[c]) {
                        if (p.F != nd) break;
                        max_depth_anc[p.F]++;
                        if (max_depth_anc[p.F] == num_anc[p.F]) ancKill.insert(p.F);
                    }
                }
            }
            ++d; c = p[c];
        }
    }
    for (bool b : killed) cout << (!b);
    cout << '\n';
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