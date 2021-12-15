// doesn't work!!

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


// To create: DSU d(capacity)
// remember to add elts (between 0 and capacity)
// O(log(n)) complexity for both finds/unions

struct DSU {

    vector<int> parent, rank;
    int sz;

    DSU (int x) {
		parent.resize(x+1);
        rank.resize(x+1);
        sz = 0;
		fill(parent.begin(), parent.end(), -1);
	}

    /**
     * Adds v (in a new set) to the DSU
     */
    void make_set(int v) {
        if (parent[v] == -1) ++sz;
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
        }
    }

    int size() {
        return sz;
    }

    void clear() {
        fill(parent.begin(), parent.end(), -1);
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

    int N; cin >> N;

    int D = 505;

    DSU d(D*D);

    int maxSize = 0;

    REP(i, N) {
        int x,y,w,h; cin >> x >> y >> w >> h;
        ++x; ++y;
        for (int W = x; W < x + w; ++W) {
            for (int H = y; H < y + h; ++H) {
                int pt = W*D+H;
                d.make_set(pt);
                if (d.contains(pt+1)) d.union_sets(pt, pt+1);
                if (d.contains(pt-1)) d.union_sets(pt, pt-1);
                if (d.contains(pt+D)) d.union_sets(pt, pt+D);
                if (d.contains(pt+D+1)) d.union_sets(pt, pt+D+1);
                if (d.contains(pt+D-1)) d.union_sets(pt, pt+D-1);
                if (d.contains(pt-D)) d.union_sets(pt, pt-D);
                if (d.contains(pt-D+1)) d.union_sets(pt, pt-D+1);
                if (d.contains(pt-D-1)) d.union_sets(pt, pt-D-1);
                maxSize = max(maxSize, d.set_size(pt));
            }
        }
    }

    cout << maxSize << '\n';

}