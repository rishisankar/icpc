#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

template<class T> T edmondsKarp(vector<unordered_map<int, T>>& graph, int source, int sink) {
  assert(source != sink);
  T flow = 0;
  vi par(sz(graph)), q=par;
  for (;;) {
    fill(all(par), -1);
    par[source] = 0;
    int ptr = 1;
    q[0] = source;
    rep(i,0,ptr) {
      int x = q[i];
      for (auto e : graph[x]) {
        if (par[e.first] == -1 && e.second > 0) {
          par[e.first] = x;
          q[ptr++] = e.first;
          if (e.first == sink) goto out;
        }
      }
    }
    return flow;
out:
    T inc = numeric_limits<T>::max();
    for (int y = sink; y != source; y = par[y])
      inc = min(inc, graph[par[y]][y]);
    flow += inc;
    for (int y = sink; y != source; y = par[y]) {
      int p = par[y];
      if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
      graph[y][p] += inc;
    }
  }
}

int n,I,g,s,m,r;

int gn(int loc, int t) {
  return loc * (s+1) + t;
}

void run() {
  cin >> n;
  cin >> I >> g >> s;
  --I;
  cin >> m;
  vector<int> locs(m);
  for (int i = 0; i < m; ++i) {
    cin >> locs[i];
    locs[i]--;
  }
  cin >> r;

  int nod = n * (s+1) + 2;
  vector<unordered_map<int, int>> graph(nod);
  int source = nod-2;
  int sink = nod-1;

  for (int i = 0; i < r; ++i) {
    int a,b,p,t;
    cin >> a >> b >> p >> t;
    --a; --b;
    for (int j = 0; j + t <= s; ++j) {
      graph[gn(a, j)][gn(b, j+t)] = p;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < s; ++j) {
      graph[gn(i, j)][gn(i, j+1)] = g;
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= s; ++j) {
      graph[gn(locs[i], j)][sink] = g;
    }
  }

  graph[source][gn(I, 0)] = g;

  int res = edmondsKarp(graph, source, sink);

  cout << res << '\n';

}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int tests; cin >> tests;
  for (int i = 0; i < tests; ++i) run(); 
}