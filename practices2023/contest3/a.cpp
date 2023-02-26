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
const int MOD = 1e9+7;

void solve() {
  int n, k; cin >> n >> k;
  unordered_map<string,int> items;
  vector<unordered_set<int>> inv(n);
  rep(i, 0, k) {
    int x; string s;
    cin >> x >> s;
    int id;
    if (items.count(s)) id = items[s];
    else {
      items[s] = items.size();
      id = items[s];
    }
    inv[x].insert(id);
  }
  int m; cin >> m;
  vector<int> ord(m);
  rep(i,0,m) {
    string s; cin >> s;
    ord[i] = items[s];
  }

  dbg(ord);

  int j = 0;
  // visit stores l->r
  vector<int> s1(m);
  rep(i, 0, n) {
    while (j < m && inv[i].count(ord[j])) {
      s1[j] = i;
      ++j;
    }
  }

  if (j != m) {
    cout << "impossible\n";
    return;
  }

  dbg(s1);

  // visit stores r->l
  vector<int> s2(m);
  j = m-1;
  for (int i = n-1; i >= 0; --i) {
    while (j >= 0 && inv[i].count(ord[j])) {
      s2[j] = i;
      --j;
    }
  }

  dbg(s2);
  rep(i, 0, m) {
    if (s1[i] != s2[i]) {
      cout << "ambiguous\n";
      return;
    }
  }

  cout << "unique\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}