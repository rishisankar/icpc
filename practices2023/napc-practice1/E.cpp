#include <bits/stdc++.h>

using namespace std;
#define rep(i,a,b) for(int i = a; i < (b); ++i)
#define trav(a,x) for(auto &a: x)
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

const ull MOD = 1L<<60;

ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M*ull(1.L/M*a*b);
  return ret + M*(ret<0)- M*(ret>=(ll)M);
}

ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for(; e; b = modmul(b,b,mod), e/=2)
  if(e&1) ans = modmul(ans, b, mod);
  return ans;
}

bool isPrime(ull n) {
  if(n<2 || n % 6 % 4 != 1) return (n|1)==3;
  ull A[] = {2,325,9375,28178,450775,9780504,1795265022},
  s = __builtin_ctzll(n-1), d = n>>s;
  for(ull a:A) {
    ull p = modpow(a%n,d,n), i=s;
    while(p!=1 && p!= n-1 && a%n && i--)
      p = modmul(p,p,n);
    if(p!= n-1 && i != s) return 0;
  }
  return 1;
}

ull pollard(ull n ) {
  auto f = [n](ull x) { return modmul(x,x,n)+1; };
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while(t++ % 40 || __gcd(prd, n)==1) {
    if(x==y) x = ++i, y = f(x);
    if((q=modmul(prd, max(x,y)-min(x,y),n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}

vector<ull> factor(ull n) {
  if(n==1)return {};
  if(isPrime(n)) return{n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n/x);
  l.insert(l.end(), all(r));
  return l;
}

void dfs(int idx, ull so_far, vector<pair<ull, int>> &v, set<ull> &divs)
{
  if(idx==sz(v))
  {
    divs.insert(so_far);
    return;
  }

  ull cur=1;
  rep(i,0,v[idx].S+1)
  {
    dfs(idx+1,so_far*cur,v,divs);
    cur*=v[idx].F;
  }
}

vector<pair<ull, int>> mults(ull n) {
  vector<ull> primes = factor(n);
  unordered_map<ull, int> cnts;
  for(ull x: primes) {
    cnts[x]++;
  }
  vector<pair<ull, int>> m;
  for(auto x: cnts) {
    m.pb(x);
  }
  return m;
}

ull phi(ull x) {
  ull ans = 1;
  auto v = mults(x);
  for(auto [p, c]: v) {
    ans *= modmul(p-1, modpow(p, c-1, MOD), MOD);
  }
  return ans;
}

void solve()
{
  int N;
  cin >> N;
  vector<pair<ull, int>> v=mults(N);
  set<ull> divs;
  dfs(0,1,v,divs);
  ull ans = 0;
  for(ull x: divs) {
    ans += phi(x+1);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  rep(i,0,T)
  solve();
}