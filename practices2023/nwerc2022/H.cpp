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

vi depth;
pair<vector<vi>,vi> rootTree(vector<vi>& adj, int r) {
    int n = adj.size();
    vector<vi> childs(n);
    vi parent(n);
    vector<bool> visited(n,false);
    stack<int> s;
    s.push(r);
    visited[r] = true;
    parent[r] = -1;
    while (!s.empty()) {
        int t = s.top();
        if (parent[t] == -1) depth[t] = 0; else depth[t] = 1+depth[parent[t]];
        s.pop();
        for (int x : adj[t]) {
            if (visited[x]) continue;
            parent[x] = t;
            childs[t].push_back(x);
            visited[x] = true;
            s.push(x);
        }
    }
    return {childs,parent};
}

typedef multiset<int>* P;

P merge(P p1, P p2) {
    if (p1->size() < p2->size()) {
        swap(p1,p2);
    }
    for (int i : (*p2)) p1->insert(i);
    return p1;
}

// remove all elts with D >= d
inline int remD(P s, int d) {
    auto it = s->lower_bound(d);
    int ct = 0;
    auto it2(it);
    while (it != s->end()) {
        ++ct;
        advance(it,1);
    }
    s->erase(it2,s->end());
    return ct;
}

pair<P,int> balance(int t, VVI& chd) {
    if (sz(chd[t]) == 0) {
        // leaf node
        P s = new multiset<int>();
        s->insert(depth[t]);
        dbg(t+1,0,"l");
        return {s,0};
    } else if (sz(chd[t]) == 1) {
        auto [s,A] = balance(chd[t][0],chd);
        s->insert(depth[t]);
        int z = remD(s,depth[t]+2);
        dbg(t+1,A+z,"1");
        return {s,A+z};
    } else {
        auto [s1,A1] = balance(chd[t][0],chd);
        auto [s2,A2] = balance(chd[t][1],chd);
        int A = A1+A2;
        int md1 = *(--(s1->end()));
        int md2 = *(--(s2->end()));
        if (md1 < md2) {
            A += remD(s2, md1+2);
        } else {
            A += remD(s1, md2+2);
        }
        dbg(t+1,A,"2");
        P s = merge(s1,s2);
        s->insert(depth[t]);
        return {s,A};
    }
}

void run() {
    int n; cin >> n;
    VVI adj(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    depth.resize(n);
    auto [chd, par] = rootTree(adj, 0);
    dbg(depth);
    auto [s,a] = balance(0,chd);
    print(a);
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