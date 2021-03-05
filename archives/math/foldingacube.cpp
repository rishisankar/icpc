#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)  // for compatibility with kactl
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
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
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; // for compatibility with kactl
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii; // for compatibility with kactl
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

void fail() {
    cout << "cannot fold\n";
    exit(0);
}

void win() {
    cout << "can fold\n";
    exit(0);
}

VVB grid(6,VB(6));
VI r(6, 0);
VI c(6, 0);

bool test() {

    int m = max(maxe(r), maxe(c));

    if (m > 4) {
        fail();
    }

    if (m == 2) {
        win();
    }

    if (m == 4) {
        REP(i, 6) {
            if (r[i] == 4) {
                if (i == 0 || i == 5) fail();
                if (r[i-1] != 1 || r[i+1] != 1) fail();
                win();
            }
        }
    }

    if (m == 3) {
        REP(i, 6) {
            if (r[i] == 3) {
                int fnd = 0;
                bool broken = false;
                for (int j = 0; j < 6; ++j) {
                    if (grid[i][j]) {
                        if (fnd == 2) broken = true;
                        fnd = 1;
                    } else if (!grid[i][j] && fnd == 1) {
                        fnd = 2;
                    }
                }
                if (broken) continue;
                //if (i != 5 && r[i+1] == 3) win();
                // if ((i != 0 && r[i-1] > 2) || (i != 5 && r[i+1] > 2)) {
                //     for (int k = i-1; k <= i+1; ++k) {
                //         if (k < 0 || k > 5) continue;
                //         int found = 0; // 0 = not found, 1 = found, 2 = over
                //         REP(l, 6) {
                //             if (grid[k][l]) {
                //                 if (found == 2) fail();
                //                 found = 1;
                //             } else if (!grid[k][l] && found == 1) {
                //                 found = 2;
                //             }
                //         }
                //     }
                //     win();
                // }
                // if (i == 0 || i == 5) fail()
                REP(j, 6) {
                    if (grid[i][j]) {
                        if (i!=5 && grid[i+1][j] && grid[i+1][j+2]) return false;
                        if (i!=0 && grid[i-1][j] && grid[i-1][j+2]) return false;
                        if (i!=5 && grid[i+1][j] && i+2 < 6 && grid[i+2][j]) return false;
                        if (i!=5 && grid[i+1][j+2] && i+2 < 6 && grid[i+2][j+2]) return false;
                        if (i!=0 && grid[i-1][j] && i-2 >= 0 && grid[i-2][j]) return false;
                        if (i!=0 && grid[i-1][j+2] && i-2 >= 0 && grid[i-2][j+2]) return false;
                        if (i<4) {
                            if ((grid[i+1][j] || grid[i+1][j+2]) && r[i+2] != 0) return false;
                        }
                        if (i>1) {
                            if ((grid[i-1][j] || grid[i-1][j+2]) && r[i-2] != 0) return false;
                        }
                        // if (r[i-1] == 1 && r[i+1] == 1) {
                        //     if (i-2 >= 0 && r[i-2] == 1) {
                        //         if (grid[i-1][j+1]) win(); else fail();
                        //     }
                        //     if (i+2 <= 5 && r[i+2] == 1) {
                        //         if (grid[i+1][j+1]) win(); else fail();
                        //     }
                        // }
                        return true;
                    }
                }
            }
        }
    }

    return true;

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    REP(i, 6) {
        string s; cin >> s;
        REP(j, 6) {
            char c = s.at(j);
            bool b = (c == '#');
            grid[i][j] = b;
        }
    }


    REP(i, 6) {
        REP(j, 6) {
            if (grid[i][j]) ++r[i];
            if (grid[j][i]) ++c[i];
        }
    }

    int mr = maxe(r);
    int mc = maxe(c);

    bool random = true;

    if (mc >= mr) {

        if (mc == mr && mr == 3) {
            random = test();
        }

        VI tmp = c;
        c = r;
        r = tmp;
        for (int i = 1; i < 6; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(grid[i][j], grid[j][i]);
            }
        }
    }

    bool r2 = test();

    if (random && r2) win(); else fail();
}