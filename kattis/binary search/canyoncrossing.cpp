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

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}

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

VVLL grid;
int r,c,k;

void getneighbors(int x, int y, VPII& neighbors) {
    if (x+1 < r) neighbors.PB({x+1,y});
    if (x-1 >= 0) neighbors.PB({x-1, y});
    if (y+1 < c) neighbors.PB({x,y+1});
    if (y-1 >= 0) neighbors.PB({x,y-1});
}

bool test(ll h) {
    VVLL best(r, VLL(c, LLONG_MAX));
    queue<PII> q;
    REP(i, c) {
        best[0][i] = grid[0][i] >= h ? 0 : 1;
        if (k >= best[0][i]) q.push({0,i});
    }
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        VPII neighbors;
        getneighbors(x,y,neighbors);
        for (PII neighbor : neighbors) {
            ll poss = grid[neighbor.first][neighbor.second] >= h ? best[x][y] : best[x][y]+1;
            if (poss < best[neighbor.first][neighbor.second]) {
                best[neighbor.first][neighbor.second] = poss;
                if (k >= poss) q.push({neighbor.first, neighbor.second});
            }
        }
    }
    REP(i, c) {
        if (best[r-1][i] <= k) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    cin >> r >> c >> k;
    grid.resize(r,VLL(c));
    REP(i, r) REP(j, c) cin >> grid[i][j];

    ll minh = 0;
    ll maxh = 1e9;

    while(minh < maxh) {
        ll mid = (minh+maxh+1)/2;
        if (test(mid)) minh = mid;
        else maxh = mid-1;
    }

    cout << minh << '\n';

}