#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

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
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

/*

Run linear sieve.
{P} stores all primes that the xi are divisible by.
Using linear sieve, figure out which numbers <= X are combinations of {P} / count # of primes from P
For each of these numbers i:
  Iterate through all multiples of i <= X
  Figure out how many of the xi are divisible by i
  Number of pairs this reaches is given by ^ choose 2
  Store in I/E sum
Inclusion Exclusion:
  [Number of pairs] - [Number of pairs divisible by 1 prime] + [Number of pairs divisible by 2 primes] - ...

Complexity: O(X log X)

or mobius inversion!
special case for 1s --> assume all removed

sum(i:1-n) sum(j:1-n) [gcd(vi, vj) == 1]
sum(i:1-n) sum(j:1-n) sum(d|gcd(vi,vj)) mu(d)
sum(i:1-n) sum(j:1-n) sum(d:1-X) [d|vi] [d|vj] mu(d)
sum(d:1-X) mu(d) sum(i:1-n)[d|vi] sum(j:1-n)[d|vj]

sum(j:1-n)[d|vj] calculate by considering d, 2d, 3d, ... and adding # vi that equal any of these
*/

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

void run() {
    int n; cin >> n;
    ll n1s = 0;
    vector<ll> v;
    rep(i,0,n) {
        ll x; cin >> x;
        if (x == 1) n1s++;
        else v.pb(x);
    }
    ll ans1 = n1s * (n-1) - (n1s)*(n1s-1)/2;
    ll ans = 0;
    n = v.size();
    ll X = maxe(v);
    vector<int> cts(X+1,0);
    for (ll x : v) {
        cts[x]++;
    }
    VLL mu; mu_1_to_n(X, mu);
    rep(d,1,X+1) {
        ll sm = 0;
        for (ll z = d; z <= X; z+=d) {
            sm += cts[z];
        }
        ans += mu[d] * sm * sm;
    }
    ans = ans/2 + ans1;
    print(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}