// Compute diameter of rooted tree by calling dfs on root node.
// get<1>(dfs(r)) = diameter, get<3>/get<4> are the end nodes for the diameter.
// Time: O(n)

typedef tuple<int,int,int,int,int> TD;

// returns {longest path touching i, longest diam found, root of longest path, r1 of diam, r2 of diam}
TD dfs(int i) {
    if (!adj.count(i)) {
        // dbg(i,1,1,i,i,i);
        return {1,1,i,i,i};
    }
    int bestDiam = 1;
    int bestR1 = i;
    int bestR2 = i;
    VPII nums;
    for (int j : adj[i]) {
        TD soln = dfs(j);
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
        nums.PB({get<0>(soln), get<2>(soln)});
    }
    sort(all(nums));
    if (nums.size() >= 2) {
        int newDiam = nums[nums.size()-1].first + nums[nums.size()-2].first + 1;
        if (newDiam > bestDiam) {
            bestDiam = newDiam;
            bestR1 = nums[nums.size()-1].second;
            bestR2 = nums[nums.size()-2].second;
        }
    }
    // dbg(i,1 + nums[nums.size()-1].first , bestDiam, nums[nums.size()-1].second, bestR1, bestR2 );
    return {1 + nums[nums.size()-1].first , bestDiam, nums[nums.size()-1].second, bestR1, bestR2};
}