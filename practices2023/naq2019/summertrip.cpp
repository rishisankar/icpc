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


const int MOD = 1e9+7;
void solve()
{
  string s; cin >> s;
  int n = s.size();
  vector<vector<int>> pos(26);
  rep(i,0,n) {
    pos[(s[i]-'a')].pb(i);
  }
  ll ans = 0;
  for (char c = 'a'; c <= 'z'; ++c) {
    if (pos[(c-'a')].size() == 0) continue; // not valid start
    // iterate until next occurrence of c, pick anything that hasn't been seen before
    for (int p : pos[(c-'a')]) {
      vector<bool> seen(26,false);
      for (int i = p+1; i < n && s[i] != c; ++i) {
        if (!seen[(s[i]-'a')]) ++ans;
        seen[(s[i]-'a')]=true;
      }
    }
  }
  cout << ans << "\n";
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}
