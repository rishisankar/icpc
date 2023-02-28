/*
Find max subarray sum of length a<=L<=b
Assumes 0<=a<=b<=n , runs in O(n)
*/
ll maxSubarraySumInRange(VLL& v, int a, int b) {
    int n = v.size();
    assert(0<=a && a<=b && b<=n);
    if (b == 0) return 0;
    VLL pf(n); pf[0]=v[0];
    for (ll i = 1; i < n; ++i) pf[i]=pf[i-1]+v[i];
    deque<int> d;
    // initial population of deque
    rep(j,0,b-1) {
        while (!d.empty() && pf[d.back()]<=pf[j]) d.pop_back();
        d.push_back(j);
    }
    ll ans = LLONG_MIN;
    if (a == 0) {
        ans = 0;
        a = 1;
    }
    // consider subarrays starting at i (of length at most b)
    rep(i,0,n-a+1) {
        // last index j must be in [a+i-1,b+i-1] , choose such j w max pf[j]
        while (!d.empty() && d.front()<a+i-1) d.pop_front();
        // b+i-1 now in range ==> add to deq; remove anything smaller
        if (b+i-1 < n) {
            while (!d.empty() && pf[d.back()]<=pf[b+i-1]) d.pop_back();
            d.push_back(b+i-1);
        }
        ans = max(ans, pf[d.front()]-(i==0?0:pf[i-1]));
    }
    return ans;
}
