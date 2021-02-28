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
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    ld tf, tr;
    cin >> tf >> tr;

    vector<int> history;
    ld s;
    cin >> s;
    history.PB(0);

    while (cin >> s) {
        int i = (int) s;
        int j = i+1;
        if (s < 1 && s > 0) {
            history.PB(1);
        } else if (s >= i && s < i+tf) {
            history.PB(i);
        } else if (s > i+tr && s < j) {
            history.PB(j);
        } else {
            for (int k = history.size() - 1; k >= 0; --k) {
                int l = history[k];
                if (l < i+tf) {
                    history.PB(i);
                    break;
                } else if (l > i+tr) {
                    history.PB(j);
                    break;
                }
            }
        }
    }

    for (int i : history) {
        cout << i << '\n';
    }

}