#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for(auto &a: x)
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

template<typename T> ostream& operator << (ostream &os, const vector<T> &v) { os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;

void fail() {
  cout << "impossible\n";
  exit(0);
}

vector<pair<ll, bool>> vals; 
int n;
vector<int> par;
vector<vector<int>> adj;

void test(int x) {
  for (int child : adj[x]) {
    test(child);
  }
  int numNotExact = 0;
  ll sumVals = 0;
  for (int child : adj[x]) {
    if (!vals[child].S) ++numNotExact;
    sumVals += vals[child].F;
  }
  if (vals[x].S) {
    if (adj[x].size() == 0) return;
    ll k = vals[x].F;
    if (sumVals == k) {
      return;
    } else if (sumVals > k) {
      fail();
    } else {
      if (numNotExact > 1 || numNotExact == 0) fail();
    }
  } else {
    if (adj[x].size() == 0) return;
    if (numNotExact == 0) {
      vals[x] = {sumVals, true};
    } else if (numNotExact == 1) {
      vals[x] = {sumVals, false};
    } else {
      vals[x] = {sumVals, false};
    }
  }

}

void solve()
{
  cin >> n;
  par.assign(n,-1);
  adj.resize(n);
  rep(i,0,n-1) {
    int x; cin >> x;
    --x;
    par[i+1] = x;
    adj[x].push_back(i+1);
  }
  vals.resize(n);
  rep(i, 0, n) {
    ll x; cin >> x;
    if (x == 0) {
      vals[i] = {1, false};
    } else {
      vals[i] = {x, true};
    }
  }
  dbg(vals);

  test(0);
  if (vals[0].S == false) fail();

  dbg(vals);

  stack<int> s;
  s.push(0);
  while (!s.empty()) {
    int t = s.top();
    if (vals[t].S == false) fail();
    s.pop();
    if (adj[t].size() == 0) continue;
    int numNotExact = 0;
    ll sumVals = 0;
    for (int child : adj[t]) {
      if (!vals[child].S) ++numNotExact;
      sumVals += vals[child].F;
    }
    if (numNotExact > 1) {
      // set all childs to min
      if (sumVals != vals[t].F) fail();
      for (int child : adj[t]) {
        if (!vals[child].S) vals[child].S = true;
      }
    } else if (numNotExact == 1) {
      for (int child : adj[t]) {
        if (!vals[child].S) {
          vals[child] = {vals[child].F+vals[t].F-sumVals, true};
        }
      }
    }
    for (int child : adj[t]) s.push(child);
  }
  dbg(vals);
  rep(i,0,n) {
    cout << vals[i].F << '\n';
  }
}

int main()
{
  solve(); 
}