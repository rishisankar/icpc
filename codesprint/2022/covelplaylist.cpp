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

const int MOD = int(1e9) + 9;
vector<string> st;
int n, m;

const ll P1 = 11;
const ll P2 = 13;

void chshP(int k, int sti, vector<ll>& hsh, ll P) {
    unordered_map<ll,ll> invv; invv[11] = 363636367; invv[13] = 615384621;
    ll h = 0;
    ll pw = 1;
    REP(i, k-1) {
        h += (st[sti][i]-'A'+1) * pw;
        h%=MOD;
        pw *= P;
        pw%=MOD;
    }
    REP(i, n) {
        char vl = (i+k-1 >= n) ? 'H' : st[sti][i+k-1];
        h += (vl-'A'+1) * pw;
        h%= MOD;
        hsh[i] = h;
        h -= (st[sti][i]-'A'+1);
        h = (h+MOD)%MOD;
        h *= invv[P];
        h %= MOD;
    }
}

void chsh(int k, int sti, vector<ll>& hsh) {
    VLL v1(n), v2(n);
    chshP(k,sti,v1,P1); chshP(k,sti,v2,P2);
    REP(i, n) {
        hsh[i] = (v1[i] << 32) + v2[i];
    }
}

bool match(int i, int j, int si, int k) {
    REP(a, k) {
        char v1 = (i+a >= n) ? 'H' : st[0][i+a];
        char v2 = (j+a >= n) ? 'H' : st[si][j+a];
        if (v1 != v2) return false;
    }
    return true;
}

bool check(int k) {
    unordered_map<ll, unordered_set<ll>> mp;
    vector<ll> h1(n); chsh(k,0,h1);
    // printV(h1);
    int ct = 0;
    REP(i,n) {
        mp[h1[i]].insert(i);
    }
    for (int i = 1; i < m; ++i) {
        vector<ll> hv(n); chsh(k,i,hv);
        // printV(hv);
        REP(j,n) {
            if (mp.count(hv[j]) && mp[hv[j]].size()>0) {
                for (int ind : mp[hv[j]]) {
                    if (match(ind, j, i, k)) {
                        // dbg("match", ind, j, i, k);
                        mp[hv[j]].erase(ind);
                        ++ct;
                    }
                }
            }
        }
    }
    return ct*2 <= n;
}

void run() {
    cin >> n >> m;
    st.resize(m);
    REP(i,m) {
        cin >> st[i];
    }
    int lo = 1; int hi = n;
    int best = -1;
    while (lo <= hi) {
        int mid = (lo+hi)/2;
        bool t = check(mid);
        // dbg("check",mid,t);
        if (t) {
            best = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    print(best);
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