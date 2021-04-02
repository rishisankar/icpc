// Returns largest power of p that divides n! 
ll largestPower(ll n, ll p) { 
    ll x = 0;
    while (n) { 
        n /= p;
        x += n;
    }
    return x;
}
