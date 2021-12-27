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

/**
 * count number of inversions in O(nlogn)
 * int numInversions(vector<T>& arr);
 * source: https://www.geeksforgeeks.org/counting-inversions/
 */

typedef int T;

long long numInversions(vector<T>& a) {
  if (a.size() == 1) return 0;
  vector<T> left = vector<T>(a.begin(), a.begin() + a.size() / 2);
  vector<T> right = vector<T>(a.begin() + a.size() / 2, a.end());
  long long swaps = numInversions(left) + numInversions(right);
  a.clear();
  int i=0, j=0;
  while (i < left.size() && j < right.size()) {
    if (left[i] < right[j]) {
      a.push_back(left[i++]);
    } else {
      a.push_back(right[j++]);
      swaps += left.size() - i;
    }
  }
  while (i < left.size()) {
    a.push_back(left[i++]);
  }
  while (j < right.size()) {
    a.push_back(right[j++]);
  }
  return swaps;
}

ll n;
ll calc(VI& v1, VI& v2) {
    unordered_map<int,int> m;
    REP(i,n) {
        m[v1[i]] = i+1;
    }
    vector<int> nv(n);
    REP(i,n) {
        nv[i] = m[v2[i]];
    }
    return numInversions(nv);
}

void run() {
    cin >> n;
    vector<int> v1(n),v2(n),v3(n);
    INP(v1,n);
    INP(v2,n);
    INP(v3,n);
    ll x = calc(v1,v2) + calc(v1,v3) + calc(v2,v3);
    x/=2;
    x = n*(n-1)/2 - x;
    print(x);
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