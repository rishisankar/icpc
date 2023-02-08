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

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

ll solve(int x, VVI& rv) {
    ll ans = 1;
    for (int v : rv[x]) {
        ans *= solve(v, rv);
        ans %= mod;
    }
    return (ans+1)%mod;
}

void run() {
    int n; cin >> n;
    VI v(n);
    VVI rv(n);
    REP(i ,n) {
        cin >> v[i];
        v[i]--;
        rv[v[i]].PB(i);
    }
    VB visited(n, false);
    VI sol(n, 0); // 1.. = part of chain, -1.. = part of cycle
    unordered_map<int, VI> chainForCyc;
    unordered_map<int, int> chainHead;
    ll nc = 0;
    ll chains = 0;
    REP(i, n) {
        if (visited[i]) continue;
        // dbg("running for ", i);
        unordered_set<int> visT;
        // follow starting from...
        int t = i;
        while(true) {
            visited[t] = true;
            visT.insert(t);
            int x = v[t];
            if (visited[x] && !visT.count(x)) {
                // then everything up to t is part of a chain.
                int chaini;
                if (sol[x] < 0) {
                    // cycle ==> new chain
                    ++chains;
                    chaini = chains;
                    chainForCyc[sol[x]].PB(chaini);
                    chainHead[chaini] = t;
                } else {
                    // old chain
                    chaini = sol[x];
                }
                int cv = i;
                while (cv != x) {
                    sol[cv] = chaini;
                    cv = v[cv];
                }
                break;
            } else if (visited[x] && visT.count(x)) {
                // x..x is a cycle, i..{x-1} chain
                // dbg("2", x, i);
                ++nc;
                if (x != i) {
                    ++chains;
                    chainForCyc[-nc].PB(chains);
                }
                int cv = i;
                while (cv != x) {
                    // link to new cycle
                    sol[cv] = chains;
                    if (v[cv] == x) chainHead[chains] = cv;
                    cv = v[cv];
                }
                sol[x] = -nc;
                cv = v[x];
                while (cv != x) {
                    sol[cv] = -nc;
                    cv = v[cv];
                }
                break;
            } else {
                t = x;
            }
        }
    }
    // printV(sol);
    // dbg(nc, chains);

    VLL chainlen(chains, 0);
    // for (int i : sol) {
    //     if (i > 0) chainlen[i-1]++;
    // }
    REP(i, chains) {
        chainlen[i] = solve(chainHead[i+1], rv);
    }

    // printV(chainlen);
    
    ll ans = 1;
    REP(i, nc) {
        // for each cycle
        int idx = -(i+1);
        ll choices = 1;
        for (int cyc : chainForCyc[idx]) {
            ll clen = chainlen[cyc-1];
            // dbg("c", i, cyc, clen);
            choices *= (clen);
            choices %= mod;
        }
        choices += 1;
        choices %= mod;

        // dbg("res",i, choices);

        ans = (ans*choices)%mod;
    }

    print((ans+mod-1)%mod);

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