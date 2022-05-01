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

void run() {
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    
    vector<vector<char>> tbl(16, vector<char>(3));
    REP(i, 7) {
        tbl[i][0] = digits[i];
        tbl[i][1] = digits[i+1];
        tbl[i][2] = digits[i+2];
    }
    REP(i, 9) {
        tbl[i+7][0] = tbl[i+7][1] = tbl[i+7][2] = digits[i];
    }

    unordered_set<string> wins;

    REP(i, 16) {
        REP(j, 16) {
            REP(k, 16) {
                REP(l, 16) {
                    REP(m, 9) {
                        string s = "";
                        for (char z : tbl[i]) s.push_back(z);
                        for (char z : tbl[j]) s.push_back(z);
                        for (char z : tbl[k]) s.push_back(z);
                        for (char z : tbl[l]) s.push_back(z);
                        s.push_back(digits[m]);
                        s.push_back(digits[m]);
                        sort(s.begin(), s.end());
                        wins.insert(s);
                    }
                }
            }
        }
    }

    int x; cin >> x; --x;
    string hand = "";
    vector<int> cts(9,0);
    REP(i, 14) {
        int hi; cin >> hi; --hi; ++cts[hi];
        hand.push_back(digits[hi]);
    }
    ld best = 0;
    REP(i, 14) {
        ld expv = 0;
        REP(j, 9) {
            char tmp = hand[i];
            hand[i] = digits[j];

            string s = hand;
            sort(s.begin(), s.end());
            int pts = 0;
            if (wins.count(s)) {
                pts = 1;
                REP(k, 14) {
                    if ((s[k] - '0') == x) ++pts;
                }
            }

            hand[i] = tmp;
            ld P = 4 - cts[j];
            P/=22;
            expv += P*pts;
        }
        best = max(best,expv);
    }
    print(best);
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