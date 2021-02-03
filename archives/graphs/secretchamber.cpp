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
#define all(cont) cont.begin(), cont.end()

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

typedef long long ll;
typedef long double ld;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;

void dfs(int i, vector<vector<int>> &adj, vector<bool>& visited, vector<bool> &tran) {
    if (visited[i]) return;
    tran[i] = true;
    visited[i] = true;
    for (int j : adj[i]) {
        if (!visited[j]) {
            dfs(j, adj, visited, tran);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int m,n; cin >> m >> n;

    vector<vector<int>> adj(26);
    REP(i, m) {
        char c1, c2;
        cin >> c1 >> c2;
        int a1 = c1 - 'a';
        int a2 = c2 - 'a';
        adj[a1].push_back(a2);
    }

    vector<vector<bool>> tran(26, vector<bool>(26, false));
    REP(i, 26) {
        vector<bool> visited(26, false);
        dfs(i, adj, visited, tran[i]);
    }

    REP(i, n) {
        string s, f;
        cin >> s >> f;
        if (s.size() != f.size()) {
            cout << "no\n"; continue;
        }
        bool works = true;
        REP(j, s.size()) {
            int a = s.at(j) - 'a';
            int b = f.at(j) - 'a';
            if (!tran[a][b]) works = false;
        }
        if (works) cout << "yes\n"; else cout << "no\n";
    }


}