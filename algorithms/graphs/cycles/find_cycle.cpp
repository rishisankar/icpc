/*
Find cycle in an undirected graph in O(n+m)
Finds arbitrary cycle (start node, size not guaranteed)
Usage: VI ans = find_cycle(adj)
  ans will return the vertices of the cycle, ie 0 2 5 3 0
  (note first vertex = last vertex)

Example: cses/graphs/round_trip
*/

void dfs_cyc(int t, VVI& adj, VI& colors, VI& par, VI& cyc) {
    if (cyc.size()>0)return;// once cycle found, done
    colors[t] = 1;
    for (int x : adj[t]) {
        if (colors[x] == 2) continue;
        if (colors[x] == 1 && par[t] != x) {
            // cycle found
            int cur = t;
            while (cur != x) {
                cyc.pb(cur);
                cur=par[cur];
            }
            cyc.pb(x);
            cyc.pb(t);
            return;
        } else if (colors[x] == 0) {
            par[x] = t;
            dfs_cyc(x,adj,colors,par,cyc);
            if (cyc.size()>0)return; //if cycle found, done
        }
    }
    colors[t] = 2;
}

VI find_cycle(VVI& adj) {
    int n = adj.size();
    VI colors(n,0); // 0 = white, 1 = gray, 2 = black
    VI par(n,-1);
    VI cyc;
    rep(i,0,n) {
        if (colors[i] == 0) {
            dfs_cyc(i,adj,colors,par,cyc);
        }
    }
    return cyc;
}
