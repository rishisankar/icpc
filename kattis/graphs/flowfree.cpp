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

vector<vector<char>> grid;
unordered_map<char, vector<PII>> mp;
unordered_set<char> vals;
int nc;
vector<PII> dirs = {{-1,0},{1,0}, {0,1}, {0,-1}};

void succeed() {
    print("solvable");
    exit(0);
}

char curColor;
int ct;
bool dfs(int x, int y, int ex, int ey, int amt) {
    if (amt == ct - 1 && ex == x && ey == y) {
        return true;
    }
    grid[x][y] = '*';
    for (PII dir : dirs) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
        cerr.flush();
        if (grid[nx][ny] != curColor) continue;
        bool work = dfs(nx,ny, ex,ey,amt+1);
        if (work) {
            grid[x][y] = curColor;
            return true;
        }
    }
    grid[x][y] = curColor;
    return false;
}

void test(int i, int j) {
    if (i == 4) {
        bool ok = true;
        for (char c : vals) {
            if (c == 'W') continue;
            ct = 0;
            curColor = c;
            REP(a,4) {
                REP(b,4) {
                    if (grid[a][b] == c) ++ct;
                }
            }
            int st = 0;
            bool work = dfs(mp[c][0].first,mp[c][0].second,mp[c][1].first,mp[c][1].second,0);
            if (!work) {
                ok = false;
                break;
            }
        }
        if (ok) succeed();
        return;
    }
    int ni = i; int nj = j+1;
    if (nj == 4) {
        nj = 0; ni++;
    }
    if (grid[i][j] != 'W') {
        test(ni,nj);
    } else {
        grid[i][j] = 'R';
        test(ni,nj);
        grid[i][j] = 'G';
        test(ni,nj);
        grid[i][j] = 'B';
        test(ni,nj);
        if (vals.size() > 4) {
            grid[i][j] = 'Y';
            test(ni,nj);
        }
        grid[i][j] = 'W';
    }
}

void run() {
    grid.resize(4, vector<char>(4));
    REP(i,4) {
        string s; cin >> s;
        REP(j ,4) {
            grid[i][j] = s[j];
            vals.insert(s[j]);
            if (grid[i][j] != 'W') {
                mp[grid[i][j]].PB({i,j});
            }
        }
    }
    test(0,0);
    print("not solvable");
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