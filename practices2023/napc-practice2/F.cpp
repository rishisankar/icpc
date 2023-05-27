#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<(b) ; ++i)
#define trav(a,x) for(auto &a:x)
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

const int LIM = 20000000;
vi lp(LIM+1), pr;
void sieve() {
  for (int i =2; i <= LIM; ++i) {
    if (lp[i] == 0) {
      lp[i] = i; pr.push_back(i);
    }
    for (int j = 0; i*pr[j] <= LIM; ++j) {
      lp[i*pr[j]] = pr[j];
      if (lp[i] == pr[j]) break;
    }
  }
}

vi pi,ni;

vi par;

bool solve(int l, int r, int T) {
  if (l > r) return true;
  if (l == r) {
    par[l] = T;
    return true;
  }
  rep(i,0,r-l+1) {
    int t;
    if (i&1) {
      t = r - i/2;
    } else {
      t = l + i/2;
    }
    if (pi[t] < l && ni[t] > r) {
      par[t] = T;
      return solve(l,t-1,t) && solve(t+1,r,t);
    }
  }
  return false;
}

void run() {
  sieve();
  int n; cin >> n;
  par.resize(n,-1);
  vector<ll> v(n); rep(i,0,n) cin >> v[i];
  pi.assign(n,-1); ni.assign(n,n);
  unordered_map<int, int> m;
  rep(i,0,n) {
    int c = v[i];
    while (c != 1) {
      int g = lp[c];
      if (m.count(g)) {
        pi[i] = max(pi[i], m[g]);
      }
      m[g] = i;
      while (c%g==0)c/=g;
    }
  }
  m.clear();
  for (int i = n-1; i >= 0; --i) {
    int c = v[i];
    while (c!=1) {
      int g = lp[c];
      if (m.count(g)) {
        ni[i] = min(ni[i], m[g]);
      }
      m[g] = i;
      while (c%g==0)c/=g;
    }
  }
  if (!solve(0,n-1,-1)) {
    cout << "impossible\n";
    return;
  }
  rep(i,0,n) cout << par[i]+1 << ' ';
  cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  run();
}