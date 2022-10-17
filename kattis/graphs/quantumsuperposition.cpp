#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;


void dfs(int v, vector<int>& ans, VVI& adj, int n, VB& visited) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs(u, ans, adj, n, visited);
    }
    ans.push_back(v);
}

void topological_sort(vector<int>& ans, VVI& adj, int n, VB& visited) {
    visited.assign(n, false);
    ans.clear();
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i, ans, adj, n, visited);
    }
    reverse(ans.begin(), ans.end());
}

void run() {
    int n1, n2, m1, m2;
    cin >> n1 >> n2 >> m1 >> m2;

    vector<vector<int>> a1(n1);
    vector<vector<int>> ra1(n1);
    vector<vector<int>> a2(n2);
    vector<vector<int>> ra2(n2);
    REP(i, m1) {
        int a,b; cin >> a >> b;--a;--b;
        a1[a].push_back(b);
        ra1[b].PB(a);
    }
    REP(i, m2) {
        int a,b; cin >> a >> b;--a;--b;
        a2[a].push_back(b);
        ra2[b].PB(a);
    }
    int q; cin >> q;
    vector<int> ts1, ts2;
    VB visited;
    topological_sort(ts1, a1, n1, visited);
    topological_sort(ts2, a2, n2, visited);
    // printV(ts2);


    vector<unordered_set<int>> d1(n1), d2(n2);
    d1[0].insert(0);
    d2[0].insert(0);
    for (int t : ts1) {
        for (int at : ra1[t]) {
            for (int x : d1[at])
            d1[t].insert(x+1);
        }
        if (t == n1-1) break;
    }
    for (int t : ts2) {
        for (int at : ra2[t]) {
            for (int x : d2[at])
            d2[t].insert(x+1);
        }
        if (t == n2-1) break;
    }

    // for (int X : d1[n1-1]) {
    //     cout << X << ' ';
    // }
    // cout << "\n";
    //     for (int X : d2[n1-1]) {
    //     cout << X << ' ';
    // }
    // cout << "\n";

    REP(i, q) {
        bool valid = false;
        int X; cin >> X;
        for (int a : d1[n1-1]) {
            if (d2[n2-1].find(X-a) != d2[n2-1].end()) {
                valid = true;
                break;
            }
        }
        if (valid) print("Yes");
        else print("No");
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
    REP(tests,t) run();
}