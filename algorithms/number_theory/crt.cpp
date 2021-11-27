ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

/*

CRT: find x s.t. x = a (mod m) and x = b (mod n)
Return -1 if no solution
Time: log(max(m,n))
Source: kactl
Example: numbertheory/generalchineseremainder
Note: not necessarily the smallest nonnegative soln. crt(...) % lcm(m,n) is the smallest.
*/
ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if ((a - b) % g == 0) {
	    x = (b - a) % n * x % n / g * m + a;
	    return x < 0 ? x + m*n/g : x;
    } else {
        return -1;
    }
}
