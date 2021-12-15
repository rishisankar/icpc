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

bool verifysolution(VVLL v) {
    REP(i, 4) {
        for (int j = 1; j < 5; ++j) {
            if (v[i][j] != 0) continue;
            REP(k, 4) {
                if (i == k || v[k][j] == 0) continue;

                // i0 * kj / k0 = ij / i0
                ll test = v[i][0] * v[k][j];
                if (test % v[k][0] != 0) {
                    return false;
                } else {
                    v[i][j] = test / v[k][0];
                }
            }
        }
    }
    REP(i, 4) {
        REP(j, 5) {
            REP(k, 4) {
                if (i == k) continue;
                REP(l, 5) {
                    if (j == l) continue;
                    if (v[i][j] * v[k][l] != v[i][l] * v[k][j]) return false;
                }
            }
        }
    }

    REP(i, 5) {
        cout << v[0][i] << " " << v[1][i];
        if (i != 4) cout << " ";
    }
    cout << '\n';
    REP(i, 5) {
        cout << v[2][i] << " " << v[3][i];
        if (i != 4) cout << " ";
    }
    cout << '\n';
    return true;
}

ll readval() {
    string s;
    cin >> s;
    if (s == "_") {
        return 0;
    } else {
        return stoll(s);
    }
}

void run() {
    VVLL v(4, vector<ll>(5));
    REP(i, 5) {
        v[0][i] = readval();
        v[1][i] = readval();
    }
    REP(i, 5) {
        v[2][i] = readval();
        v[3][i] = readval();
    }

    REP(i, 5) {
        bool many = true;
        REP(j, 4) {
            if (v[j][i] != 0) many = false;
        }
        if (many) {
            print("many");
            return;
        }
    }
    REP(i, 4) {
        bool many = true;
        REP(j, 5) {
            if (v[i][j] != 0) many = false;
        }
        if (many) {
            print("many");
            return;
        }
    }

    bool done = false;
    while (!done) {
        done = true;
        REP(i, 4) {
            REP(j, 5) {
                if (v[i][j] != 0) continue;
                REP(k, 4) {
                    if (i == k || v[k][j] == 0) continue;
                    REP(l, 5) {
                        if (j == l) continue;
                        if (v[k][l] == 0 || v[i][l] == 0) continue;
                        v[i][j] = v[i][l] * v[k][j] / v[k][l];
                        done = false;
                    }
                }
            }
        }
    }

    vector<unordered_set<ll>> choices(4);

    REP(i, 4) {
        if (v[i][0] != 0) {
            choices[i].insert(v[i][0]);
            continue;
        }

        REP(j, 4) {
            if (j == i || v[j][0] == 0) continue;
            REP(k, 5) {
                if (k == 0 || v[i][k] == 0) continue;

                ll b = v[j][0] * v[i][k];

                for (ll a=1; a<=sqrt(b); ++a) {
                    if (b%a == 0) {
                        choices[i].insert(a);
                        if (b/a != a) choices[i].insert(b/a);
                    }
                }
            }
        }

    }

    ll res = 0;
    for (ll a : choices[0]) {
        v[0][0] = a;
        for (ll b : choices[1]) {
            v[1][0] = b;
            for (ll c : choices[2]) {
                v[2][0] = c;
                for (ll d : choices[3]) {
                    v[3][0] = d;
                    if (verifysolution(v)) {
                        return;
                    }
                }
            }
        }
    }

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