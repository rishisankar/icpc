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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int n, k;
    cin >> n >> k;

    VI pos(n, 0);
    VVS prefs(n);
    REP(i, n) {
        int tmp; cin >> tmp;
        REP(j, tmp) {
            string s; cin >> s;
            prefs[i].PB(s);
        }
    }

    int p; cin >> p;
    VS players(p);
    REP(i, p) {
        cin >> players[i];
    }
    int ppos = 0;

    unordered_set<string> drafted;

    VVS draft(n);

    REP(i, k) {
        REP(j, n) {
            bool found = false;
            while (pos[j] < prefs[j].size()) {
                if (drafted.find(prefs[j][pos[j]]) == drafted.end()) {
                    string res = prefs[j][pos[j]];
                    draft[j].PB(res);
                    drafted.insert(res);
                    found = true;
                    break;
                }
                pos[j]++;
            }
            if (!found) {
                while (true) {
                    if (drafted.find(players[ppos]) == drafted.end()) {
                        string res = players[ppos]; 
                        draft[j].PB(res);
                        drafted.insert(res);
                        found = true;
                        break;
                    }
                    ++ppos;
                }
            }
        }
    }

    REP(i, n) {
        for (string s : draft[i]) {
            cout << s << " ";
        }
        cout << '\n';
    }

}