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

void test(string s1, string s2, string s3, string op) {

    if (op == "+") {
        if (stoll(s1) + stoll(s2) == stoll(s3)) {
            print(s1,op,s2,"=",s3);
            exit(0);
        }
    } else {
        if (stoll(s1) * stoll(s2) == stoll(s3)) {
            print(s1,op,s2,"=",s3);
            exit(0);
        }
    }
}

void run() {
    string s1, s2, s3, op, eq;
    cin >> s1 >> op >> s2 >> eq >> s3;

    // first try swapping s1,s2
    for (int l1 = 1; l1 < s1.size(); ++l1) {
        for (int l2 = 1; l2 < s2.size(); ++l2) {
            string s1p = s2.substr(0, l2) + s1.substr(l1, s1.size()-l1);
            string s2p = s1.substr(0, l1) + s2.substr(l2, s2.size()-l2);
            test(s1p,s2p,s3,op);
        }
    }

    // try swapping s1,s3
    for (int l1 = 1; l1 < s1.size(); ++l1) {
        for (int l2 = 1; l2 < s3.size(); ++l2) {
            string s1p = s3.substr(0, l2) + s1.substr(l1, s1.size()-l1);
            string s3p = s1.substr(0, l1) + s3.substr(l2, s3.size()-l2);
            test(s1p,s2,s3p,op);
        }
    }

    // try swapping s2,s3
    for (int l1 = 1; l1 < s2.size(); ++l1) {
        for (int l2 = 1; l2 < s3.size(); ++l2) {
            string s2p = s3.substr(0, l2) + s2.substr(l1, s2.size()-l1);
            string s3p = s2.substr(0, l1) + s3.substr(l2, s3.size()-l2);
            test(s1,s2p,s3p,op);
        }
    }
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