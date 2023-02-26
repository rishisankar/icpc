#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define pb push_back
using namespace std;
typedef long long ll;

const int MOD=1000000000+7;

vector<bool> visitFirst;
vector<vector<int>> childs;

void solve(int x) {
  if (visitFirst[x]) {
    cout << (x+1) << ' ';
    for (int c : childs[x]) {
      solve(c);
    }
  } else {
    for (int c : childs[x]) {
      solve(c);
    }
    cout << (x+1) << ' ';
  }
}

void run() {
  int n, m; cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; ++i) {
    int a,b; cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  childs.resize(n);
  visitFirst.assign(n, false);

  queue<pair<int, bool>> q;
  vector<bool> visited(n, false);
  visited[0] = true;
  visitFirst[0] = true;
  q.push({0, true});
  while (!q.empty()) {
    pair<int,bool> t = q.front();
    q.pop();
    for (int x : adj[t.first]) {
      if (visited[x]) continue;
      visited[x] = true;
      visitFirst[x] = !t.second;
      q.push({x, visitFirst[x]});
      childs[t.first].push_back(x);
    }
  }
  solve(0);
  cout << '\n';
}

int main() {
  run();
}

