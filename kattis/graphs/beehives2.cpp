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

int n,m;

int shortest_cycle(int n, vector<vector<int>>& adj) {
    int res = INT_MAX;

    for (int i = 0; i < n; ++i) {
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n);
        queue<int> q;
        dist[i] = 0;
        parent[i] = i;
        q.push(i);
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            for (int a : adj[t]) {
                if (dist[a] == INT_MAX) {
                    dist[a] = dist[t] + 1;
                    parent[a] = t;
                    q.push(a);
                } else {
                    if (parent[t] != a && parent[a] != t) {
                        res = min(res, dist[t] + dist[a] + 1);
                    }
                }
            }
        }
    }
    
    return (res == INT_MAX) ? -1 : res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    cin >> n >> m;
    VVI adj(n);
    REP(i, m) {
        int a,b; cin >> a >> b;
        adj[a].PB(b);
        adj[b].PB(a);
    }

    int minCycle = shortest_cycle(n, adj);

    if (minCycle == -1) cout << "impossible\n";
    else cout << minCycle << '\n';

}