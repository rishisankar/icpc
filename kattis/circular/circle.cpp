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

unordered_set<string> visited;

// check if any cyclic version of s in visited
bool ctns(string& s) {
    int n = s.size();
    for (int i = 0;  i < n; ++i) {
        string s2 = s.substr(i, n-i) + s.substr(0, i);
        if (visited.count(s2)) return true;
    }
    return false;
}

void run() {
    int n, k; cin >> n >> k;
    vector<char> v(n);
    string s; cin >> s;
    REP(i, n) { v[i] = s[i]; }
    REP(rp, k) {
        vector<char> vn(n);
        REP(i, n) {
            vn[i] = (v[i] == v[(n+i-1)%n] ? 'B' : 'W');
        }
        v = vn;
    }
    string o1 = "";
    for (char c : v) o1 += c;
    // dbg("original", o1);
    vector<string> opts;
    opts.PB(o1);
    REP(i, k) {
        vector<string> nopts;

        // go backward one step
        for (string s : opts) {
            string sp = "W";
            REP(j, n) {
                if (s[j] == 'B') sp += sp[sp.size()-1];
                else sp += (sp[sp.size()-1] == 'B') ? 'W' : 'B';
            }
            if (sp[0] != sp[n]) {
                dbg("unexpected error");
                continue;
            }
            sp = sp.substr(0, n);
            nopts.PB(sp);
            string sp2 = "";
            REP(j, n) {
                sp2 += (sp[j] == 'B' ? 'W' : 'B');
            }
            nopts.PB(sp2);
        }

        // remove dups
        visited.clear();
        opts.clear();
        for (string s : nopts) {
            if (ctns(s)) continue;
            opts.PB(s);
            visited.insert(s);
        }

        // dbg("opts for", k);
        // printV(opts);
    }
    print(opts.size());
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