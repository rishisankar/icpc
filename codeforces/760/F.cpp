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
    string r = "";
    while (n!=0) {
        char c = n%2==0 ? '0' : '1';
        r.PB(c);
        n/=2;
    }
    reverse(all(r));
    return r;
}

void succeed() {
    print("YES");
    exit(0);
}

/*
assumes x is of the form 1...1
*/
bool test11(string x, string y) {
    if (x == y) return true;
    if (x.size() >= y.size()) return false;
    for (int j = 0; j <= y.size() - x.size(); ++j) {
        string ys = y.substr(j, x.size());
        dbg(x,y,ys,j);
        if (x != ys) continue;
        bool failed = false;
        for (int i = 0; i < j; ++i) {
            if (y[i] != '1') {
                failed = true;
                break;
            }
        }
        for (int i = j+x.size(); i < y.size(); ++i) {
            if (y[i] != '1') {
                failed = true;
                break;
            }
        }
        if (failed) continue;
        return true;
    }
    return false;
}

void run() {
    ll x, y;
    cin >> x >> y;

    if (x == y) succeed();

    string xs = toBinary(x);
    string ys = toBinary(y);
    int n = xs.size();
    if (xs[n-1] == '1') {
        dbg("test1");
        if (test11(xs,ys)) succeed();
        reverse(all(xs));
        if (test11(xs,ys)) succeed();
        print("NO");
        return;
    } else {
        dbg("test2");
        int i;
        for (i = xs.size() - 1; i >= 0; --i) {
            if (xs[i] == '1') {
                break;
            }
        }
        string xsub = xs.substr(0, i+1);
        dbg(i, xsub);
        if (test11(xsub,ys)) succeed();
        dbg("t1");
        reverse(all(xsub));
        if (test11(xsub,ys)) succeed();
        dbg("t2");
        xs += '1';
        if (test11(xs,ys)) succeed();
        dbg("t3");
        reverse(all(xs));
        if (test11(xs,ys)) succeed();
        dbg("t4");
        print("NO");
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