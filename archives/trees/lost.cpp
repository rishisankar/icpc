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

    int n, m; cin >> n >> m;

    unordered_map<string, int> languages;
    languages.insert({"English", 0});
    REP(i, n) {
        string tmp; cin >> tmp;
        languages[tmp] = i+1;
    }
    
    ++n; // include english
    VVI matrix(n, VI(n, 0));
    REP(i, m) {
        string s1, s2;
        cin >> s1 >> s2;
        int cost; cin >> cost;
        int i1, i2;
        i1 = languages[s1];
        i2 = languages[s2];
        matrix[i1][i2] = cost;
        matrix[i2][i1] = cost;
    }

    int totalCost = 0;
    int totalVisited = 1;
    VB visited(n, false);
    visited[0] = true;
    vector<int> v;
    v.PB(0);

    while(totalVisited < n) {
        if (v.empty()) {
            cout << "Impossible\n";
            return 0;
        }
        VI curCost(n, INT_MAX);
        REP(i, n) {
            if (visited[i]) continue;
            for (int j : v) {
                if (matrix[i][j]) {
                    curCost[i] = min(curCost[i], matrix[i][j]);
                }
            }
        }
        v.clear();
        REP(i, n) {
            if (curCost[i] != INT_MAX) {
                visited[i] = true;
                ++totalVisited;
                v.PB(i);
                totalCost += curCost[i];
            }
        }
    }

    cout << totalCost << '\n';



}