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

/*

answer is NO iff there exists cyclic interval I where |I| < num reqs fully contained in I (HMT)
=> find maximum of    (num reqs fully contained in I) - |I|   , if this is >0 we fail
greedy approach, duplicate range to avoid cyclicity

m=n=6
[0, 1] [1,2] [2,3] [3,4]
0 1
1 2
2 3
3 4
4 5
5 0

[0,0] [1,2] [2,3] [4,4] [4,5] [5,6] [6,6] [7,8] [8,9] [10,10] [10,11]
0 0
1 2
2 3
4 4
4 5
5 0


*/

void run() {
    ll m, n; cin >> m >> n;
    // dup: [0, m-1], [m, 2m-1]
    unordered_set<ll> starts;
    vector<pair<ll,ll>> invs;
    REP(i, n) {
        ll x,y;
        cin >> x >> y;
        if (y < x) {
            // wrap around
            starts.insert(x);
            invs.PB({x,y+m});
        } else {
            starts.insert(x);
            starts.insert(x+m);
            invs.PB({x,y});
            invs.PB({x+m, y+m});
        }
    }

    if (n > m) {
        print("NO");
        return;
    }

    vector<pair<ll, pair<ll, ll>>> crits; // {val, {s=0/f=1, idx}}
    REP(i,invs.size()) {
        // dbg("inv", invs[i].F, invs[i].S);
        crits.PB({invs[i].F, {0,i}});
        crits.PB({invs[i].S, {1,i}});
    }
    sort(all(crits));

    unordered_set<ll> endi;

    unordered_set<ll> active;
    REP(i, crits.size()) {
        pair<ll,pair<ll,ll>> p = crits[i];
        if (p.S.F == 0) {
            // start
            active.insert(p.S.S);
        } else {
            // finish
            active.erase(p.S.S);
            if (active.size() == 0) {
                endi.insert(p.F);
            }
        }
    }

    // for (ll x : endi) dbg("endi",x);

    set<ll> choices;
    for (ll x : starts) choices.insert(x);

    vector<pair<ll,ll>> invsbe;
    REP(i, invs.size()) {
        invsbe.PB({invs[i].S,invs[i].F});
    }
    sort(all(invsbe));

    REP(i, invsbe.size()) {
        ll s = invsbe[i].S;
        ll f = invsbe[i].F;
        auto it = choices.lower_bound(s);
        // if (it == choices.end()) dbg("end", i, s, f);
        // else dbg("nend", i, s, f, *it);
        if (it == choices.end()) {
            print("NO");
            return;
        }
        ll val = *it;
        if (val > f) {
            print("NO");
            return;
        }
        choices.erase(it);
        // next is valid: not end, next is not interval start, this is not end of interval
        if (val != 2*m-1 && (!starts.count(val+1)) && (!endi.count(val))) {
            choices.insert(val+1);
        }
    }
    print("YES");

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t; // t=1;
    // ll t=1;
    REP(tests,t) run();
}