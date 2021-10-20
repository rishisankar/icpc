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

std::string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

void run() {
    /* palindrome of length i:

    12th palindrome, tg = 6
    sm[5] = 10 -> we want the 2nd 6-bit palindrome

    1  0 1 _ _  1

    */

    const int N = 32;
    VLL ct(N, 0);
    VLL sm(N,0);
    for (int i = 1; i < N; ++i) {
       int res = i;
       if (res%2 == 1) res+=1;
       res/=2;
       res-=1;
       ct[i] = (1 << res);
       sm[i] = sm[i-1] + ct[i];
    }
    // for (int i = 1; i < N; ++i) {
    //     print(i, ct[i], sm[i]);
    // }
    int m; cin >> m;
    if (m == 1) {
        print(1);
        return;
    }
    if (m == 2) {
        print(3);
        return;
    }
    int bts = 0;

    for (int i = 0; i < N; ++i) {
        if (sm[i] >= m) {
            bts = i;
            break;
        }
    }

    int r = m - sm[bts-1];
    int fll = ((bts+1)/2) - 1;
    string bits = toBinary(r-1);
    int l = bits.size();
    //dbg(bts, r, bits, l, fll);

    string s = "1";
    for (int i = 0; i < fll - l; ++i) {
        s += '0';
    }
    s += bits;
    for (int i = 0; i < bts/2; ++i) {
        s += s.at(bts/2 - 1 - i);
    }

    int res = stoi(s, 0, 2);
    print(res);
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