#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(cont) cont.begin(), cont.end()
#define PB push_back

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
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;

// O(n) - find mobius function value for all from 1-N
void least_prime_factor(ll N, vector<ll> &lpf) {  // from sieve of eratosthenes code
    lpf.resize(N+1);
    fill(lpf.begin(), lpf.end(), 0); 
    for (ll i = 2; i <= N; i++) {
        // If it is a prime number 
        if (!lpf[i]) {
            for (ll j = i; j <= N; j += i) {
                // For all multiples which are not 
                // visited yet. 
                if (!lpf[j]) lpf[j] = i; 
            }
        }
    }
}
void mu_1_to_n(ll n, vector<ll> &mu) {
    mu.resize(n+1);
    mu[0] = 1;
    mu[1] = 1;
    vector<ll> lpf;
    least_prime_factor(n, lpf);
    for (ll i = 2; i <= n; ++i) {
        // if number has a squared prime factor
        if (lpf[i / lpf[i]] == lpf[i]) {
            mu[i] = 0LL;
        } else {
            mu[i] = -1LL * mu[i / lpf[i]];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    ll a,b,c,d;
    cin >> a >> b >> c >> d;

    vector<ll> mu;
    ll n = max(b,d);

    mu_1_to_n(n, mu);

    ll total = 0;
    OREP(i, n) {
        total += mu[i] * ((b/i)-((a-1)/i)) * ((d/i)-((c-1)/i));
    }

    cout << total << '\n';

}