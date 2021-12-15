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

// O(log(min(a,b)))
ll gcd(ll a, ll b) {
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 

// note that lcm(i, j) = ij / gcd(i,j)

// return gcd(a,b) and solve for integer x,y: ax+by=gcd(a,b)
ll euclidean(ll a, ll b, ll &x, ll &y) {

    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    ll x1,y1;
    ll gcd_ = euclidean(b%a, a, x1, y1);

    x = y1 - (b/a) * x1;
    y = x1;

    return gcd_;

}

// only exists if gcd(a,m) = 1 !! otherwise return -1
ll modularInverse(ll a, ll m) {
    ll x,y;
    ll g = euclidean(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m; // shift x to positive in case it is negative
}

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int t; cin >> t;
    REP(tests, t) {
        ll k, c; cin >> k >> c;
        if (gcd(c,k) != 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        ll i = modularInverse(c, k);
        if (k == 1) i = 2;
        if (c == 1) {
            if (k == 1000000000LL) {
                cout << "IMPOSSIBLE\n";
                continue;
            }
            i = k+1;
        }
        cout << i << '\n';
    }

}