#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(cont) cont.begin(), cont.end()
#define PB push_back

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
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;

const int N = 10000;

VVI pos(N+1, VI(2));
int x, y, cur;

int maxx, maxy;

VI ct(5, 0);

void load() {
    ++cur;
    if (cur > N) return;
    pos[cur][0] = x;
    pos[cur][1] = y;
    maxx = max(maxx, x); maxy = max(maxy, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    pos[1][0] = 1000;
    pos[1][1] = 1000;
    int rad = 0;
    cur = 1;
    x = 1000;
    y = 1000;

    maxx = 0; maxy = 0;

    while (cur <= N) {
        ++rad;
        
        REP(i, rad) {
            ++x; load();
        }

        REP(i, rad-1) {
            ++y; load();
        }

        REP(i, rad) {
            --x; ++y; load();
        }

        REP(i, rad) {
            --x; load();
        }

        REP(i, rad) {
            --y; load();
        }

        REP(i, rad) {
            --y; ++x; load();
        }
    }

    //cout << maxx << " " << maxy << '\n';
    //cout << pos[13][0] << " " << pos[13][1] << '\n';

    VVI grid(2000, VI(2000, -1)); //origin: (1000, 1000) - could be wayy smaller, grid only really needs to be ~400 x 400

    VI table(10001);
    OREP(i, 10000) {
        VB allowed(5, true);
        int px = pos[i][0];
        int py = pos[i][1];
        int var;
        if ((var = grid[px+1][py]) != -1) { allowed[var] = false; }
        if ((var = grid[px][py+1]) != -1) { allowed[var] = false; }
        if ((var = grid[px-1][py+1]) != -1) { allowed[var] = false; }
        if ((var = grid[px-1][py]) != -1) { allowed[var] = false; }
        if ((var = grid[px][py-1]) != -1) { allowed[var] = false; }
        if ((var = grid[px+1][py-1]) != -1) { allowed[var] = false; }

        int best = -1;
        int bestC = INT_MAX;
        REP(j, 5) {
            if (allowed[j] && ct[j] < bestC) {
                best = j;
                bestC = ct[j];
            }
        }

        grid[px][py] = best;
        table[i] = best+1;
        ++ct[best];
    }


    int c; cin >> c;
    REP(tests,c) {
        int n;
        cin >> n;
        cout << table[n] << '\n';
    }

}
