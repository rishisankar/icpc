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

typedef pair<ll,ll> PLL;

struct Tree {
	typedef PLL T;
	static constexpr T unit = {LLONG_MAX,LLONG_MAX};
	T f(T a, T b) { if (a.second < b.second) return a; else return b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};


void fail() {
    print("cancel road trip");
    exit(0);
}

void run() {
    ll n, g;
    cin >> n >> g;
    unordered_map<ll, int> indx;

    vector<PLL> v(n);
    REP(i, n) {
        cin >> v[i].first >> v[i].second;
    }
    sort(all(v));
    REP(i, n) {
        indx[v[i].first] = i;
    }

    Tree t(n);
    REP(i, n) {
        t.update(i, v[i]);
    }

    ll qs = 0;
    ll qe = n;
    for (int i = 0; i < n; ++i) {
        if (v[i].first > g) {
            qe = i;
            break;
        }
    }
    if (qe <= qs) {
        fail();
    }

    ll cst = 0;
    ll gas = g;
    gas -= v[0].first;
    if (qe == n) {
        print(cst);
        return;
    }

    while (qe < n) {
        PLL cp = t.query(qs, qe);
       
        int m = indx[cp.first];
        // dbg("x", cp.first, cp.second, m);
    
        gas -= (v[m].first - v[qs].first);
        
        int last;
        bool cheaper = false;
        for (last = m+1; last < n; ++last) {
            if (v[last].first - cp.first > g) {
                last = last-1;
                break;
            }
            if (v[last].second <= cp.second) {
                cheaper = true;
                break;
            }
        }
        if (last == n) {
            last--;
            cheaper = true;
        }

        // dbg(qs, qe, m, last, gas, cst, cheaper);

        if (last <= m) fail();
        
        if (!cheaper) {
            // buy as much gas as possible
            cst += (g - gas) * v[m].second;
            gas = g;
        } else {
            // buy enough to travel to cheaper
            ll req = (v[last].first - v[m].first) - gas;
            if (req < 0) req = 0;
            cst += req * v[m].second;
            gas += req;
        }
        gas -= (v[m+1].first - v[m].first);
        if (gas < 0) fail();
        qs = m+1;
        qe = last + 1;
    }

    print(cst);

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