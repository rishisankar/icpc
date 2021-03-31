// Euler's Totient Function
// Euler's Theorem: if gcd(a,n) = 1, then a^{phi(n)} = 1 (mod n)

// Complexity: O(sqrt(n)) - example numbertheory/crackingrsa
// Uses the property that phi(n) = n(1-1/p1)(1-1/p2)...(1-1/pk) if n = p1^a1 ... pk^ak
// factorizes n
ll phi(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// Calculate ETC for 1 to n O(n log log n)
void phi_1_to_n(int n, vector<int> &phi) {
    phi.resize(n+1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i;

    // uses idea similar to sieve of eratosthenes
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {  // basically, if prime
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
