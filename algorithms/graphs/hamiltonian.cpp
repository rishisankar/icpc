/*
Computes hamiltonian path and cycle (undirected, unweighted graph)
- For a given mask, fix start S as the rightmost 1 bit set; find hamiltonian path/cycle using all set bits
- cyc[mask]: stores last node in cycle starting from S (can use path to reconstruct), or -1 if no cycle
- path[mask][end]: stores previous node in hamiltonian path from S to end (-1 if no path, -2 if no prev i.e. S=end)
Time: O(2^N * N^2)

Note: mask uses ints ==> N < 31 (complexity too slow otherwise anyway)
Example: https://codeforces.com/contest/1804/problem/E (tested on this)
*/
pair<VVI, VI> hamiltonian(VVI& adj, VVB& adjm) {
    int n = adj.size();
    vector<int> masks;
    rep(i,0,(1<<n)) {
        masks.pb(i);
    }
    sort(all(masks), [&](int a, int b) {
        return __builtin_popcount(a) < __builtin_popcount(b);
    });
    VVI path((1<<n), VI(n,-1));
    VI cyc((1<<n), -1);
    for (int mask : masks) {
        if (mask == 0) continue;
        int s = -1; // can change if need to fix root
        rep(i,0,n) {
            if ((mask >> i)&1) {
                s = i;
                break;
            }
        }
        int siz = __builtin_popcount(mask);
        if (siz == 1) {
            path[mask][s] = -2;
            continue;
        }
        rep(end,s+1,n) {
            if (((mask >> end)&1) == 0) continue;
            if (siz == 2) path[mask][end] = (adjm[s][end] ? s : -1);
            else {
                for (int a : adj[end]) { // find node to be second last in path
                    if (a == s) continue;
                    if (((mask >> a)&1) && path[(mask ^ (1<<end))][a] != -1) {
                        path[mask][end] = a;
                        break;
                    }
                }
            }
        }
        // siz >= 2 can have cycle, so check:
        rep(end,s+1,n) {
            if (((mask >> end)&1) == 0 || !adjm[s][end]) continue;
            if (path[mask][end] != -1) {
                cyc[mask] = end;
                break;
            }
        }
    }
    return {path, cyc};
}

/*
Recover a hamiltonian path from precomputed path array (given mask, end node)
Assumes path[mask][end] != -1
To recover a cycle: recoverPath(path, mask, cyc[mask]); (then append start if you want)
*/
VI recoverPath(VVI& path, int mask, int E) {
    VI res;
    res.pb(E);
    int cur = path[mask][E];
    mask ^= (1<<E);
    while (cur != -2) {
        res.pb(cur);
        cur = path[mask][cur];
        mask ^= (1 << res.back()); // update mask to remove cur
    }
    reverse(all(res)); // optional
    return res;
}
