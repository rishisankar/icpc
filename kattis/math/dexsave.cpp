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
    int d,m; cin >> d >> m;
    string s; cin >> s;
    int k; cin >> k;
    vector<pair<bool,int>> dice;
    REP(i,k) {
        string dd; cin >> dd;
        bool add = (dd[0] == '+');
        int x;
        if (dd.size() == 4) x=10; else x = (dd[2] - '0');
        dice.PB({add,x});
    }
    ll ct = 0;
    ll good = 0;
    int mp = 1;
    REP(i,k) {
        mp*=10;
    }
    for (int r1 = 1; r1 <= 20; ++r1) {
        for (int r2 = 1; r2 <= 20; ++r2) {
            if (s == "straight" && r1 != r2) continue;
            for (int i = 0; i < mp; ++i) {
                int sm = 0;
                bool fail = false;
                int curj = i;
                for (int j = 0; j < k; ++j) {
                    int rj = (curj % 10) + 1;
                    curj/=10;
                    if (rj > dice[j].S) {
                        fail = true;
                        break;
                    }
                    if (dice[j].F) sm += rj; else sm-=rj;
                }
                if (fail) continue;
                ++ct;
                int roll = (s == "disadvantage") ? min(r1,r2) : max(r1,r2);
                if (roll == 20) {
                    ++good; continue;
                }
                if (roll == 1) continue;
                if (roll + m + sm >= d) ++good;
            }
        }
    }
    ld res = good/(ld)ct;
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