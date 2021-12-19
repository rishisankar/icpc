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

string toBinary(ll n) {
    string r;
    while (n!=0) {
        r = (n%2==0 ? "0" : "1") + r;
        n/=2;
    }
    return r;
}
ll countBits(ll i) {
    ll count = 0;
    while (i != 0) {
        count += (i & 1);
        i >>= 1;
    }
    return count;
}

int n;
ll L;
VVLL adj;
int gl;

int complement(int init) {
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res <<= 1;
        int nb = ((init >> (n-i-1)) & 1);
        if (nb == 0) res += 1;
    }
    return res;
}

void run() {
    cin >> n >> L;
    adj.assign(n, VLL(n));
    REP(i, n) {
        REP(j, n) {
            cin >> adj[i][j];
        }
    }

    if (n <= 7) {

        vector<int> nums;
        REP(i, n) {
            nums.PB(i);
        }
        do {
            ll ct = 0;
            for (int k = 0; k < nums.size()-1; ++k) {
                ct += adj[nums[k]][nums[k+1]];
            }
            ct += adj[nums[nums.size() - 1]][nums[0]];
            if (ct == L) {
                print("possible");
                return;
            }
        } while (next_permutation(all(nums)));
        print("impossible");
        return;
    }

    if (n % 2 == 0) {
        gl = n/2;
    } else {
        gl = (n-1)/2;
    }

    vector<vector<vector<unordered_set<ll>>>> dp(n, vector<vector<unordered_set<ll>>>(n, vector<unordered_set<ll>>((1<<n))));

    vector<int> masks;

    for (int i = 0; i < (1 << n); ++i) {
        if (countBits(i) == gl) {
            masks.PB(i);
            vector<int> nums;
            REP(j, n) {
                if (((i >> j) & 1) == 1) {
                    nums.PB(j);
                }
            }
            do {
                ll ct = 0;
                for (int k = 0; k < gl-1; ++k) {
                    ct += adj[nums[k]][nums[k+1]];
                }
                dp[nums[0]][nums[gl-1]][i].insert(ct);
            } while (next_permutation(all(nums)));
        }
    }
    // REP(i,n) {
    //     REP(j,n) {
    //         REP(k, (1<<n)) {
    //             cout << "dp" << i << ' ' << j << ' ' << toBinary(k) << ":";
    //             for (int g : dp[i][j][k]) {
    //                 cout << ' ' << g;
    //             }
    //             cout << '\n';
    //         }
    //     }
    // }

    int lb = 0, rb = 0;
    if (n % 2 == 1) {
        lb = 1; rb = n-1;
    }
    for (int p1s = lb; p1s <= rb; ++p1s) {
        for (int p1e = 1; p1e < n; ++p1e) {
            if (p1e == p1s) continue;
            for (int p2s = 1; p2s < n; ++p2s) {
                if (p2s == p1e || p2s == p1s) continue;
                for (int p2e = 1; p2e < n; ++p2e) {
                    if (p2e == p2s || p2e == p1e || p2e == p1s) continue;
                    for (int i : masks) {
                        if (((i >> p1s) & 1) != 1) continue;
                        if (((i >> p1e) & 1) != 1) continue;
                        if (((i >> p2s) & 1) != 0) continue;
                        if (((i >> p2e) & 1) != 0) continue;
                        if (n%2 == 1 && ((i&1) == 1)) continue;
                        int comp = complement(i);
                        if (n%2 == 1) {
                            if (comp % 2 == 1) {
                                --comp;
                            }
                        }
                        // dbg("trying",p1s,p1e,p2s,p2e,toBinary(i), toBinary(comp));
                        ll needed;
                        if (n%2==0) {
                            needed = L - adj[p1e][p2s] - adj[p2e][p1s];
                        } else {
                            needed = L - adj[0][p1s] - adj[p1e][p2s] - adj[p2e][0];
                        }
                        for (ll val : dp[p1s][p1e][i]) {
                            if (dp[p2s][p2e][comp].count(needed-val)) {
                                print("possible");
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    print("impossible");
    
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