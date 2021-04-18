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
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

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

pair<int,int> gs(int m, int n) {
    if (m == 0) {
        return {0,0};
    }
    if (n == 0) {
        return {INT_MAX,INT_MAX};
    }
    bool sg = false;
    if ((m < 0 && n > 0) || (n < 0 && m > 0)) sg = true;
    n = abs(n); m = abs(m);
    int g = __gcd(m,n);
    n /= g; m /= g;
    if (sg) n=-n;
    return {m,n};
}

int maxPoints(vector<vector<int>>& points) {
    int N = points.size();
    if (N == 1) return 1;

    int mc = -1;
    for (int i = 0; i < N; ++i) {
        map<PII, int> mp;
        for (int j = 0; j < N; ++j) {
            if (j == i) continue;
            int m = points[j][1] - points[i][1];
            int n = points[j][0] - points[i][0];
            pair<int,int> ppp = gs(m,n);
            if (!mp[ppp]) mp[ppp] = 1; else ++mp[ppp];
            mc = max(mc, mp[ppp]);
        }
    }
    return mc+1;
}

void run(int n) {
    VVI pts(n,VI(2));
    REP(i, n) {
        cin >> pts[i][0] >> pts[i][1];
    }
    print(maxPoints(pts));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;
        run(n);
    }
}