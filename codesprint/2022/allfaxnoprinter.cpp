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

struct job {
    job(int t, int l, int i_) : s(t), e(t+l), i(i_) {}
    ll s, e, i; // s = start time, e = end time (exclusive) = s+l
};

void run() {
    int n,k; cin >> n >> k;
    auto compare1 = [](job a, job b) { return a.e < b.e; };
    auto compare2 = [](job a, job b) { return a.e > b.e; };
    priority_queue<job, vector<job>, decltype(compare1)> pq1(compare1); // latest end time at top
    priority_queue<job, vector<job>, decltype(compare2)> pq2(compare2); // earliest end time at top
    vector<bool> valid(n, true);
    int ml = k;

    int mlo = k;
    priority_queue<job, vector<job>, decltype(compare2)> pqo(compare2); // earliest end time at top
    int flo = 0;

    int fails = 0;
    REP(i, n) {
        int t,l; cin >> t >> l;
        job j(t,l,i);
        while (!pq2.empty() && pq2.top().e <= t) {
            if (valid[pq2.top().i]) {
                ++ml;
            }
            pq2.pop();
        }
        while (!pqo.empty() && pqo.top().e <= t) {
            pqo.pop();
            ++mlo;
        }
        if (mlo > 0) {
            --mlo;
            pqo.push(j);
        } else {
            ++flo;
        }
        pq1.push(j);
        pq2.push(j);
        --ml;
        if (ml < 0) {
            ++ml;
            valid[pq1.top().i] = false;
            pq1.pop();
            ++fails;
        }
        print(flo-fails);
    }
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