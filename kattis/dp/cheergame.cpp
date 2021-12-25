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

int n, t, m;

//dp[i][j][k] = best score after i minutes, assuming used j cheers so far. k = -4..-1 = you won last few rounds, k = 1...4 = opponent won
vector<vector<unordered_map<int,PII>>> dp;
vector<int> cts;

const PII worst = {0, 1000};

PII maxScore(PII p1, PII p2) {
    if (p1.first - p1.second > p2.first - p2.second) return p1;
    else if (p1.first - p1.second < p2.first - p2.second) return p2;
    else if (p1.first > p2.first) return p1;
    else return p2;
}

PII solve(int a, int b, int c) {
    if (dp[a][b][c].first != -1) return dp[a][b][c];
    if (a == 0) return dp[a][b][c] = {0, 0};
    if (a == 45) c = 0;
    PII bestScore = worst;
    // 1) choose to score
    int cost = cts[a-1] + 1;
    if (cost <= n && cost <= b) {
        int newc = c;
        int plusScore = 0;
        if (c == -4) {
            newc = 0;
            plusScore = 1;
        } else {
            if (c > 0) newc = 0;
            --newc;
        }
        PII newScore = solve(a-1, b-cost, newc);
        newScore.first += plusScore;
        bestScore = maxScore(bestScore, newScore);
    }
    // 2) choose to block
    cost = cts[a-1];
    if (cost <= n && cost <= b) {
        PII newScore = solve(a-1, b-cost, 0);
        bestScore = maxScore(bestScore, newScore);
    }
    // 3) choose to lose
    if (cts[a-1] > 0) {
        int newc = c;
        int plusScore = 0;
        if (c == 4) {
            plusScore = 1;
            newc = 0;
        } else {
            if (c < 0) newc = 0;
            ++newc;
        }
        PII newScore = solve(a-1, b, newc);
        newScore.second += plusScore;
        bestScore = maxScore(bestScore, newScore);
    }
    
    return dp[a][b][c] = bestScore;
}

void run() {
    cin >> n >> t >> m;
    dp.resize(91, vector<unordered_map<int,PII>>(n*t+1));
    REP(j, 91 ) {
        REP(k, n*t+1) {
            for (int i = -4 ; i <= 4; ++i) {
                dp[j][k][i] = {-1,-1};
            }
        }
    }
    cts.assign(90, 0);
    REP(j, m) {
        int a,b; cin >> a >> b;
        for (int i = a; i < b; ++i) {
            ++cts[i];
        }
    }
    PII res = solve(90, n*t, 0);
    print(res.first,res.second);
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