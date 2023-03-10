/*
Compute diameter of tree by calling dfs on a root node
(Returns # nodes in longest path, if you want # edges, subtract 1)
get<1>(dfs(r)) = diameter, get<3>/get<4> are the end nodes for the diameter.
Time: O(n)
Tested on cses/trees/tree_diameter
*/

typedef tuple<int,int,int,int,int> TD;

// returns {longest path touching i, longest diam found, root of longest path touching i, r1 of diam, r2 of diam}
TD dfs(int i, int p, VVI& adj) {
    int bestDiam = 1, bestR1 = i, bestR2 = i;
    priority_queue<pii,vector<pii>,greater<pii>> nums; // store top two longest paths
    for (int j : adj[i]) if (j!=p) {
        TD soln = dfs(j,i,adj);
        if (get<1>(soln) > bestDiam) {
            bestDiam = get<1>(soln);
            bestR1 = get<3>(soln);
            bestR2 = get<4>(soln);
        }
        if (get<0>(soln) + 1 > bestDiam) {
            bestDiam = get<0>(soln) + 1;
            bestR1 = get<2>(soln);
            bestR2 = i;
        }
        pii res = {get<0>(soln), get<2>(soln)};
        if (nums.size()==2 && res.F > nums.top().F) nums.pop();
        if (nums.size()<2) nums.push(res);
    }
    if (nums.size() == 2) {
        pii p1 = nums.top(); nums.pop();
        pii p2 = nums.top();
        int newDiam = p1.F + p2.F + 1;
        if (newDiam > bestDiam) {
            bestDiam = newDiam, bestR1 = p1.S, bestR2 = p2.S;
        }
    }
    if (nums.empty()) return {1,1,i,i,i};
    else return {1+nums.top().F, bestDiam, nums.top().S, bestR1, bestR2};
}