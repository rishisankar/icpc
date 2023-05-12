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

// for each node, store set of all unkilled descendants + depth
// when you kill a node, iterate through ancestors, for each ancestor update

inline int gd(set<pii>& s) {
    if (sz(s) == 0) return -1;
    auto it = s.end(); advance(it,-1);
    return it->F;
}

vi getLargest(set<pii>& s) {
    if (sz(s) == 0) return {};
    auto it = s.end();
    advance(it,-1);
    int md = it->F;
    vi ans;
    while (true) {
        if (it->F != md) return ans;
        ans.pb(it->S);
        if (it == s.begin()) return ans;
        advance(it,-1);
    }
    return {};
}

void run() {
    int n,k; cin >> n >> k;
    vi p(n); INP(p,n); rep(i,0,n) if (p[i]!=-1)p[i]--;
    vi pc(n); 
    rep(i,0,n) {
        if (p[i] == -1)++pc[i];
        int c = p[i];
        while (c != -1) {
            ++pc[i];
            c = p[c];
        }
    }
    VVI adj(n);
    rep(i,0,n) {
        if (p[i]!=-1)
        adj[p[i]].pb(i);
    }
    vi cc(n); rep(i,0,n) {
        if (p[i] != -1) cc[p[i]]++;
    }
    vi nlc(n); rep(i,0,n) {
        if (p[i] != -1 && cc[i] == 0) nlc[p[i]]++;
    }
    dbg("r1");
    set<int> lk; rep(i,0,n) if (nlc[p[i]] == 2) lk.insert(i);
    vector<set<pii>> unkilled(n);
    priority_queue<int> kill;
    rep(i,0,n) {
        int c = p[i], d=1;
        while (c!=-1) {
            unkilled[c].insert({d,i});
            c=p[c];
            ++d;
        }
    }
    dbg("r2");
    vi kc(n);
    rep(i,0,n) {
        vi zz = getLargest(unkilled[i]);
        for (auto j : zz) kc[j]++;
    }
    rep(i,0,n) {
        if (kc[i] == pc[i]) {
            kill.push(i);
        }
    }
    dbg("hi");
    VB killed(n,false);
    rep(T,0,n-k) {
        int x;
        if (sz(lk) == 0) {
            x = kill.top(); kill.pop();
        } else {
            auto itz = lk.end(); advance(itz,-1);
            int xx = *itz;
            if (kill.empty() || kill.top() < xx) {
                x = xx;
            } else {
                x = kill.top();
                kill.pop();
            }
        }
        if (lk.find(x) != lk.end()) lk.erase(lk.find(x));
        if (killed[x]) continue;
        killed[x] = true;
        dbg("hi!");
        dbg(x);
        dbg(p[x]);
        nlc[p[x]]--;
        if (nlc[p[x]] == 1) {
            // gotta remove the other thing from lk...
            for (int z : adj[p[x]]) {
                if (z == x) continue;
                lk.erase(lk.find(z));
            }
        } else if (sz(adj[p[x]]) == 1) {
            // now parent is a leaf
            if (p[p[x]] != -1) {
                nlc[p[p[x]]]++;
                if (nlc[p[p[x]]] == 2) {
                    for (int yy : adj[p[p[x]]]) lk.insert(yy);
                }
            }
        }
        dbg("hello");
        int c = p[x], d = 1;
        while (c != -1) {
            int pd = gd(unkilled[c]);
            unkilled[c].erase(unkilled[c].find({d,x}));
            int nd = gd(unkilled[c]);
            if (pd != nd) {
                vi newKill = getLargest(unkilled[c]) ;
                for (int y : newKill) {
                    kc[y]++;
                    if (kc[y] == pc[y]) kill.push(y);
                }
            }
            ++d;
            c = p[c];
        }
    }
    dbg(killed);
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