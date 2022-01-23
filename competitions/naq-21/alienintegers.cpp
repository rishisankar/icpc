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

void run() {
    ll n; cin >> n;
    if (n == 0) {
        print(1);
        return;
    }
    string s = to_string(n);
    set<int> digits;
    for (int i = 0; i <= 9; ++i) {
        digits.insert(i);
    }
    int k = s.size();
    for (int i = 0; i < k; ++i) {
        int dig = s[i] - '0';
        digits.erase(dig);
    }

    vector<int> dd;
    
    for (int i : digits) dd.PB(i);
    sort(all(dd));
    int M = dd.size();

    if (dd.size() == 0) {
        print("Impossible");
        return;
    }

    string lwr = "0";
    int d0 = s[0] - '0';
    if (d0 != 1) {
        int bst = dd[0];
        for (int i : dd) {
            if (i >= d0) break;
            bst = i;
        }
        lwr += to_string(bst);
    }
    for (int i = 0; i < k - 1; ++i) {
        lwr += to_string(dd[M-1]);
    }

    string hgr = "0";
    d0 = s[0] - '0';
    int bst = dd[M-1];
    for (int i = M-2; i >= 0; --i) {
        if (dd[i] <= d0) break;
        bst = dd[i];
    }
    hgr += to_string(bst);
    for (int i = 0; i < k - 1; ++i) {
        hgr += to_string(dd[0]);
    }

    printV(dd);

    string hh2 = "0";
    int lwst = dd[0];
    if (lwst == 0 && M >= 2) {
        lwst = dd[1];
    }
    dbg(lwst);
    hh2 += to_string(lwst);
    REP(i, k) {
        hh2 += to_string(dd[0]);
    }

    string ll2 = "0";
    REP(i, k-1) {
        ll2 += to_string(dd[M-1]);
    }

    set<ll> ansz;
    ansz.insert(stoll(hh2));
    ansz.insert(stoll(ll2));
    ansz.insert(stoll(hgr));
    ansz.insert(stoll(lwr));
    if (!digits.count(0)) {
        if (ansz.count(0)){
            ansz.erase(0);
        }
    }
    VLL ans;
    for (ll i : ansz) 
    {
        ans.PB(i);
    }
    sort(all(ans));

    printV(ans);
    dbg(lwr,hgr,ll2,hh2);

    if (ans.size() == 0) {
        print("Impossible");
        return;
    }
    ll bestDiff = LLONG_MAX;
    VLL bstv;
    for (ll i : ans) {
        ll dif = abs(n - i);
        if (dif < bestDiff) {
            bstv.clear();
            bestDiff = dif;
            bstv.PB(i);
        } else if (dif == bestDiff) {
            bstv.PB(i);
        }
    }

    sort(all(bstv));
    for (ll l : bstv) {
        cout << l << ' ';
    }
    cout << '\n';


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