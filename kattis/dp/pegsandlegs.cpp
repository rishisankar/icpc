#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define REP(i, j) FOR(i, 0, j)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define mp make_pair
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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

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
    int L,P; cin >> L >> P;
    int n = L+P;
    vector<pair<ld,ld>> exv(L+P);
    rep(i,0,L) {
        cin >> exv[i].F;
        exv[i].S = 0;
    }
    unordered_set<int> zid;
    rep(i,0,n) zid.insert(i);
    rep(i,0,P) {
        ld l, r; cin >> l >> r;
        int l1, l2; cin >> l1 >> l2; --l1; --l2;
        if (zid.count(l1)) zid.erase(zid.find(l1));
        if (zid.count(l2)) zid.erase(zid.find(l2));
        ld pstk = 0;
        ld ev = 0;
        pstk += (1-l-r);
        pstk += l*exv[l1].S;
        pstk += r*exv[l2].S;
        ev += l * (1-exv[l1].S) / (1-pstk)  * exv[l1].F;
        ev += r * (1-exv[l2].S) / (1-pstk)  * exv[l2].F;
        exv[i+L] = {ev,pstk};
    } 
    dbg(exv);
    ld best = 0;
    for (int i : zid) {
        dbg(i,exv[i]);
        best = max(best, exv[i].F);
    }
    cout << best << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    cout.setf(ios::fixed);
    cout.precision(15);
    cerr.setf(ios::fixed);
    cerr.precision(3);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}