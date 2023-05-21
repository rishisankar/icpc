const ll INF = 1000000000000000000LL;
void dijkstra(int s, vector<ll> &d, vector<int> &p, vector<vector<pair<int, ll>>>& adj) {
  int n = adj.size();
  d.assign(n, INF);
  p.assign(n, -1);
  d[s] = 0;
  using pii = pair<ll, int>;
  priority_queue<pii, vector<pii>, greater<pii>> q;
  q.push({0,s});
  while(!q.empty()) {
    int v = q.top().second;
    ll d_v = q.top().first;
    q.pop();
    if(d_v != d[v]) continue;
    for(auto edge: adj[v]) {
      int to = edge.first;
      ll len = edge.second;
      if(d[v] + len < d[to]) {
        d[to] = d[v] + len;
        p[to] = v;
        q.push({d[to], to});
      }
    }
  }
}