#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;


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

typedef pair<int,int> T;

tree < T ,  null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update > pbds_tree;

struct quest {
    int v, l, k, ans, index;
    // quest(int v, int l, int k) : v(v), l(l), k(k) {}
};

int n, q;
VI v;
VVI adj;
vector<int> answers;
unordered_map<int, vector<quest>> qmap;
unordered_map<int, int> cts;

void dfs(int node) {

    for (quest qu : qmap[node]) {
        int ord = pbds_tree.order_of_key({qu.l, -1}); // number of smaller terms
        ord += qu.k - 1;
        if (ord >= pbds_tree.size()) {
            qu.ans = -1;
        } else {
            qu.ans = pbds_tree.find_by_order(ord)->second;
        }

        answers[qu.index] = qu.ans;
    }

    for (int a : adj[node]) {
        if (cts[v[a]] > 0) {
            pbds_tree.erase({cts[v[a]], v[a]});
        }
        ++cts[v[a]];
        pbds_tree.insert({cts[v[a]], v[a]});

        dfs(a);

        pbds_tree.erase({cts[v[a]], v[a]});
        --cts[v[a]];
        if (cts[v[a]] > 0) {
            pbds_tree.insert({cts[v[a]], v[a]});
        }

    }
}

void run() {
    cin >> n >> q;
    v.resize(n, 0);
    adj.assign(n, VI(0));
    answers.clear();
    answers.resize(q);
    qmap.clear();
    cts.clear();
    pbds_tree.clear();
    INP(v,n);
    REP(i, n) {
        cts[v[i]] = 0;
    }
    REP(i,n-1) {
        int x;
        cin >> x;
        adj[x-1].PB(i+1);
    }

    REP(i,q) {
        quest Q;
        cin >> Q.v >> Q.l >> Q.k;
        Q.index = i;
        qmap[Q.v-1].PB(Q);
    }

    pbds_tree.insert({1, v[0]});
    ++cts[v[0]];

    // printVV(adj);
    dfs(0);

    REP(i, q) {
        cout << answers[i] << ' ';
    }
    cout << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    ll t; cin >> t;
    // ll t=1;
    REP(tests,t) run();

    // Node* tree = new Node({5, 0});

	// // insert at pos
	// tree = ins(tree, new Node({2, 1}));
    // tree = ins(tree, new Node({5, 4}));
	// tree = ins(tree, new Node({15, 2}));
	// tree = ins(tree, new Node({12, 3}));
	// tree = ins(tree, new Node({5, 4}));

    // for (int i = 0; i < tree->c; ++i) {
    //     T val = getAt(tree, i);
    //     print(val.first, val.second);
    // }

    // tree = erase(tree, {5, 4});
    // tree = erase(tree, {15, 2});

    // Node *t1, *t2;
    // tie(t1,t2) = splitsz(tree, 4);

	// each(t1, [](T val) {
	// 	cout << val.first << ' ' << val.second << '\n';
	// });

    // print("end");

    // each(t2, [](T val) {
	// 	cout << val.first << ' ' << val.second << '\n';
	// });

}