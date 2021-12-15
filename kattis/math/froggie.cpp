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
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; print(args...); }

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

bool run() {
    int L, W;
    cin >> L >> W;
    VVI v(L, VI(2));
    VI offsets(L);
    REP(i, L) {
        int O,I,S;
        cin >> O >> I >> S;
        offsets[i] = O;
        v[i][0] = I;
        v[i][1] = S;
    }
    int px; cin >> px;
    int py = L;
    string d;
    cin >> d;
    int M = d.size();

    REP(i, M) {

        char c = d.at(i);
        if (c == 'U') {
            --py;
        } else if (c == 'D') {
            ++py;
        } else if (c == 'R') {
            ++px;
        } else {
            --px;
        }

        if (!(py < 0 || py >= L)) {
            // check collisions with cars

            int o = offsets[py];
            int s = v[py][1];
            bool right = (py % 2 == 0);

            int cx = px;
            if (!right) cx = W-1-cx;

            for (int a = o; a < W; a += v[py][0]) {
                if (s == 0) {
                    if (a == cx) return false;
                } else {
                    if (a+1 <= cx && cx <= a+s) return false;
                }
            }
        }

        REP(l, L) {
            if (v[l][1] == 0) continue;
            int o = offsets[l];
            o += v[l][1];
            o %= v[l][0];
            offsets[l] = o;
        }

    }
    return py < 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    // ll t; cin >> t;
    if (run()) {
        print("safe");
    } else {
        print("squish");
    }
}