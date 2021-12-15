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

struct DSU {

    vector<int> parent, rank, highest, amt;
    int elts;
    int sz;

    DSU (int x) {
		parent.resize(x+1);
        rank.resize(x+1);
        highest.resize(x+1);
        amt.resize(x+1);
        elts = 0;
        sz = 0;
		fill(parent.begin(), parent.end(), -1);
	}

    /**
     * Adds v (in a new set) to the DSU
     */
    void make_set(int v, int am) {
        if (parent[v] == -1) { ++elts; ++sz; }
        parent[v] = v;
        rank[v] = 1;
        highest[v] = v;
        amt[v] = am;
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
            highest[a] = max(highest[a], highest[b]);
            amt[a] += amt[b];
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
     * Returns size of the set containing v (assuming in v)
     */
    int set_size(int v) {
        return rank[find_set(v)];
    }

    int set_amt(int v) {
        return amt[find_set(v)];
    }

    int set_highest(int v) {
        return highest[find_set(v)];
    }

    bool contains(int v) {
        return parent[v] != -1;
    }

};

void run() {
    int n,m,q;
    cin >> n >> m >> q;
    vector<pair<ll, bool>> v;

    ll sm = 0;
    REP(i, n) {
        ll x; cin >> x;
        sm += x;
        v.PB({x, true});
    }
    REP(i, m) {
        ll x; cin >> x;
        v.PB({x, false});
    }
    VLL que(q);
    INP(que,q);
    VLL queries = que;
    sort(all(v));
    sort(all(queries));

    vector<PII> gaps;
    DSU dsu(n+m);
    VLL vals(n+m);
    REP(i, n+m) {
        dsu.make_set(i, v[i].second);
        if (v[i].second) {
            vals[i] = v[i].first;
        } else {
            vals[i] = 0;
        }
    }

    REP(i, n+m-1) {
        gaps.PB({v[i+1].first - v[i].first, i});
    }
    sort(all(gaps));

    int ptr = 0;

    VLL pref(n+m);
    pref[0] = v[0].first;
    for (int i = 1; i < n+m; ++i) {
        pref[i] = pref[i-1] + v[i].first;
    }

    unordered_map<int,ll> querymap;
    REP(i, q) {
        int k = queries[i];
        while (ptr < gaps.size() && gaps[ptr].first <= k) {
            int old1 = dsu.find_set(gaps[ptr].second);
            int old2 = dsu.find_set(gaps[ptr].second + 1);
            sm -= vals[old1] + vals[old2];
            dsu.union_sets(old1, old2);
            int hg = dsu.set_highest(old1);
            int at = dsu.set_amt(old1);
            ll nsum = pref[hg];
            if (hg - at >= 0) nsum -= pref[hg-at];
            // REP(ii, at) {
            //     nsum += v[hg-ii].first;
            // }
            sm += nsum;
            vals[dsu.find_set(old1)] = nsum;
            ++ptr;
        }
        querymap[k] = sm;
    }

    REP(i, q) {
        print(querymap[que[i]]);
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