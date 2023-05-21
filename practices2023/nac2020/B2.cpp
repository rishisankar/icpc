#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); i++)
#define trav(a,x) for(auto& a:x)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os <<'(' <<p.F << ", " << p.S << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
  os << '{';
  string sep;
  for(const auto &x: v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const ll mod = 998244353;

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


ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
void solve() {
  int m,k; cin >> m >> k;
  vector<ll> mu;
  mu_1_to_n(k, mu);
  int e = 0;
  ll ans = 1;
  rep(i,1,k+1) {
    ans += (mu[i] * modpow(k/i*2+1, m)) % mod;
    ans %= mod;
    e -= mu[i];
  }
  cout << (ans+e+mod)%mod << '\n';
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}