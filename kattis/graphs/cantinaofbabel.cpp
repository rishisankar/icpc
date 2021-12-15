// goal: take max strongly connected component (Kosaraju) and subtract from N

#include <bits/stdc++.h>
using namespace std;

void split(string s, string delim, vector<string>& result) {
    auto start = 0U;
    auto end = s.find(delim);
    while (end != string::npos)
    {
        result.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }

    result.push_back(s.substr(start, end));
}

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

int main() {
    int N; cin >> N;
    cin.ignore(1000, '\n');

    unordered_map<string, int> languages;
    int languageCount = 0;

    vector<vector<int>> speaks(3000);
    vector<vector<int>> understands(3000);

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin,line);
        vector<string> tokens;
        split(line, " ", tokens);
        for (int j = 1; j < tokens.size(); ++j) {
            if (languages.find(tokens[j]) == languages.end()) {
                languages[tokens[j]] = languageCount;
                ++languageCount;
            }
        }

        speaks[languages[tokens[1]]].push_back(i);
        for (int j = 1; j < tokens.size(); ++j) {
            understands[languages[tokens[j]]].push_back(i);
        }
    }

    // directed edge: speak -> understand
    vector<vector<int>> adj_list(N);
    for (int i = 0; i < languageCount; ++i) {
        for (int j = 0; j < speaks[i].size(); ++j) {
            for (int k = 0; k < understands[i].size(); ++k) {
                if (speaks[i][j] == understands[i][k]) continue;
                adj_list[speaks[i][j]].push_back(understands[i][k]);
            }
        }
    }

    vector<vector<int>> scc;
    kosaraju(adj_list, scc);

    int max_scc = INT_MIN;
    for (int i = 0; i < scc.size(); ++i) {
        max_scc = max(max_scc, static_cast<int>(scc[i].size()));
    }

    cout << N - max_scc << '\n';
}