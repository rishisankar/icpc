#include <bits/stdc++.h>
using namespace std;

const unsigned long long INF = LONG_MAX;

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<pair<int,int>>> adj(n+1, vector<pair<int,int>>());

  for (int i = 0; i < m; ++i) {
    int a,b,c;
    cin >> a >> b >> c;
    adj[a].push_back(make_pair(b, c));
    adj[b].push_back(make_pair(a, c));
  }


  set<pair<int,int>, less<pair<int,int>>> pq;

  vector<unsigned long long> dist(n+1, INF);
  vector<unsigned long long> prev(n+1, INF);

  pq.insert({0,1});
  dist[1] = 0;
  prev[1] = -1;

  while (!pq.empty()) {
    int cur = pq.begin()->second;
    pq.erase(pq.begin());

    for (pair<int,int> pair : adj[cur]) {
      int adj = pair.first;
      int adj_w = pair.second;
      if (dist[adj] > dist[cur] + adj_w) {
        pq.erase({dist[adj], adj});
        dist[adj] = dist[cur] + adj_w;
        prev[adj] = cur;
        pq.insert({dist[adj], adj});
      }
    }

  }

  vector<int> result;
  
  int cur = n;
  while (cur != -1) {
    if (prev[cur] == INF) {
      cout << -1 << endl;
      return 0;
    }
    result.push_back(cur);
    cur = prev[cur];
  }

  reverse(result.begin(), result.end());

  bool first = true;
  for (int i : result) {
    if (first) {
      first = false;
      cout << i;
    } else {
      cout << ' ' << i;
    }
  }
  cout << endl;
}