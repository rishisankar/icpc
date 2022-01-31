#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
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

void run() {
    ld res = 0;
    int d,m; cin >> d >> m;
    unordered_map<int, ld> p;
    string s; cin >> s;
    VPII dr;
    for (int i = 1; i <= 20; ++i) {
        int lb=1; int rb=20;
        if (s == "straight") { lb = i; rb = i; }
        for (int j = lb; j <= rb; ++j) {
            dr.PB({i,j});
        }
    }
    for (PII pr : dr) {
        int roll;
        if (s == "disadvantage") roll = min(pr.F, pr.S);
        else roll = max(pr.F, pr.S);
        if (!p.count(roll))p[roll] = 0;
        p[roll] += 1/(ld)dr.size();
    }
    p[1] = 0;
    res += p[20];
    p[20] = 0;
    int k; cin >> k;
    REP(rolls, k) {
        string dd; cin >> dd;
        bool add = (dd[0] == '+');
        int x;
        if (dd.size() == 4) x=10; else x = (dd[2] - '0');
        unordered_map<int, ld> p2;
        for (auto par : p) {
            for (int i = 1; i <= x; ++i) {
                int nr = add ? par.F + x : par.F - x;
                ld pb = par.S / x;
                if (p2.count(nr)) {
                    p2[nr] += pb;
                } else p2[nr] = pb;
            }
        }
        p = p2;
    }
    for (auto par : p) {
        // if (par.F == 1) continue;
        // if (par.F == 20) {res+=par.S; continue;}
        dbg("map",par.F, par.S);
        if (par.F + m >= d) res += par.S;
    }
    print(res);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    cout.setf(ios::fixed);
    cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}