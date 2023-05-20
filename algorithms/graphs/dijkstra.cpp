// O( (m+n) log n )
// define VLL d, VI p; (don't size)
// d gives distances to each point, p gives parent in path
// from cp-algorithms.com

const ll INF = 10000000000000000LL;
void dijkstra(int s, vector<ll>& d, vector<int>& p, vector<vector<pair<int,ll>>>& adj) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    using pii = pair<ll, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        ll d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            ll len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}




/*
Compute number of shortest paths to each node (directed/undirected)
Edge weights must be > 0 (if 0, could be infinite ways...)
Need both adj and reverse adj list (in undirected graph, use adj for both)
Time complexity same as dijsktra O(E log V)

Tested (directed) on cses/additional/visiting_cities
Tested (undirected) on https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/
*/
const ll INF = 10000000000000000LL;
void dijkstra(int s, VLL& d, vector<vector<pair<int,ll>>>& adj) {
    int n = adj.size();
    d.assign(n, INF);
    d[s] = 0;
    using pii = pair<ll, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        ll d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            ll len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}
void numShortestPaths(int s, VLL& paths, vector<vector<pair<int,ll>>>& adj, vector<vector<pair<int,ll>>>& radj, ll mod) {
    int n = adj.size();
    VLL d; dijkstra(s,d,adj);
    paths.assign(n,0);
    paths[s] = 1;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    rep(i,0,n) {
        if (i != s) pq.push({d[i],i});
    }
    while (!pq.empty()) {
        pair<ll,int> p = pq.top(); pq.pop();
        for (auto ed : radj[p.S]) {
            if (d[ed.F] + ed.S == p.F) {
                paths[p.S] += paths[ed.F];
                paths[p.S] %= mod;
            }
        }
    }
}
