#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }

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
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

void finish_time_dfs(int vertex, vector<vector<int>>& adj_list, vector<bool>& visited, stack<int>& s) {
    if (visited[vertex]) return;
    visited[vertex] = true;

    for (int i = 0; i < adj_list[vertex].size(); ++i) {
        finish_time_dfs(adj_list[vertex][i], adj_list, visited, s);
    }

    s.push(vertex);
}

void reverse_dfs(int vertex, vector<vector<int>>& adj_list, int scc_count, vector<bool>& visited, vector<vector<int>>& result) {
    if (visited[vertex]) return;
    visited[vertex] = true;
    result[scc_count].push_back(vertex);

    for (int i = 0; i < adj_list[vertex].size(); ++i) {
        reverse_dfs(adj_list[vertex][i], adj_list, scc_count, visited, result);
    }
}

int kosaraju(vector<vector<int>>& adj_list, vector<vector<int>>& result) {
    int N = adj_list.size();
    if (N == 0) return 0;

    stack<int> s;
    vector<bool> visited(N, false);
    for (int i = 0; i < N; ++i) {
        finish_time_dfs(i, adj_list, visited, s);
    }

    // reverse adj list
    vector<vector<int>> transpose(N);
    for (int i = 0; i < N; ++i) {
        for (int j : adj_list[i]) {
            transpose[j].push_back(i);
        }
    }

    fill(visited.begin(), visited.end(), false);
    result.resize(N);
    int scc_count = 0;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (visited[v]) continue;
        reverse_dfs(v, transpose, scc_count, visited, result);
        ++scc_count;
    }
    result.resize(scc_count);

    return scc_count;
    
}

int geti(int i) {
    int res = abs(i) * 2;
    if (i < 0) ++res;
    return res;
}

void fail() {
    cout << "NO\n";
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int n, m;
    cin >> n >> m;

    VVI result;
    VVI adj(2*m+2);

    REP(i, n) {
        int a,b;
        cin >> a >> b;

        adj[geti(-a)].PB(geti(b));
        adj[geti(-b)].PB(geti(a));
    }

    kosaraju(adj, result);

    for (VI v : result) {
        sort(all(v));
        int prev = -1;
        for (int i : v) {
            if (i%2 == 1 && prev == i-1) {
                fail();
            }
            prev = i;
        }
    }
    cout << "YES\n";

}