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

struct name {
  string first;
  string second;

  string getK(int k) {
    string res = "";
    res += tolower(second[0]);
    int i;
    for (i = 0; i < k && i+1 < second.size(); ++i) {
        res += tolower(second[i+1]);
    }
    k-=i;
    res += tolower(first[0]);
    for (i = 0; i < k && i+1 < first.size(); ++i) {
        res += tolower(first[i+1]);
    }
    return res;
  }  
};

void run() {
    int n; cin >> n;
    vector<pair<string,int>> markOrder;
    vector<name> names(n);
    REP(i, n) {
        cin >> names[i].first >> names[i].second;
        string trs = "";
        REP(j, names[i].second.size()) trs += tolower(names[i].second[j]);
        REP(j, names[i].first.size()) trs += tolower(names[i].first[j]);
        // dbg(trs,i);
        markOrder.PB({trs,i});
    }
    sort(all(markOrder));

    vector<vector<string>> strs(n);
    REP(i, n) {
        name nm = names[markOrder[i].second];
        REP(j, (nm.first.size() + nm.second.size() - 1)) {
            strs[i].PB(nm.getK(j));
        }
    }

    // printVV(strs);

    const int MM = 90;
    vector<vector<ll>> dp(n, vector<ll>(MM, LLONG_MAX - 10000));
    REP(i,MM) dp[0][i] = i;
    OREP(i, n-1) {
        name curName = names[markOrder[i].second];
        name prevName = names[markOrder[i-1].second];
        int maxadd = curName.first.size() + curName.second.size() - 2;
        for (int j = 0; j <= maxadd; ++j) {
            int prevmaxadd = prevName.first.size() + prevName.second.size() - 2;
            for (int k = 0; k <= prevmaxadd; ++k) {
                if (strs[i-1][k] < strs[i][j]) {
                    dp[i][j] = min(dp[i][j], dp[i-1][k]+j);
                }
            }
        }
    }

    ll best = LLONG_MAX;
    REP(i, MM) {
        best = min(best, dp[n-1][i]);
    }

    print(best);

    // printVV(dp);


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