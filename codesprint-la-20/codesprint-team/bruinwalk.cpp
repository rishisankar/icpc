#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> adj[1001];

int bfs(int start, int finish) {
    queue<int> q;
    bool visited[1001] = {false};
    int dist[1001];
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        for (int i = 0; i < adj[f].size(); ++i) {
            int pt = adj[f][i];
            if (!visited[pt]) {
                visited[pt] = true;
                dist[pt] = dist[f] + 1;
                q.push(pt);
            }
            if (pt == finish) {
                return dist[pt];
            }
        }
    }
    return -1;

}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v1,v2;
        cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }





    int s, t, k;
    cin >> s >> t >> k;
    int min = bfs(s, t);
    for (int i = 0; i < k; ++i) {
        int v;
        cin >> v;
        if (bfs(v,t) <= min) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;


}