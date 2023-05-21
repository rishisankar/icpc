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
const int MOD = 998244353;

const int LIM = 1e6+5;
ll phi[LIM];
void calculatePhi() {
  rep(i, 0, LIM) phi[i] = i&1?i:i/2;
  for(int i = 3; i < LIM; i+=2) if(phi[i]==i)
    for(int j = i; j < LIM; j+=i) phi[j] -= phi[j]/i;
}

void solve() {
  int m, k;
  cin >> m >> k;
  ll coef = 0;
  rep(i, 2, k+1) {
    coef += phi[i];
    coef %= MOD;
  }
  coef *= 2;
  ++coef;
  coef %= MOD;
  dbg(coef);
  vector<ll> S(m+1);
  S[0] = 1; S[1] = 3;
  vector<ll> G(m+1);
  G[0] = 1;
  rep(i,1,m+1) G[i] = ((1+2*k) * G[i-1]) % MOD;
  rep(i,2,m+1) {
    ll z = (S[i-1] + ((2+4*coef)*G[i-2])%MOD)%MOD;
    S[i] = max(z,(2*G[i-1] + S[i-1])%MOD);
  }
  cout << S[m] << '\n';
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  calculatePhi();
  solve();
}