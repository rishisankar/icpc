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

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

typedef long long ll;
typedef long double ld;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    vector<VVB> wins(501, VVB(501, VB(2, false)));
    OREP(i, 500) {
        OREP(j, 500) {
            if (i == j) continue;
            else if (j < i) {
                wins[i][j][0] = wins[j][i][1];
                wins[i][j][1] = wins[j][i][0];
            } else {
                if (i == 1) {
                    wins[i][j][0] = true;
                } else if (wins[i][j-1][0]) {
                    wins[i][j][0] = true;
                } else {
                    for (int k = 1; k < j; ++k) {
                        if ((!wins[i][k][1]) && (!wins[i][j-k][1])) {
                            wins[i][j][0] = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    int N;
    cin >> N;

    REP(i,N) {
        int b,a; cin >> b >> a;
        string s; cin >> s;
        int index = 0;
        if (s == "Harry") index = 1;
        cout << s;
        if (wins[a][b][index]) {
            cout << " can win\n";
        } else {
            cout << " cannot win\n";
        }

    }

}