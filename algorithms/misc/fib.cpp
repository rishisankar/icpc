// based on https://levelup.gitconnected.com/how-to-calculate-the-fibonacci-sequence-in-logarithmic-time-abde842f5a39

pair<ll,ll> fibHelp(ll n);

ll fib(ll N) {
    if (N == 0) return 0;
    pair<ll,ll> sol = fibHelp(N);
    return sol.S;
}

pair<ll,ll> fibHelp(ll n) {
    if (n == 1) {
        return {0,1};
    }
    ll m = n/2;
    
    pair<ll,ll> temp = fibHelp(m);
    
    ll fPrev = temp.F;
    ll fCur = temp.S;
    
    ll prev = (fPrev * fPrev) + (fCur * fCur);
    ll cur = fCur * (2 * fPrev + fCur);
    ll next = prev + cur;
    
    if(n % 2 == 0) { 
        return {prev, cur};
    }
    else {
        return {cur, next};
    }
}
