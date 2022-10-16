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

// result should be empty at first
// example: graphs/cantinaofbabel

void split(string s, string delim, vector<string>& result) {
    auto start = 0U;
    auto end = s.find(delim);
    while (end != string::npos)
    {
        result.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }

    result.push_back(s.substr(start, end));
}

void run() {
    
    string x1, x2;
    getline(cin, x1);
    getline(cin, x2);
    vector<string> c1, c2;
    split(x1, " ", c1);
    split(x2, " ", c2);
    printV(c1);
    printV(c2);
    ll a1 = 0; ll a2 = 0;
    ll pw = 1;
    for (int i = 0; i < c1.size(); ++i) {
        a1 += (stoll(c1[c1.size()-1-i]) * pw);
        pw *= 10;
    }
    pw = 1;
    for (int i = 0; i < c2.size(); ++i) {
        a2 += (stoll(c2[c2.size()-1-i]) * pw);
        pw *= 10;
    }
    ll res = a1 + a2;
    dbg(a1,a2,res);
    vector<int> rv;
    while (res != 0) {
        rv.PB(res % 10);
        res /= 10;
    }
    if (rv.size() == 0) print(0);
    else {
        reverse(all(rv));
        for (int i : rv) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    cin.ignore(1000, '\n');
    // ll t=1;
    // cin >> t;
    // dbg(t);
    // t=1;
    REP(tests,t) run();
}