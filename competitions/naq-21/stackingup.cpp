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

// 0: 1, 1: d, 2: +
void printIns(vector<int>& ins) {
    for (int i : ins) {
        if (i == 0) cout << '1';
        else if (i == 1) cout << 'd';
        else if (i == 2) cout << '+';
    }
    // cout << '\n';
}

string toBinary(ll n) {
    string r;
    while (n!=0) {
        r = (n%2==0 ? "0" : "1") + r;
        n/=2;
    }
    return r;
}

// 0: 1, 1: d, 2: +
ll gen(ll x, vector<int>& ins) {
    string b = toBinary(x);
    int n = b.size();
    ll ct = 0;
    ins.PB(0);
    for (int i = 1; i < n; ++i) {
        ins.PB(1);
        ins.PB(2);++ct;
        if (b[i] == '1') {
            ins.PB(0);
            ins.PB(2);++ct;
        }
    }
    return ct;

    // // 101011
    // bool built = false;
    // for (int i = n-1; i >= 0; --i) {
    //     if (b[i] == '0') continue;
    //     ins.PB(0);
    //     for (int j = 0; j < (n-1-i); ++j) { // # of doubling
    //         ins.PB(1); //d
    //         ins.PB(2); ++ct; // +
    //     }
    //     if (built) {
    //         ins.PB(2); ++ct;

    //         // # of +1 = n-1-i
    //         for (int j = 0; j < n-1-i; ++j) {
    //             ins.PB(0);
    //             ins.PB(0);
    //             ins.PB(2);
    //             ins.PB(2);
    //             ct +=2 ;
    //         }
    //     }
    //     built = true;
    // }
    // return ct;
}

void run() {
    int n; cin >> n;
    vector<int> inp(n);
    REP(i,n) {
        cin >> inp[i];
    }
    vector<vector<int>> ans(n);
    ll offset = 0;
    for (int i = n-1; i >= 0; --i) {
        ll off = gen(inp[i] + offset, ans[i]);
        offset += off;
    }
    // dbg(offset);

    for (int i = 0; i < n; ++i) {
        printIns(ans[i]);
    }
    cout << '\n';

    // vector<int> ins;
    // ll r = gen(n, ins);
    // dbg("R",r);
    // printIns(ins);
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