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

ll n, m;

// d: 0, 1, 2, 3, 4 (4 = no dir, 0 = 0 deg)
ll dir(ll i, ll j, ll d) {
    return d + 5*i + 5*n*j;
}

vector<vector<int>> adj_rev;

vector<bool> winning;
vector<bool> losing;
vector<bool> visited;
vector<int> degree;

void dfs(int v) {
    ll ei = (v%(5*n)) / 5;
    ll ej =  v/(5*n);
    ll ed = v%5;
    // dbg("dfs", ei, ej, ed,winning[v], losing[v]);
    visited[v] = true;
    for (int u : adj_rev[v]) {
        if (!visited[u]) {
            if (losing[v])
                winning[u] = true;
            else if (--degree[u] == 0)
                losing[u] = true;
            else
                continue;
            dfs(u);
        }
    }
}

void run() {
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    int lx, ly;
    REP(i, n) {
        string s;
        cin >> s;
        REP(j, m) {
            v[i][j] = s[j];
            if (s[j] == 'L') {
                lx = i;
                ly = j;
            }
        }
    }

    int N = 5*n*m;
    adj_rev.assign(N, vector<int>(0));
    winning.assign(N, false);
    losing.assign(N, false);
    visited.assign(N, false);
    degree.assign(N, 0);

    VPII dirs = {{0,1},{-1,0},{0,-1},{1,0}};

    REP(i, n) {
        REP(j, m) {
            REP(k, 4) {
                adj_rev[dir(i,j,k)].PB(dir(i,j,4));
                ++degree[dir(i,j,4)];
            }
            REP(l, 4) {
                REP(k, 4) {
                    if (l == k) continue;

                    int nx = i + dirs[k].first;
                    int ny = j + dirs[k].second;
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m || v[nx][ny] == '#') {
                        continue;
                    }

                    adj_rev[dir(nx,ny,4)].PB(dir(i,j,l));
                    ++degree[dir(i,j,l)];
                }
            }
        }
    }

    // for (int a : adj_rev[dir(lx,ly,4)]) {
    //     ll ei = (a%(5*n)) / 5;
    //     ll ej =  a/(5*n);
    //     ll ed = a%5;
    //     dbg(ei,ej,ed);
    // }

    winning[dir(lx,ly,4)] = true;
    dfs(dir(lx,ly,4));



    REP(i, n) {
        REP(j, m) {
            if (v[i][j] != '.') {
                cout << v[i][j];
            } else {
                int x = dir(i,j,4);
                if (visited[x] && winning[x]) {
                    cout << '+';
                } else {
                    cout << '.';
                }
            }
        }
        cout << '\n';
    }


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    ll t; cin >> t;
    // ll t=1;
    REP(tests,t) run();
}