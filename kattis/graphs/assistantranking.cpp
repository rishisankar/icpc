#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void finish_time_dfs(int vertex, vector<vector<int>>& adj_list, vector<bool>& visited, stack<int>& s) {
    if (visited[vertex]) return;
    visited[vertex] = true;

    for (int i = 0; i < adj_list[vertex].size(); ++i) {
        finish_time_dfs(adj_list[vertex][i], adj_list, visited, s);
    }

    s.push(vertex);
}

void reverse_dfs(int vertex, vector<vector<int>>& adj_list, int scc_count, vector<bool>& visited, vector<vector<int>>& result) {
    if (visited[vertex]) return;
    visited[vertex] = true;
    result[scc_count].push_back(vertex);

    for (int i = 0; i < adj_list[vertex].size(); ++i) {
        reverse_dfs(adj_list[vertex][i], adj_list, scc_count, visited, result);
    }
}

int kosaraju(vector<vector<int>>& adj_list, vector<vector<int>>& result) {
    int N = adj_list.size();
    if (N == 0) return 0;

    stack<int> s;
    vector<bool> visited(N, false);
    for (int i = 0; i < N; ++i) {
        finish_time_dfs(i, adj_list, visited, s);
    }

    // reverse adj list
    vector<vector<int>> transpose(N);
    for (int i = 0; i < N; ++i) {
        for (int j : adj_list[i]) {
            transpose[j].push_back(i);
        }
    }

    fill(visited.begin(), visited.end(), false);
    result.resize(N);
    int scc_count = 0;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (visited[v]) continue;
        reverse_dfs(v, transpose, scc_count, visited, result);
        ++scc_count;
    }
    result.resize(scc_count);

    return scc_count;
    
}

int main() {
  
  ll n,k; cin >> n >> k;

  vector<ll> a(n), b(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];

  // nodes: [0...n-1] for the people, [n...n+P-1] for unique x, [n+P ... n+P+Q] for unique y
  unordered_set<int> c1,c2;
  for (int i = 0; i < n; ++i) {
    c1.insert(a[i]);
    c2.insert(b[i]);
  }
  int P = c1.size();
  int Q = c2.size();
  int N = n + P + Q;
  vector<vector<int>> adj(N);
  vector<int> cv1, cv2;
  for (int i : c1) cv1.push_back(i);
  for (int i : c2) cv2.push_back(i);
  sort(cv1.begin(), cv1.end());
  sort(cv2.begin(), cv2.end());
  // for (int x : cv1) cout << x << " "; cout << '\n';
  // for (int x : cv2) cout << x << " "; cout << '\n';
  for (int i = 0; i < P-1; ++i) {
    adj[n+i].push_back(n+i+1);
  }
  for (int i = 0; i < Q-1; ++i) {
    adj[n+P+i].push_back(n+P+i+1);
  }
  unordered_map<int,int> cr1, cr2;
  for (int i = 0; i < P; ++i) cr1[cv1[i]] = i;
  for (int i = 0; i < Q; ++i) cr2[cv2[i]] = i;

  for (int i = 0; i < n; ++i) {
    // cout << i << " " << a[i] << " " << cr1[a[i]] << " " << b[i] << " " << cr2[b[i]] << "\n";
    adj[cr1[a[i]] + n].push_back(i);
    adj[cr2[b[i]] + n+P].push_back(i);
  }

  vector<pair<int,int>> Ax(n);
  for (int i = 0; i < n; ++i) {
    Ax[i] = {a[i], i};
  }
  sort(Ax.begin(), Ax.end());
  int p = 0;
  for (int i = 0; i < n; ++i) {
    while (p < P && Ax[i].first + k >= cv1[p]) ++p;
    if (p < P) {
      // cout << "addingP\n";
      adj[Ax[i].second].push_back(n+p);
    }
  }

  vector<pair<int,int>> Bx(n);
  for (int i = 0; i < n; ++i) {
    Bx[i] = {b[i], i};
  }
  sort(Bx.begin(), Bx.end());
  p = 0;
  for (int i = 0; i < n; ++i) {
    while (p < Q && Bx[i].first + k >= cv2[p]) ++p;
    if (p < Q) {
      // cout << "addingQ\n";
      adj[Bx[i].second].push_back(n+P+p);
    }
  }

  vector<vector<int>> result;

  int scc = kosaraju(adj, result);

  int ct = 0;
  for (int i = 0; i < result.size(); ++i) {
    bool valid = false;
    for (int j = 0; j < result[i].size(); ++j) {
      // cout << result[i][j] << ' ';
      if (result[i][j] < n) valid = true; 
    }
    // cout << '\n';
    if (valid) ++ct;
  }

  cout << ct << '\n';
  



}