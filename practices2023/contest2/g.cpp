#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for (auto& a: x)
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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;
#define double long double

void solve() {
  int n, k;
  cin >> n >> k;
  vector<double> p1(2*n+1, 0);
  vector<double> p2(2*n+1, 0);
  double odds[n];
  rep(i, 0, n) {
    cin >> odds[i];
  }
  sort(odds, odds+n);
  p1[n] = 1;
  double ans = 0, cur = 0;
  rep(i, 1, n+1) {
    rep(j, n-i+1, n+i) {
      p2[j+1] += p1[j]*odds[n-i];
      p2[j-1] += p1[j]*(1-odds[n-i]);
    }
    rep(j, n+k, 2*n+1) {
      cur += p2[j];
    }
    ans = max(ans, cur);
    cur = 0;
    swap(p1, p2);
    dbg(p1);
    p2 = vector<double>(2*n+1, 0);
  }
  cout << ans << endl;
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}