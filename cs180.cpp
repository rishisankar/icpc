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

void run(VI& z) {
    int n,K;
    cin >> n >> K;
    VI y(n);
    INP(y,n);
    if (K == 0) return;
    sort(all(y)); printV(y);
    VVI P(n, VI(n, 0));
    REP(i, n) {
        REP(j, n) {
            P[i][j] = abs(y[j] - y[i]);
            if (j != 0) 
                P[i][j] = P[i][j] + P[i][j-1];
        }
    }
    VVI S(K, VI(n, INT_MAX));
    VVI T(K, VI(n, -1));
    REP(j, n) {
        S[0][j] = P[j][j];
    }
    for (int i = 1; i <= K-1; ++i) {
        for (int j = i; j <= n-1; ++j) {
            int ptr = j;
            for (int k = j-1; k >= i-1; --k) {
                while (abs(y[ptr] - y[j]) <= abs(y[ptr] - y[k]))
                    --ptr;
                int cost = S[i-1][k] + P[k][ptr] - P[k][k] + P[j][j] - P[j][ptr];
                if (cost < S[i][j]) {
                    S[i][j] = cost;
                    T[i][j] = k;
                }
            }
        }
    }
    int opt = INT_MAX;
    int optj = K-1;
    for (int j = K-1; j <= n-1; ++j) {
        int cost = S[K-1][j] + P[j][n-1] - P[j][j];
        if (cost < opt) {
            opt = cost;
            optj = j;
        }
    }
    z.PB(y[optj]);
    int i = K-1, j = optj;
    while (T[i][j] != -1) {
        int k = T[i][j];
        z.PB(y[k]);
        j = k;
        --i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    VI z;
    run(z); reverse(all(z));
    REP(i,sz(z)) cout << z[i] << ' ';
    cout << '\n';
}