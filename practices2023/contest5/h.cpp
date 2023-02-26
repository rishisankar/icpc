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
  string grid[10];
  rep(i, 0, 10) {
    cin >> grid[i];
  }
  string sub[10];
  rep(i, 0, 10) {
    cin >> sub[i];
  }
  vector<pii> stars;
  rep(i, 0, 10) {
    rep(j, 0, 10) {
      if(sub[i][j] == '*') {
        stars.push_back({i, j});
      }
    }
  }
  if(stars.size() != 20) {
    cout << "invalid" << endl;
    return;
  }
  rep(i, 0, 20) {
    rep(j, i+1, 20) {
      if(abs(stars[i].F-stars[j].F) <= 1 && abs(stars[i].S-stars[j].S) <= 1) {
        cout << "invalid" << endl;
        return;
      }
    }
  }

  rep(i, 0, 10) {
    int count = 0;
    rep(j, 0, 10) {
      if(sub[i][j] == '*') count++;
    }
    if(count != 2) {
      cout << "invalid" << endl;
      return;
    }
  }
  rep(i, 0, 10) {
    int count = 0;
    rep(j, 0, 10) {
      if(sub[j][i] == '*') count++;
    }
    if(count != 2) {
      cout << "invalid" << endl;
      return;
    }
  }
  int counts[10]{};
  rep(i, 0, 10) {
    rep(j, 0, 10) {
      if(sub[i][j] == '*') {
        int num = grid[i][j]-'0';
        counts[num]++;
      }
    }
  }
  rep(i, 0, 10) {
    if(counts[i] != 2) {
      cout << "invalid" << endl;
      return;
    }
  }
  cout << "valid" << endl;
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}