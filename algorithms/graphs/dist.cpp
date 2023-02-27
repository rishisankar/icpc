/*
Distances from s to all other nodes in unweighted graph.
Returns -1 for any node not connected to s.
O(n+m)
*/
vi distances(int s, vector<vi>&adj) {
    int n = adj.size();
    vi dist(n, -1);
    vector<bool> visited(n,false);
    dist[s] = 0;
    visited[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int x : adj[t]) {
            if (visited[x]) continue;
            dist[x] = dist[t]+1;
            visited[x] = true;
            q.push(x);
        }
    }
    return dist;
}