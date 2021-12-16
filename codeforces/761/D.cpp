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

int query(int a, int b, int c) {
    print('?',a+1,b+1,c+1);
    cout.flush();
    int r;
    cin >> r;
    return r;
}

void run() {
    int n; cin >> n;

    int ci = -1, ii = -1;
    vector<int> queries(n, -1);
    vector<int> res(n, -1);
    REP(i, n/3) {
        int r = query(3*i, 3*i+1, 3*i+2);
        queries[i] = r;
        if (r == 0) {
            ii = i*3;
        } else {
            ci = i*3;
        }
    }


    int a1 = query(ci, ii, ii+1);
    int a2 = query(ci, ii, ii+2);
    int a3 = query(ci, ii+1, ii+2);
    if (a1 == a2 && a2 == a3) {
        // all imp  -> either ci is imposter or all 3 are imposter
        int b1 = query(ci+1, ii, ii+1);
        int b2 = query(ci+1, ii, ii+2);
        if (b1 == b2 && b1 == 0) {
            // all imp
            res[ii] = res[ii+1] = res[ii+2] = 0;
            int c1 = query(ci, ci+1, ii);
            int c2 = query(ci, ci+2, ii);
            int c3 = query(ci+1, ci+2, ii);
            if (c1 == c2 && c2 == c3) {
                // all crew
                res[ci] = res[ci+1] = res[ci+2] = 1;
            } else {
                if (c1 == 1) {
                    res[ci] = res[ci+1] = 1;
                    res[ci+2] = 0;
                } else if (c2 == 1) {
                    res[ci] = res[ci+2] = 1;
                    res[ci+1] = 0;
                } else if (c3 == 1) {
                    res[ci+1] = res[ci+2] = 1;
                    res[ci] = 0;
                }
            }
        } else if (b1 == b2 && b1 == 1) {
            // not all imp                
            res[ci+1] = 1;
            res[ii] = 1;
            res[ii+1] = res[ii+2] = 0;
            res[ci] = query(ii, ii+1, ci);
            res[ci+2] = query(ii, ii+1, ci+2);
        } else {
            res[ci+1] = 1;
            res[ii] = 0;
            if (b1 == 1) {
                res[ii+1] = 1;
                res[ii+2] = 0;
            } else {
                res[ii+1] = 0;
                res[ii+2] = 1;
            }
            res[ci] = query(ii+2, ii+1, ci);
            res[ci+2] = query(ii+2, ii+1, ci+2);
        }
    } else {
        int bd;
        res[ci] = 1;
        if (a1 == a2) {
            res[ii] = 1;
            res[ii+1] = res[ii+2] = 0;
            bd = ii+1;
        } else if (a1 == a3) {
            res[ii+1] = 1;
            res[ii] = res[ii+2] = 0;
            bd = ii;  
        } else {
            res[ii+2] = 1;
            res[ii] = res[ii+1] = 0;
            bd = ii;
        }
        res[ci+1] = query(ci, bd, ci+1);
        res[ci+2] = query(ci, bd, ci+2);
    }

    int crew = -1;
    int imp = -1;
    REP(i, res.size()) {
        if (res[i] == 0) imp = i;
        if (res[i] == 1) crew = i;
    }

    REP(x, n/3) {
        int i = 3*x;
        if (res[i] != -1 && res[i+1] != -1 && res[i+2] != -1) continue;

        int qq = queries[x];
        int other;
        int dmi, sbi;
        if (qq == 1) {
            dmi = crew;
            sbi = imp;
            other = 0;
        } else {
            dmi = imp;
            sbi = crew;
            other = 1;
        }
        int a1 = query(i,i+1,sbi);
        int a2 = query(i+1,i+2,sbi);
        if (a1 == qq && a2 == qq) {
            res[i] = res[i+1] = res[i+2] = qq;
        } else if (a1 == qq) {
            res[i] = res[i+1] = qq;
            res[i+2] = other;
        } else if (a2 == qq) {
            res[i+1] = res[i+2] = qq;
            res[i] = other;
        } else {
            res[i+1] = other;
            res[i] = res[i+2] = qq;
        }
    }

    // REP(i, n) {
    //     if (res[i] != -1) continue;
    //     res[i] = query(i, crew, imp);
    // }

    vector<int> imposters;
    REP(i, res.size()) {
        if (res[i] == 0) {
            imposters.PB(i);
        }
    }
    cout << "! " << imposters.size();
    REP(i, imposters.size()) {
        cout << ' ' << (imposters[i]+1);
    }
    cout << '\n';
    cout.flush();

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    ll t; cin >> t;
    //ll t=1;
    REP(tests,t) run();
}