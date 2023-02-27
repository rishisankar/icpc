#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define REP(i, j) FOR(i, 0, j)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define mp make_pair
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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
vector<ll> arm;
struct Graph {
  int n,m;
  bool isDirected;
  vector<vector<int>> adj;
  Graph(int n, int m, bool isDirected=false)
    : n(n), m(m), isDirected(isDirected) {
    adj.resize(n);
  }

  void addEdge(int a, int b) {
    if (!isDirected) adj[b].push_back(a);
    adj[a].push_back(b);
  }

  void readEdges(bool zeroIndexed) {
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (!zeroIndexed) {
            --a; --b;
        }
        addEdge(a,b);
    }
  }

  void dfs(int start, function<bool(int)> fn) {
    vector<bool> vis(n, false);
    auto comp = [&](int i1, int i2) {return arm[i1]>arm[i2];};
    priority_queue<int,vector<int>,decltype(comp)> st(comp);
    st.push(start);
    vis[start] = true;
    while (!st.empty()) {
        int t = st.top();
        st.pop();
        if (fn(t)) {
            for (int a : adj[t]) {
                if (vis[a]) continue;
                st.push(a);
                vis[a] = true;
            }
        }
    }
  }
};

void run() {
    int n,m; cin >> n >> m;
    Graph g(n,m);
    g.readEdges(false);
    arm.resize(n);
    INP(arm,n);
    g.dfs(0, [&](int x) {
        if (x==0)return true;
        if (arm[x] < arm[0]) {
            arm[0] += arm[x];
            return true;
        }
        return false;
    });
    print(arm[0]);
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