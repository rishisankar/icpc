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

int X, Y;

bool inBounds(int a, int b) {
    return (a >= 0 && b >= 0 && a < X && b < Y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    cin >> Y >> X;
    string skey; cin >> skey;
    int n = skey.size();

    vector<vector<vector<int>>> dp(X, VVI(Y, VI(n+1, INT_MAX)));
    VVI grid(X, VI(Y));
    REP(i, X) {
        string tmp; cin >> tmp;
        REP(j, Y) {
            grid[X-i-1][j] = tmp.at(j) - '0';
        }
    }

    dp[0][0][0] = grid[0][0];

    REP(i, X) {
        REP(j, Y) {
            if (i == 0 && j== 0) continue;

            int x = grid[i][j];
            // cout << x << '\n';

            if (inBounds(i-1, j)) {
                REP(k, n+1) {
                    if (dp[i-1][j][k] != INT_MAX)
                        dp[i][j][k] = dp[i-1][j][k] + x;
                }
            }
            if (inBounds(i, j-1)) {
                REP(k, n+1) {
                    if (dp[i][j-1][k] != INT_MAX)
                        dp[i][j][k] = min(dp[i][j][k], dp[i][j-1][k] + x);
                }
            }

            for (int v = 2; v <= 10; ++v) {
                if (!inBounds(i-v, j)) continue;
                REP(k, n) {
                    if (dp[i-v][j][k] != INT_MAX) {
                        int var = skey.at(k) - '0';
                        if (var == v-1) {
                            dp[i][j][k+1] = min(dp[i][j][k+1], x + dp[i-v][j][k]);
                        }
                    }
                }
            }
            for (int v = 2; v <= 10; ++v) {
                if (!inBounds(i, j-v)) continue;
                REP(k, n) {
                    if (dp[i][j-v][k] != INT_MAX) {
                        int var = skey.at(k) - '0';
                        if (var == v-1) {
                            dp[i][j][k+1] = min(dp[i][j][k+1], x + dp[i][j-v][k]);
                        }
                    }
                }
            }
        }
    }

    // REP(i, X) {
    //     REP(j, Y) {
    //         REP(k, n+1) {
    //             cout << i << " " << j << " " << k << " " << dp[i][j][k] << "\n";
    //         }
    //     }
    // }


    int res = INT_MAX;
    REP(i, n+1) {
        res = min(res, dp[X-1][Y-1][i]);
    }

    cout << res << '\n';

}