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

vector<pii> dirs;

// bf
int bfg(pii s, pii f, int n, int M) {
  if (s == f) return 0;
  int MD = 10;
  if (s.F > MD) {
    int tmp = s.F-MD;
    s.F -= tmp;
    f.F -= tmp;
    n -= tmp;
  }
  if (s.S > MD) {
    int tmp = s.S-MD;
    s.S -= tmp;
    f.S -= tmp;
    M -= tmp;
  }
  n = min(n, f.F + MD);
  M = min(M, f.S+MD);
  
  dbg(s,f,n,M);

  map<pii, int> m;
  vector<vector<int>> adj(n*M);
  rep(i,0,n) {
    rep(j,0,M) {
      m[mp(i,j)] = m.size();
    }
  }
  for (auto k : m) {
    pii p = k.first;
    for (pii d : dirs) {
      pii nx = {p.F + d.F, p.S + d.S};
      if (nx.F < 0 || nx.S < 0 || nx.F >= n || nx.S >= M) continue;
      adj[k.S].push_back(m[nx]);
    }
  }

  queue<pii> q;
  vector<bool> visited(n*M, false);
  q.push({m[s], 0});
  visited[m[s]] = true;
  while (!q.empty()) {
    pii t = q.front();
    q.pop();
    for (int k : adj[t.F]) {
      if (visited[k]) continue;
      visited[k] = true;
      if (k == m[f]) return t.S+1;
      q.push({k,t.S+1});
    }
  }
  return -1;
}
int solve() {
  int nx, ny, kx, ky, cx, cy;
  cin >> nx >> ny >> kx >> ky >> cx >> cy;

  int x = abs(cx-kx);
  int y = abs(cy-ky);
  if (y > x) {
    swap(x,y);
    swap(nx,ny);
    swap(kx,ky);
    swap(cx,cy);
  }
  if (cx-kx < 0) {
    cx = nx-1-cx;
    kx = nx-1-kx;
  }
  if (cy-ky < 0) {
    cy = ny-1-cy;
    ky = ny-1-ky;
  }
  int k = x-y;
  dbg(nx, ny, kx, ky, cx, cy);

  if (x < 30 && y < 30) {
    // bf
    dbg("case 0", x, y);
    return bfg({kx,ky}, {cx,cy}, nx,ny);
  }

  if (y - k == 0) {
    dbg("case 1",x,y,k);
    return k;
  } else if (y - k < 0) {
    dbg("case 2", x,y,k);
    if (x%2 == 0) {
      assert(x > 25);
      if ((x/2) % 2 == y%2) return x/2;
      else return x/2+1;
    } else {
      if ((x/2) % 2 == y%2) return x/2+1;
      else return x/2+2;
    }
  } else {
    dbg("case 2", x,y,k);
    int ans = 0;
    if (k - 5 > 0) {
      ans += (k-5);
      kx += 2*(k-5);
      ky += (k-5);
    }
    // new position: 
    if ((y-k) / 3 - 5 > 0) {
      int mvs = ((y-k) / 3) - 5;
      ans += mvs*2;
      kx += mvs*3;
      ky += mvs*3;
    }
    x = abs(cx-kx);
    y = abs(cy-ky);
    assert(x < 30 && y < 30);
    return ans + bfg({kx,ky}, {cx,cy}, nx, ny);
  }
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);

  dirs.push_back({-2,1});
  dirs.push_back({-2,-1});
  dirs.push_back({2,1});
  dirs.push_back({2,-1});
  dirs.push_back({1,2});
  dirs.push_back({1,-2});
  dirs.push_back({-1,2});
  dirs.push_back({-1,-2});

  int x = solve();
  cout << x << '\n';
}