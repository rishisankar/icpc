#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
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
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; print(args...); }

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


const int INF = 1000000000;
void dijkstra(int s, vector<int> & d, vector<int> & p, VVPII &adj) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

void run() {

    VPII dirs = {{1,0}, {0,1}, {-1,0}, {0,-1}};

    int r,c; cin >> r >> c;
    VVI inp(r, VI(c));
    REP(i, r) {
        string s;
        cin >> s;
        REP(j, c) {
            if (s[j] == '#') {
                inp[i][j] = -1;
            } else if (s[j] == 'c') {
                inp[i][j] = 1;
            } else {
                inp[i][j] = 0;   
            }
        }
    }

    int x,y; cin >> x >> y;
    VVPII adj(r*c);
    REP(i, r) {
        REP(j, c) {
            if (inp[i][j] == -1) continue;
            int node = i*c+j;
            for (PII p : dirs) {
                int ni = p.first + i;
                int nj = p.second + j;
                if (ni < 0 || nj < 0 || ni >=r || nj >= c) continue;
                if (inp[ni][nj] == -1) continue;
                adj[node].PB({ni*c+nj,inp[ni][nj]});
            }
        }
    }

    VI d,p;
    --x; --y;
    dijkstra(x*c+y, d, p, adj);

    VPII border;
    for (int i = 0; i < r; ++i) {
        border.PB({i, 0});
        if (c != 1) border.PB({i,c-1});
    }
    for (int i = 1; i < c-1; ++i) {
        border.PB({0,i});
        if (r != 1) border.PB({r-1,i});
    }
    int best = INT_MAX;
    for (PII p : border) {
        if (inp[p.first][p.second] == -1) continue;
        int nd = p.first * c + p.second;
        best = min(best, d[nd]);
    }
    print(best+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}