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

void run() {
    int n; cin >> n;
    VVLL inp(n, VLL(n));
    REP(i,n) {
        REP(j,n) {
            cin >> inp[i][j];
        }
    }
    VVLL oup(n, VLL(n, -1));

    VVI levels;
    VB taken(n, false);
    int ct = 0;
    while (ct < n) {
        levels.resize(levels.size() + 1);
        REP(j, n) {
            if (taken[j]) continue;
            bool success = true;
            REP(i, n) {
                if (i == j || taken[i]) continue;
                if (inp[i][j] != -1) {
                    success = false;
                    break;
                }
            }
            if (success) {
                levels[levels.size()-1].PB(j);
            }
        }
        for (int i : levels[levels.size()-1]) {
            taken[i] = true;
            ++ct;
        }
    }

    if (levels.size() > 1) {
        VVLL counts(n, VLL(n, 0));
        REP(i, levels.size() - 1) {
            for (int u : levels[i]) {
                for (int v : levels[i+1]) {
                    if (inp[u][v] != -1) {
                        ++counts[u][v];
                        oup[u][v] = inp[u][v];
                    }
                }
            }
        }
        for (int sep = 2; sep < levels.size(); ++sep) {
            for (int st = 0; st < levels.size() - sep; ++st) {
                for (int u : levels[st]) {
                    for (int v : levels[st + sep]) {
                        if (inp[u][v] == -1) continue;
                        ll tot = 0;
                        ll pts = 0;
                        for (int wlvl = st + 1; wlvl < st + sep; ++wlvl) {
                            for (int w : levels[wlvl]) {
                                if (oup[u][w] != -1 && inp[w][v] != -1) {
                                    tot += counts[w][v] * (oup[u][w] + inp[w][v]);
                                    pts += counts[w][v];
                                }
                            }
                        }
                        counts[u][v] = pts;
                        
                        if (pts ==0 || tot != pts * inp[u][v]) {
                            oup[u][v] = (pts+1LL) * inp[u][v] - tot;
                            counts[u][v] += 1;
                        }
                    }
                }
            }
            
        }
        
    }

    REP(i, n) {
        REP(j, n) {
            cout << oup[i][j] << ' ';
        }
        cout << '\n';
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