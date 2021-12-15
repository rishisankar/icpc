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

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}
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

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if ((a - b) % g == 0) {
	    x = (b - a) % n * x % n / g * m + a;
	    return x < 0 ? x + m*n/g : x;
    } else {
        return -1;
    }
}

struct S {
    ll prime;
    VLL classes;
};

struct P {
    ll prime;
    ll mc; // max count
    unordered_map<ll, pair<ll, ll>> groups; // equivalence class -> highest #, count

    S convert() {
        S tmp;
        tmp.prime = prime;
        for (auto it = groups.begin(); it != groups.end(); ++it) {
            if (it->second.second == mc) {
                tmp.classes.PB(it->second.first);
            }
        }
        return tmp;
    }
};

struct Q {
    ll a;
    ll m;
    ll maxN;
    ll ind;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int n;
    cin >> n;

    unordered_map<ll, P> firstData;

    REP(i, n) {
        ll x, d;
        cin >> x >> d;
        if (firstData.find(d) == firstData.end()) {
            P tmp;
            tmp.prime = d;
            tmp.mc = 1;
            tmp.groups[x%d] = {x, 1LL};
            firstData[d] = tmp;
        } else {
            P tmp = firstData[d];
            if (tmp.groups.find(x%d) == tmp.groups.end()) {
                tmp.groups[x%d] = {x, 1LL};
            } else {
                pair<ll,ll> tmp2 = tmp.groups[x%d];
                tmp.groups[x%d] = {max(tmp2.first, x), tmp2.second+1};
                tmp.mc = max(tmp.mc, tmp2.second+1);
            }
            firstData[d] = tmp;
        }
    }

    vector<S> data;
    ll total = 0;
    for (auto it = firstData.begin(); it != firstData.end(); ++it) {
        data.PB(it->second.convert());
        total += it->second.mc;
    }

    ll N = data.size();

    ll best = LLONG_MAX;
    
    stack<Q> st;
    for (ll i : data[0].classes) {
        Q tmp;
        tmp.a = (i % data[0].prime);
        tmp.m = data[0].prime;
        tmp.maxN = i;
        tmp.ind = 1;
        st.push(tmp);
    }
    while (!st.empty()) {
        Q t = st.top();
        st.pop();
        if (t.ind == N) {
            ll v = t.maxN % t.m;
            ll scl = t.a % t.m;
            if (scl < v) scl += t.m;
            v = scl - v;
            best = min(best, t.maxN+v);
        } else {
            for (ll i : data[t.ind].classes) {
                ll tp = data[t.ind].prime;
                Q newT;
                newT.a = crt(t.a, t.m, i%tp, tp);
                newT.m = t.m*tp;
                newT.ind = t.ind+1;
                newT.maxN = max(t.maxN, i);
                st.push(newT);
            }
        }
    }

    print(best, total);

}