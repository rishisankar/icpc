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

typedef long double ld;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{
  os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}'; 
}


const int MOD = 1e9+7;
void solve()
{
  int n, m; cin >> n >> m;
  vector<unordered_set<int>> adj(n);
  rep(i,0,m) {
    int a,b; cin >> a >> b;
    --a; --b;
    adj[a].insert(b);
    adj[b].insert(a);
  }
  vector<int> conn(n, -1);
  
  int cp = 0;
  rep(i,0,n) {
    if (conn[i] != -1) continue;
    stack<int> s;
    s.push(i);
    conn[i] = cp;
    while (!s.empty()) {
      int t = s.top();
      s.pop();
      for (int x : adj[t]) {
        if (conn[x] == -1) {
          s.push(x);
          conn[x] = cp;
        }
      }
    }
    ++cp;
  }

  vector<int> lens(cp,0);
  rep(i,0,n) {
    lens[conn[i]]++;
  }

  ld ans = 0;
  rep(i, 0, cp) {
    if (lens[i] ==1 ) continue;
    ans += lens[i] / ((ld)n) * (lens[i]-1) / ((ld)(n-1));
  }

  cout << setprecision(10) << ans << '\n';
}

int main()
{
  solve();
}