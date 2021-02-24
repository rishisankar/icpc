// Sprague-Grundy theorem (nim)

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int P, K;
    cin >> P >> K;

    VI piles(P); // grundy number of top of each pile, will eventually take xor

    REP(p, P) {
        int N; cin >> N;
        VI cards(N);
        REP(i, N) { cin >> cards[i]; }
        VI grundy(N+1); // index refers to number of things left on the pile
        grundy[0] = 0; // if nothing left on pile, nothing can be done
        REP(i, N) {
            VB mex_list(15, false);
            REP(j, min(K+1, i+1)) {
                int left = i + 1 - j - cards[i-j];
                if (left >= 0 && grundy[left] < 15) {
                    mex_list[grundy[left]] = true;
                }
            }
            int mex = 0;
            REP(j, 15) {
                if (!mex_list[j]) {
                    mex = j; break;
                }
            }
            grundy[i+1] = mex;
        }
        piles[p] = grundy[N];
    }

    int xorsum = 0;
    REP(i, P) {
        xorsum ^= piles[i];
    }

    if (xorsum == 0) {
        cout << "Bob will win.\n";
    } else {
        cout << "Alice can win.\n";
    }

}