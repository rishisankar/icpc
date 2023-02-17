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

pii parse(string& s) {
  int i = 0;
  string s1 = "", s2 = "";
  while (s[i] != '-' ) {
    s1+=s[i];
    ++i;
  }
  for (i = i+1; i < s.size(); ++i) {
    s2 += s[i];
  }
  int i1 = stoll(s1);
  int i2 = stoll(s2);
  return {i1,i2};

}

bool check(string s1, string s2) {
  pii p1 = parse(s1);
  pii p2 = parse(s2);
  if (p1.F == p2.F && p1.S == p2.S) return true;
  int m1 = (p1.F + p1.S)%4;
  int m2 = (p2.F+p2.S)%4;
  if (m1 == 1 || m1 == 2) {
    if (m2 == 1 || m2 == 2) {
      // dont swap
    } else {
      // swap
      p2 = {p2.S,p2.F};
    }
  } else {
    if (m2 == 1 || m2 == 2) {
      // swap
      p2 = {p2.S,p2.F};
    } else {
      // don't swap
    }
  }
  dbg(p1);
  dbg(p2);
  if (p1.F == 11 || p1.S == 11) {
    return false;
  }
  if (p2.F == 11 && p2.S == 11) return false;
  if (p1.F <= p2.F && p1.S <= p2.S) return true;
  return false;
  // else {
  //   pii n1,n2;
  //   if ((p1.F + p1.S )% 2 == 1) {
  //     n1 = {p1.F+1, p1.S};
  //     n2 = {p1.F, p1.S+1};
  //   } else {
  //     n1 = {p1.S, p1.F+1};
  //     n2 = {p1.S+1, p1.F};
  //   }
  //   if (n1.F == p2.F && n1.S == p2.S) return true;
  //   if (n2.F == p2.F && n2.S == p2.S) return true;
  //   return false;

  // }
}

void solve() {
  int n; cin >> n;
  vector<string> v(n);
  rep(i,0,n) {
    cin >> v[i];
  }
  if (v[0] == "11-11") {
    cout << "error 1\n";
    return;
  }
  for (int i = 0; i < n-1; ++i) {
    bool ok = check(v[i], v[i+1]);
    if (!ok) {
      cout << "error " << (i+2) << endl;
      return;
    }
  }
  cout << "ok\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}