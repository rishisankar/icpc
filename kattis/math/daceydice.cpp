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

void run() {
    int n; cin >> n;
    vector<vector<char>> grid(n, vector<char>(n));
    int sx = -1;
    int sy = -1;
    int gx = -1;
    int gy = -1;
    REP(i, n) {
        string s; cin >> s;
        REP(j, n) {
            grid[i][j] = s.at(j);
            if (grid[i][j] == 'H') {
                gx = i;
                gy = j;
                grid[i][j] = '.';
            } else if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
                grid[i][j] = '.';
            }
        }
    }

    vector<vector<vector<vector<bool>>>> visited(n, vector<vector<vector<bool>>>(n, VVB(7, VB(7, false))));

    stack<tuple<int,int,int,int>> s;
    s.push({sx, sy, 1, 5});
    visited[sx][sy][1][5] = true;

    VVI rg(7, VI(7));
    VVI left(7, VI(7));
    VVI top(7, VI(7));
    VVI dn(7, VI(7));
    rg[1][5] = 3;
    rg[1][3] = 2;
    rg[1][2] = 4;
    rg[1][4] = 5;
    left[1][5] = 4;
    left[1][4] = 2;
    left[1][2] = 3;
    left[1][3] = 5;

    rg[2][1] = 3;
    rg[2][3] = 6;
    rg[2][6] = 4;
    rg[2][4] = 1;
    left[2][1] = 4;
    left[2][4] = 6;
    left[2][6] = 3;
    left[2][3] = 1;

    rg[3][5] = 6;
    rg[3][6] = 2;
    rg[3][2] = 1;
    rg[3][1] = 5;
    left[3][5] = 1;
    left[3][1] = 2;
    left[3][2] = 6;
    left[3][6] = 5;



    while (!s.empty()) {
        tuple<int,int,int,int> t = s.top();
        s.pop();
        int x = get<0>(t);
        int y = get<1>(t);
        int tp = get<2>(t);
        int lf = get<3>(t);
        //dbg("stack entry:", x, y, tp, lf);

        if (x == gx && y == gy) {
            if ((tp == 1 && lf == 4) || (tp == 3 && lf == 1) || (tp == 6 && lf == 3) || (tp == 4 && lf == 6)) {
                print("Yes");
                return;
            }
        }

        int nx, ny, nt, nl;

        // go right:
        ny = y+1;
        nx = x;
        nt = tp;
        if (tp == 1 || tp == 2 || tp == 3) {
            nl = rg[tp][lf];
        } else {
            nl = left[7-tp][lf];
        }
        if (ny >= 0 && ny < n && nx >= 0 && nx < n && (!visited[nx][ny][nt][nl])) {
            if (grid[nx][ny] != '*') {
                s.push({nx,ny,nt,nl});
                visited[nx][ny][nt][nl] = true;
            }
        }

        // go left:
        ny = y-1;
        nx = x;
        nt = tp;
        if (tp == 1 || tp == 2 || tp == 3) {
            nl = left[tp][lf];
        } else {
            nl = rg[7-tp][lf];
        }
        if (ny >= 0 && ny < n && nx >= 0 && nx < n && (!visited[nx][ny][nt][nl])) {
            if (grid[nx][ny] != '*') {
                s.push({nx,ny,nt,nl});
                visited[nx][ny][nt][nl] = true;
            }
        }

        // go up:
        ny = y;
        nx = x-1;
        nl = lf;
        if (lf == 1 || lf == 2 || lf == 3) {
            nt = rg[lf][tp];
        } else {
            nt = left[7-lf][tp];
        }
        if (ny >= 0 && ny < n && nx >= 0 && nx < n && (!visited[nx][ny][nt][nl])) {
            if (grid[nx][ny] != '*') {
                s.push({nx,ny,nt,nl});
                visited[nx][ny][nt][nl] = true;
            }
        }

        // go down:
        ny = y;
        nx = x+1;
        nl = lf;
        if (lf == 1 || lf == 2 || lf == 3) {
            nt = left[lf][tp];
        } else {
            nt = rg[7-lf][tp];
        }
        if (ny >= 0 && ny < n && nx >= 0 && nx < n && (!visited[nx][ny][nt][nl])) {
            if (grid[nx][ny] != '*') {
                s.push({nx,ny,nt,nl});
                visited[nx][ny][nt][nl] = true;
            }
        }

    }

    print("No");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    ll t; cin >> t;
    //ll t=1;
    REP(tests,t) run();
}