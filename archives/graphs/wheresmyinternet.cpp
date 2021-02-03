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

    int n, m; cin >> n >> m;
    VVI adj(n+1);
    REP(i,m) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    VB visited(n+1, false);
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int t = q.front(); q.pop();
        if (visited[t]) continue;
        visited[t] = true;
        for (int a : adj[t]) {
            q.push(a);
        }
    }

    bool connected = true;
    OREP(i, n) {
        if (!visited[i]) {connected=false; break;}
    }
    if (connected) {
        cout << "Connected\n";
    } else {
        OREP(i, n) {
            if (!visited[i]) cout << i << "\n";
        }
    }

}