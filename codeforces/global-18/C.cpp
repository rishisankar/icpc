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

string toBinary(ll n) {
    string r;
    while (n!=0) {
        r = (n%2==0 ? "0" : "1") + r;
        n/=2;
    }
    return r;
}

string comp(string x) {
    string res = "";
    REP(i,x.size()) {
        if (x[i] == '0')res += '1';
        else res +='0';
    }
    return res;
}

int diff(string a,string b) {
    int ct = 0;
    REP(i,a.size()) {
        if (a[i] != b[i]) ++ct;
    }
    return ct;
}
int ctOnes(string a) {
    int ct = 0;
    REP(i,a.size()) {
        if (a[i] == '1') ++ct;
    }
    return ct;
}

void run() {
    int n; cin >> n ;
    string a,b; cin >> a >> b;
    // if (a == b) {
    //     print(0);
    //     return;
    // }
    string c = comp(b);
    int d1 = diff(a,b);
    int d2 = diff(a,c);

    int ct1 = 0, ct0 = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            if (a[i] == '0') ++ ct0; else ++ct1;
        }
    }
    if (ct1 != ct0 && ct1 != ct0+1) d1 = INT_MAX;

    ct1 = 0; ct0 = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != c[i]) {
            if (a[i] == '0') ++ ct0; else ++ct1;
        }
    }
    if (ct1 != ct0 && ct1 != ct0+1) d2 = INT_MAX;
    if (d1 %2 != 0) d1 = INT_MAX;

    if (d2 %2 != 1) d2 = INT_MAX;
    int best = min(d1,d2);
    if (best == INT_MAX) best = -1;
    print(best);
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
}