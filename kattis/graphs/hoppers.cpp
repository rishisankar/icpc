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

struct DSU {

    vector<int> parent, rank;
    int elts;
    int sz;

    DSU (int x) {
		parent.resize(x+1);
        rank.resize(x+1);
        elts = 0;
        sz = 0;
		fill(parent.begin(), parent.end(), -1);
	}

    /**
     * Adds v (in a new set) to the DSU
     */
    void make_set(int v) {
        if (parent[v] == -1) { ++elts; ++sz; }
        parent[v] = v;
        rank[v] = 1;
    }

    /**
     * Finds the sets containing v
     */
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    /**
     * Unions the sets containing elements a and b
     */
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            rank[a] += rank[b];
            --sz;
        }
    }

    int elements() {
        return elts;
    }

    int size() {
        return sz;
    }

    void clear() {
        fill(parent.begin(), parent.end(), -1);
        elts = 0;
        sz = 0;
    }

    /**
     * Adds all integers in (inclusive) range [first, last] to DSU
     */
    void add_range(int first, int last) {
        for (int i = first; i <= last; ++i) {
            make_set(i);
        }
    }

    /**
     * Returns size of the set containing v (assuming in v)
     */
    int set_size(int v) {
        return rank[find_set(v)];
    }

    bool contains(int v) {
        return parent[v] != -1;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int N, M;
    cin >> N >> M;

    VVI adj(N);
    REP(i, M) {
        int a1,b1;
        cin >> a1 >> b1;
        --a1; --b1;
        adj[a1].push_back(b1);
        adj[b1].push_back(a1);
    }

    DSU x(N);
    x.add_range(0, N-1);
    REP(i, N) {
        for (int j = 1; j < adj[i].size(); ++j) {
            x.union_sets(adj[i][j-1], adj[i][j]);
        }
    }

    int count = 0;
    unordered_map<int, int> found;

    REP(i, N) {
        int tmp = x.find_set(i);
        if (found.find(tmp) == found.end()) {
            found.insert({tmp, count});
            ++count;
        }
    }

    int connections = 0;
    VB connected(count, false);

    REP(i, N) {
        int tmp1 = x.find_set(i);
        for (int j : adj[i]) {
            int tmp2 = x.find_set(j);
            if (tmp1 != tmp2) {
                int t1 = found.find(tmp1)->second;
                int t2 = found.find(tmp2)->second;
                if (connected[t1]) continue;
                ++connections;
                connected[t1] = true;
                connected[t2] = true;
            }
        }
    }

    bool foundOddCycle = false;
    VI colors(N,0);
    for (auto it : found) {
        int start = it.first;
        stack<pair<int,int>> s;
        s.push({start,1});
        while(!s.empty()) {
            int t = s.top().first;
            int c = s.top().second;
            s.pop();
            if (colors[t] != 0) {
                if (colors[t] != c) {
                    foundOddCycle = true;
                    break;
                }
            } else {
                colors[t] = c;
                int nc = (c%2)+1;
                for (int a : adj[t]) {
                    if (x.find_set(a) != start) continue;
                    s.push({a, nc});
                }
            }
        }
        if (foundOddCycle) break;
    }

    int res = count - connections;

    if (foundOddCycle) {
        res -= 1;
    }

    cout << res << '\n';

}