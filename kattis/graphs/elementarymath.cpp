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
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

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

// Hopcroft-Karp-Karzanov algorithm for maximum bipartite matching

// IMPORTANT: number vertices starting with 1, vertex 0 is reserved for use by algorithm

// main function: hopcroftkarp(adj_list, matches, L, R)
// adj_list (size L+1) should represent connected vertices in right set for each in set 1
// L = size of set 1, R = size of set 2
// matches (size L+1) will contain final match of each vertex in left set (or 0 if no match).

// source: https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
// time: O(sqrt(V)*E)

// examples: graphs/bookclub_hkk, graphs/historicexhibition

// checks if there is an augmenting path, update distances for later reference by dfs
bool hkk_bfs(vector<vector<int>>& adj_list, int L, int R, vector<int>& left_match, vector<int>& right_match, vector<int>& dist) {
    queue<int> q;

    // setup queue and initialize distances
    for (int i = 1; i <= L; ++i) {
        if (left_match[i] == 0) {
            dist[i] = 0;
            q.push(i);
        } else {
            dist[i] = INT_MAX;
        }
    }
    dist[0] = INT_MAX;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] < dist[0]) {
            for (int v : adj_list[u]) {
                int cur_match = right_match[v];
                if (dist[cur_match] == INT_MAX) {
                    dist[cur_match] = dist[u] + 1;
                    q.push(cur_match);
                }
            }
        }
    }

    return dist[0] != INT_MAX;

}

bool hkk_dfs(int u, vector<vector<int>>& adj_list, vector<int>& left_match, vector<int>& right_match, vector<int>& dist) {
    if (u == 0) return true;

    for (int v : adj_list[u]) {
        int cur_match = right_match[v];
        if (dist[cur_match] == dist[u] + 1) {
            if (hkk_dfs(cur_match, adj_list, left_match, right_match, dist)) {
                left_match[u] = v;
                right_match[v] = u;
                return true;
            }
        }
    }

    dist[u] = INT_MAX;
    return false;
}

int hopcroftkarp(vector<vector<int>>& adj_list, vector<int>& matches, int L, int R) {
    vector<int> left_match(L+1, 0);
    vector<int> right_match(R+1, 0);
    vector<int> dist(L+1, 0); // dist along an augmenting path (calculated using bfs)

    int total = 0;

    while (hkk_bfs(adj_list, L, R, left_match, right_match, dist)) {
        for (int i = 1; i <= L; ++i) {
            if (left_match[i] == 0 && hkk_dfs(i, adj_list, left_match, right_match, dist)) {
                ++total;
            }
        }
    }

    for (int i = 1; i <= L; ++i) {
        if (left_match[i] != 0 && right_match[left_match[i]] == i) {
            matches[i] = left_match[i];
        } else {
            matches[i] = 0;
        }
    }

    return total;
}

void run() {
    vector<pair<ll,ll>> qs;
    vector<ll> ans;
    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    int ct = 0;
    unordered_map<ll,int> vals;
    REP(i, n) {
        ll a,b; cin >> a >> b;
        qs.PB({a,b});
        unordered_set<ll> poss = {a+b, a*b, a-b};
        for (ll v : poss) {
            if (vals.count(v)) continue;
            vals[v] = ct;
            ans.PB(v);
            ++ct;
        }
        for (ll v : poss) {
            adj[i+1].PB(vals[v]+1);
        }
    }
    vector<int> matches(n+1);


    int res = hopcroftkarp(adj, matches, n, ct);
    if (res != n) {
        print("impossible");
        return;
    }
    OREP(i, n) {
        pair<ll,ll> q = qs[i-1];
        ll eq = ans[matches[i]-1];
        if (q.first + q.second == eq) {
            print(q.first,'+',q.second,'=',eq);
        } else if (q.first * q.second == eq) {
            print(q.first,'*',q.second,'=',eq);
        } else {
            print(q.first,'-',q.second,'=',eq);
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}