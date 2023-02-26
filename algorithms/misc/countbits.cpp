ll countBits(ll i) {
    ll count = 0;
    while (i != 0) {
        count += (i & 1);
        i >>= 1;
    }
    return count;
}

string toBinary(ll n) {
    string r;
    while (n!=0) {
        r = (n%2==0 ? "0" : "1") + r;
        n/=2;
    }
    return r;
}
