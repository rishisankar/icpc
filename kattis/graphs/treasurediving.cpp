#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const long long INF = 10000000000000LL;
void dijkstra(int s, vector<long long> & d, vector<int> & p, vector<vector<pair<int,long long>>> &adj) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    using pii = pair<long long, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        long long d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            long long len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

void run() {

  int n, m; cin >> n >> m;
  vector<vector<pair<int,ll>>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a,b; ll w;
    cin >> a >> b >> w;
    adj[a].push_back({b,w});
    adj[b].push_back({a,w});
  }
  int I; cin >> I;
  vector<int> idols(I);
  unordered_set<int> locs;
  locs.insert(0);
  for (int i = 0; i < I ; ++i) {
    cin >> idols[i];
    locs.insert(idols[i]);
  }
  int N = locs.size();
  vector<vector<ll>> cst(N, vector<ll>(N));
  vector<int> vlocs;
  for (int i : locs) vlocs.push_back(i);
  sort(vlocs.begin(), vlocs.end());
  for (int i = 0; i < N; ++i) {
    vector<long long> d;
    vector<int> p;
    dijkstra(vlocs[i], d, p, adj);
    for (int j = 0; j < N; ++j) {
      cst[i][j] = d[vlocs[j]];
    }
  }
  vector<int> icts(N, 0);
  for (int i : idols) {
    for (int j = 0; j < N; ++j) {
      if (vlocs[j] == i) icts[j]++;
    }
  }

  // for (int i = 0; i < N; ++i) {
  //   for (int j = 0; j < N; ++j) {
  //     cout << cst[i][j] << ' ';
  //   }
  //   cout << '\n';
  // }

  vector<int> perms;
  for (int i = 0; i < N; ++i) {
    perms.push_back(i);
  }

  int best = 0;
  int capc; cin >> capc;

  do {
    int cp = 0;
    int cost = 0;
    int amt = 0;
    for (int i = 0; i < perms.size(); ++i) {
      cost += cst[cp][perms[i]];
      amt += icts[perms[i]];
      if (cost > capc) break;
      cp = perms[i];
      if (cp == 0) {
        best = max(best, amt);
        break;
      }
    }
  } while (next_permutation(perms.begin(), perms.end()));

  cout << best << '\n';

}


int main() {
  int t; cin >> t;
  for (int i = 0 ;i < t; ++i) {
    run();
  }
}