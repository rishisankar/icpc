#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); ++i)
#define trav(a,x) for(auto& a:x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os<< '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream & operator<<(ostream &os, const vector<T> &v) {
  os << '{';
  string sep;
  for(const auto &x: v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
  cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const ll mod = 998244353;

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b=b*b%mod, e/=2)
    if (e&1) ans = ans*b%mod;
  return ans;
}
const int D = 24;

ll dp[D+1][2];

ll count(int mask, ll m) {
  ll ans = (m&mask == mask); // for no diff bit
  // dp[i][j] = # ways to set first i bits st. (j = 1 less m or 0 equal) and all bits of mask are valid
  dp[0][0] = 1;
  dp[0][1] = 0;
  rep(i,1,D+1) {
    int j = D-i;
    bool maskSet = (mask>>j)&1;
    bool mSet = (m>>j)&1;
    if (maskSet && mSet) {
      dp[i][0] = dp[i-1][0];
      dp[i][1] = dp[i-1][1];
    } else if (maskSet) {
      dp[i][0] = 0;
      dp[i][1] = dp[i-1][1];
    } else if (mSet) {
      dp[i][0] = dp[i-1][0];
      dp[i][1] = dp[i-1][0] + 2*dp[i-1][1];
    } else {
      dp[i][0] = dp[i-1][0];
      dp[i][1] = 2*dp[i-1][1];
    }
  }
  return dp[D][0] + dp[D][1];
}

const int MX = 6000000;

void solve() {
  ll N, K, M; cin >> N >> K >> M;
  if (K > 25) {
    cout << "0\n";
    return;
  }
  vector<ll> fact(MX);
  vector<ll> ifact(MX);
  fact[0] = fact[1] = 1;
  rep(i,2,MX) fact[i] = (fact[i-1] * i) % mod;
  ifact[MX-1] = modpow(fact[MX-1], mod-2);
  for(int i = MX-2; i >= 0; i--) {
    ifact[i] = (ifact[i+1]*(i+1))%mod;
  }
  vector<ll> prec(D+1);
  rep(i,0,(1<<D)) {
    int ind = __builtin_popcount(i);
    ll ct = count(i,M);
    if (ct - N == 0) prec[ind] += fact[N];
    else if (ct - N > 0) {
      prec[ind] += fact[ct] * ifact[ct-N];
    }
    prec[ind] %= mod;
  }
  ll ans = 0;
  rep(m,K,D) {
    rep(k, m, D) {
      ll val = (((k-m)&1) ? (mod-1) : 1);
      val *= fact[k]; val %= mod;
      val *= ifact[m]; val %= mod;
      val *= ifact[k-m]; val %= mod;
      val *= prec[k]; val %= mod;
      ans = (ans+val)%mod;
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}