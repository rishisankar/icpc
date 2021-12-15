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
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; print(args...); }

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
    string s;
    cin >> s;
    int n = s.size();
    VVLL dpL(n, VLL(n, 0));
    VVLL dpR(n, VLL(n, 0));
    VVLL dpX(n, VLL(n, 0));

    REP(i, n) {
        dpL[i][i] = dpR[i][i] = dpX[i][i] = 1;
    }


    for (int ln = 2; ln <= n; ++ln) {
        for (int st = 0; st < n-ln+1; ++st) {
            int ed = st + ln - 1;
            if (ln == 2) {
                if (s.at(st) == s.at(ed)) {
                    dpL[st][ed] = 2;
                    dpR[st][ed] = 2;
                    dpX[st][ed] = 3;
                } else{
                    dpL[st][ed] = 1;
                    dpR[st][ed] = 1;
                    dpX[st][ed] = 2;
                }
            } else {
                if (s.at(st) == s.at(ed)) {
                    dpL[st][ed] += dpX[st+1][ed-1] + 1;
                    dpR[st][ed] += dpX[st+1][ed-1] + 1;
                    dpX[st][ed] += dpX[st+1][ed-1] + 1;
                }
                dpL[st][ed] += dpL[st][ed-1];
                dpR[st][ed] += dpR[st+1][ed];
                dpX[st][ed] += dpX[st+1][ed-1] + dpL[st][ed-1] + dpR[st+1][ed];
            }
            dpL[st][ed] %= MOD;
            dpR[st][ed] %= MOD;
            dpX[st][ed] %= MOD;
        }
    }
    cout << (dpX[0][n-1] % MOD) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    ll t; cin >> t;
    //ll t=1;
    REP(tests,t) run();
}