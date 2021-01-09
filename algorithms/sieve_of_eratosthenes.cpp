// Sieve of Eratosthenes: compute prime #s from 1 - n
// initialize: is_prime(n+1, true);
// n >= 2
// returns # of primes <= n, and is_prime can be used to check if a number is prime
// source: https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html

// example: math/primesieve

int sieve(int n, vector<bool>& is_prime) {
    int count = n-1;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                if (is_prime[j]) {
                    is_prime[j] = false;
                    --count;
                }
            }
        }
    }
    return count;
}