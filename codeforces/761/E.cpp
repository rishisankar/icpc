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

typedef tuple<int,int,int,int,int> T;

unordered_map<int, unordered_set<int>> adj;
unordered_map<int, int> parent;

// returns {longest path touching i, longest diam found, root of longest path, r1 of diam, r2 of diam}
T dfs(int i) {
    if (!adj.count(i)) {
        // dbg(i,1,1,i,i,i);
        return {1,1,i,i,i};
    }
    int bestDiam = 1;
    int bestR1 = i;
    int bestR2 = i;
    VPII nums;
    for (int j : adj[i]) {
        T soln = dfs(j);
        if (get<1>(soln) > bestDiam) {
            bestDiam = get<1>(soln);
            bestR1 = get<3>(soln);
            bestR2 = get<4>(soln);
        }
        if (get<0>(soln) + 1 > bestDiam) {
            bestDiam = get<0>(soln) + 1;
            bestR1 = get<2>(soln);
            bestR2 = i;
        }
        nums.PB({get<0>(soln), get<2>(soln)});
    }
    sort(all(nums));
    if (nums.size() >= 2) {
        int newDiam = nums[nums.size()-1].first + nums[nums.size()-2].first + 1;
        if (newDiam > bestDiam) {
            bestDiam = newDiam;
            bestR1 = nums[nums.size()-1].second;
            bestR2 = nums[nums.size()-2].second;
        }
    }
    // dbg(i,1 + nums[nums.size()-1].first , bestDiam, nums[nums.size()-1].second, bestR1, bestR2 );
    return {1 + nums[nums.size()-1].first , bestDiam, nums[nums.size()-1].second, bestR1, bestR2};
}

void run() {
    int n; cin >> n ; VLL v(n); INP(v,n);
    unordered_map<int,int> toI;
    REP(i,n) toI[v[i]]=i+1;
    stack<int> st;
    REP(i,n) st.push(v[i]);
    parent[0] = -1;
    while (!st.empty()) {
        int t= st.top();
        st.pop();
        if (parent.count(t))continue;
        int xp2 = 1;
        while (xp2 < t) xp2 <<= 1;
        int par = xp2-t;
        parent[t] = par;
        adj[par].insert(t);
        if (!parent.count(par)) st.push(par);
    }
    int start = 0;
    while (adj[start].size() == 1 && !toI.count(start)) {
        start = *adj[start].begin();
    }
    // dbg("start", start);
    T soln = dfs(start);
    print(toI[get<3>(soln)],toI[get<4>(soln)],get<1>(soln)-1);

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