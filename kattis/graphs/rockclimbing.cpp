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

int r,c;
VVLL adj;
ll max_en;

VPII dirs;

bool test(ll m) {
    VVLL eg(r+1, VLL(c, LLONG_MIN));
    queue<tuple<int,int,ll>> q;
    REP(i, c) {
        eg[r][i] = m;
        q.push({r,i,m});
    }
    while (!q.empty()) {
        tuple<int,int,ll> t = q.front();
        q.pop();
        int x = get<0>(t);
        int y = get<1>(t);
        ll energy = get<2>(t);
        for (PII dir : dirs) {
            int xp = x + dir.F;
            int yp = y + dir.S;
            if (xp >= r+1 || xp < 0 || yp >= c || yp < 0) continue;
            if (adj[xp][yp] > energy) continue;
            if (xp == 0) return true;
            ll ne = energy - adj[xp][yp];
            if (ne >= max_en + 5) return true;
            if (ne > eg[xp][yp]) {
                q.push({xp,yp,ne});
                eg[xp][yp] = ne;
            }
        }
    }
    return false;
}

void run() {
    dirs.PB({-1,0});
    dirs.PB({1,0});
    dirs.PB({0,1});
    dirs.PB({0,-1});
    cin >> r >> c;
    adj.assign(r+1, VLL(c, 0));
    VLL sms(c, 0);
    REP(i, c) { char t; cin >> t;}
    REP(i, r) {
        REP(j, c) {
            cin >> adj[i][j];
            if (adj[i][j] > 0) sms[j] += adj[i][j];
        }
    }
    max_en = maxe(sms) + 1;
    REP(i, c) { char t; cin >> t; }

    ll lo = 0;
    ll hi = max_en;
    ll best = max_en;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (test(mid)) {
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
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}