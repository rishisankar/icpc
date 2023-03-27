/*
Shortest cycle in an unweighted, undirected graph
Returns -1 if no cycle, else returns length

Works by trying each node as the start, then doing 
bfs to find the first node with two paths to it

Can probably recover cycle by using parent array (idk)

O(n*(n+m)) to do n bfs

Tested on cses/additional/graph_girth
*/

int shortest_cycle(int n, vector<vector<int>>& adj) {
    int res = INT_MAX;

    for (int i = 0; i < n; ++i) {
        vector<int> dist(n, INT_MAX);
        vector<int> parent(n);
        queue<int> q;
        dist[i] = 0;
        parent[i] = i;
        q.push(i);
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            for (int a : adj[t]) {
                if (dist[a] == INT_MAX) {
                    dist[a] = dist[t] + 1;
                    parent[a] = t;
                    q.push(a);
                } else {
                    if (parent[t] != a && parent[a] != t) {
                        res = min(res, dist[t] + dist[a] + 1);
                    }
                }
            }
        }
    }
    
    return (res == INT_MAX) ? -1 : res;
}