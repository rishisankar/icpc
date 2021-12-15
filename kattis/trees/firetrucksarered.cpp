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

    int n; cin >> n;
    vector<vector<pair<int, int>>> adj(n);

    unordered_map<int, int> ma;
    REP(i, n) {
        int m; cin >> m;
        REP(j, m) {
            int tmp; cin >> tmp;
            if (ma.find(tmp) != ma.end()) {
                int tmp2 = ma.find(tmp)->second;
                adj[i].push_back({tmp2, tmp});
                adj[tmp2].push_back({i, tmp});
            } else {
                ma.insert({tmp, i});
            }
        }
    }

    VS proofs;
    VB visited(n, false);
    visited[0] = true;
    stack<int> s;
    s.push(0);
    while(!s.empty()) {
        int t = s.top();
        s.pop();
        for (pair<int,int> pa : adj[t]) {
            int a = pa.first;
            int w = pa.second;
            if (!visited[a]) {
                s.push(a);
                visited[a] = true;
                string st = to_string(t+1) + " " + to_string(a+1) + " " + to_string(w);
                proofs.push_back(st);
            }
        }
    }
    if (proofs.size() != n-1) {
        cout << "impossible\n";
    } else {
        for (string st : proofs) {
            cout << st << '\n';
        }
    }

}