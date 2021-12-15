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

int n,m,e;

int cmp(tuple<int,int,int,int,int>& t) {
    return (get<0>(t) * m + get<1>(t)) * m * n + (get<2>(t) * m + get<3>(t));
}

void run() {
    cin >> n >> m >> e;
    vector<vector<char>> grid(n, vector<char>(m));
    int px, py, cx, cy, ex, ey;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = s.at(j);
            if (grid[i][j] == 'E') {
                ex = i; ey = j;
            } else if (grid[i][j] == 'P') {
                px = i; py = j;
            } else if (grid[i][j] == 'C') {
                cx = i; cy = j;
            }
        }
    }

    // coordinate = (px*m + py)(mn) + (cx*m +cy)
    // t = {px, py, cx, cy}
    vector<bool> visited(m*n*m*n*2, false);
    queue<tuple<int,int,int,int,int>> q;
    q.push({px,py,cx,cy, 0});
    visited[cmp(q.front())] = true;
    while (!q.empty()) {
        tuple<int,int,int,int,int> t = q.front();
        q.pop();

        int plx = get<0>(t);
        int ply = get<1>(t);
        int crx = get<2>(t);
        int cry = get<3>(t);
        int d = get<4>(t);

        if (grid[plx][ply] == 'E') {
            cout << d << '\n';
            return;
        }

        int chd = 1;
        int cvd = 1;
        if (crx > plx) {
            cvd = -1;
        }
        if (cry > ply) {
            chd = -1;
        }
        if (crx == plx) cvd = 0;
        if (cry == ply) chd = 0;
        int ncx = crx + cvd;
        int ncy = cry + chd;
        
        int vd = abs(crx - plx);
        int hd = abs(cry - ply);

        bool hbl = false;
        if (ncy < 0 || ncy >= m || grid[crx][ncy] == 'X') {
            hbl = true;
        }
        bool vbl = false;
        if (ncx < 0 || ncx >= n || grid[ncx][cry] == 'X') {
            vbl = true;
        }

        if (hbl && vbl) {
            ncx = crx;
            ncy = cry;
        }
        else if (hbl) {
            ncy = cry;
        } else if (vbl) {
            ncx = crx;
        } else if (vd < hd) {
            ncx = crx;
        } else if (hd <= vd) {
            ncy = cry;
        }

        vector<pair<int,int>> dirs;
        dirs.push_back({0,1});
        dirs.push_back({0,-1});
        dirs.push_back({1,0});
        dirs.push_back({-1,0});
        dirs.push_back({0,0});
        for (pair<int,int> dir : dirs) {
            int npx = plx + dir.first;
            int npy = ply + dir.second;
            if (npx < 0 || npy < 0 || npx >= n || npy >= m || grid[npx][npy] == 'X') {
                continue;
            }
            if (abs(ncy-npy) <= e && abs(ncx-npx) <= e) {
                continue;
            }
            tuple<int,int,int,int,int> newt = {npx,npy,ncx,ncy,d+1};
            int res = cmp(newt);
            if (visited[res]) continue;
            visited[res] = true;
            q.push(newt);
        }

    }

    cout << "you're toast\n";

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