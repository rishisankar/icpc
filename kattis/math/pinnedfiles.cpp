#include <bits/stdc++.h>
using namespace std;

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
#define F first
#define S second
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

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;

/*

process each independently

for pinned files:
1. first k currently pinned that are correct (ignore anything that needs to be unpinned) cost 0 to order
2. remaining requires +2 (if pinned), +1 (not pinned)

other is done in reverse...

*/

ll solve(int pi, int ui, VI& vi, int pf, int uf, VI& vf) {
    unordered_set<int> pinned, unpinned, wantpin;
    int n = pi+ui;
    REP(i, n) {
        if (i < pi) {
            pinned.insert(vi[i]);
        } else {
            unpinned.insert(vi[i]);
        }
    }
    REP(i, pf) {
        wantpin.insert(vf[i]);
    }   
    ll ans = 0;
    int j = 0;
    REP(i, pi) {
        if (!wantpin.count(vi[i])) continue; // irrelevant ; going to be unpinned
        if (j < pf && vi[i] == vf[j]) {
            ++j;
        }
    }
    // j represents first index of mismatch in final
    for (; j < pf; ++j) {
        if (pinned.count(vf[j])) ans+=2;
        else ans+=1;
    }
    return ans;
}

void run() {
    int pi,ui; cin >> pi >> ui;
    VI vi(pi+ui);
    INP(vi, pi+ui);
    int pf,uf; cin >> pf >> uf;
    VI vf(pi+ui);
    INP(vf, pi+ui);
    ll a1 = solve(pi,ui,vi,pf,uf,vf);
    reverse(all(vi));
    reverse(all(vf));
    swap(pi,ui);
    swap(pf,uf);
    ll a2 = solve(pi,ui,vi,pf,uf,vf);
    print(a1+a2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}