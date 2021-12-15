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

void fail() {
    cout << "invalid\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    VVB grid(8, VB(8, false));

    int numQueens = 0;

    REP(i, 8) {
        string st;
        cin >> st;
        REP(j, 8) {
            grid[i][j] = (st.at(j) == '*');
            if (grid[i][j]) numQueens++;
        }
    }

    if (numQueens != 8) fail();

    REP(i, 8) {
        int count = 0;
        REP(j, 8) {
            if (grid[i][j]) ++count;
        }
        if (count > 1) {
            fail();
        }
    }

    REP(i, 8) {
        int count = 0;
        REP(j, 8) {
            if (grid[j][i]) ++count;
        }
        if (count > 1) {
            fail();
        }
    }

    for(int i = -16; i < 8; ++i) {
        int count = 0;
        REP(j, 8) {
            if (i+j < 0 || i+j >= 8) continue;
            if (grid[i+j][j]) ++count;
        }
        if (count > 1) {
            fail();
        }
    }

    for(int i = 0; i < 30; ++i) {
        int count = 0;
        REP(j, 8) {
            if (i-j < 0 || i-j >= 8) continue;
            if (grid[i-j][j]) ++count;
        }
        if (count > 1) {
            fail();
        }
    }

    cout << "valid\n";

}