#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i  < (b); i++)
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{
  os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}'; 
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ")";
}

void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

typedef long double ld;
const int MOD = 1e9+7;

void solve() {
  int n; cin >> n;
  vector<ll> v(n);
  rep(i,0,n) {
    cin >> v[i];
  }
  ld best_avg = 0;
  ll sm = 0;
  for (int i = 1; i <= n; ++i) {
    sm += v[i-1];
    best_avg = max(best_avg, sm/(ld)i);
  }
  sm = 0;
  for (int i = 1; i <= n; ++i) {
    sm += v[n-i];
    best_avg = max(best_avg, sm/(ld)i);
  }
  cout << setprecision(20) << best_avg << "\n";
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}