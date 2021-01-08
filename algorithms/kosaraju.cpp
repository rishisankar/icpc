// main func: kosaraju(adj_list, result)
// result should be empty to start
// result will contain K vectors, where K = # of strongly connected components, and result[i] is a list of vertices in the ith SCC

// example: graphs/cantinaofbabel.cpp

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

void kosaraju(vector<vector<int>>& adj_list, vector<vector<int>>& result) {
    int N = adj_list.size();
    if (N == 0) return;

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
    
}