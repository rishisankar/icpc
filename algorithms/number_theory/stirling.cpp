/*
Compute all stirling numbers of the first kind: stirling[n][k] = S(n,k)
(# of permutations of n elements with k disjoint cycles)
Note: invalid if k > n
Recurrence relation: S(n+1,k) = n*S(n,k) + (n,k-1)
Time: O(n^2)
Example: cses/additional/functional_graph_distribution
*/
VVLL stirling(int n, int mod) {
    VVLL ans(n+1, VLL(n+1,0));
    ans[0][0] = 1; // all other S(n,0) = 0
    rep(N,1,n+1) {
        rep(K,1,N+1) {
            ans[N][K] = ((N-1)*ans[N-1][K])%mod + ans[N-1][K-1];
            ans[N][K] %= mod;
        }
    }
    return ans;
}
