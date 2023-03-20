/*

# of trees on n labeled vertices = n^{n-2}
- Equivalently, # of spanning trees of complete graph with labeled vertices
- Implies: labeled rooted forests on n vertices: (n+1)^(n-1)

Let Tn,k be the number of labeled forests on n vertices with k connected components, 
such that vertices 1, 2, ..., k all belong to different connected components. Then:
- Tn,k = kn^{n-k-1}

*/


// to compute T(n,k) for all k for a given n in O(nlogn) - example cses/additional/functional_graph_distribution
VLL cayley(int n) {
    VLL ans(n+1);
    rep(i,0,n+1) {
        ans[i] = i;
        if (n-i-1 > 0) {
            ans[i] *= modpow(n,n-i-1,mod);
        } else if (n-i-1 < 0) {
            ans[i] *= inv(modpow(n,-(n-i-1),mod));
        }
        ans[i] %= mod;
    }
    return ans;
}

// depends on modpow/inv: (note mod should be set too)
typedef ll T;
ll modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}
ll inv(ll x) {
    x%=mod;
    return modpow(x, mod-2, mod);
}