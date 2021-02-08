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

    int n, m;
    cin >> n >> m;
    VVI adj(n);
    VI colors(n, -1); // colors: 0 (no lounge) or 1 (lounge)

    stack<pair<int,int>> coloring;

    int count = 0;

    REP(i, m) {
        int a,b,c;
        cin >> a >> b >> c;
        --a; --b;
        if (c == 0) {
            coloring.push({a, 0});
            coloring.push({b, 0});
        } else if (c == 2) {
            coloring.push({a, 1});
            coloring.push({b, 1});
        } else {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    while (!coloring.empty()) {
        int t = coloring.top().first;
        int c = coloring.top().second;
        coloring.pop();
        if (colors[t] != -1) {
            if (colors[t] != c) {
                cout << "impossible\n";
                return 0;
            }
        } else {
            colors[t] = c;
            if (c == 1) ++count;
            int nc = (c+1)%2;
            for (int a : adj[t]) {
                coloring.push({a, nc});
            }
        }
    }

    REP(i, n) {
        if (colors[i] == -1) {
            int zeroes = 0;
            int ones = 0;
            coloring.push({i,0});
            while (!coloring.empty()) {
                int t = coloring.top().first;
                int c = coloring.top().second;
                coloring.pop();
                if (colors[t] != -1) {
                    if (colors[t] != c) {
                        cout << "impossible\n";
                        return 0;
                    }
                } else {
                    colors[t] = c;
                    if (c == 0) ++zeroes; else ++ones;
                    int nc = (c+1)%2;
                    for (int a : adj[t]) {
                        coloring.push({a, nc});
                    }
                }
            }
            count += min(zeroes, ones);
        }
    }

    cout << count << '\n';

}