/**

The Mobius function is defined as follows:
mu(n) = {
    1 if n=1
    0 if a^2 | n for some a > 1 (so if any prime factor in prime factorization has power > 2)
    (-1)^k if n is the product of k distinct primes
}

Useful for sums of gcd, lcm, and other things
- lcm follows from lcm(i,j) = ij / gcd(i,j)

Properties:
- the sum over all d that divide n of mu(d) = [n=1] (= 1 if n == 1 else 0)
    - this can be used to solve problems that ask you to efficiently sum functions that equal 1 (such as gcd)
- if g(n) = sum over all d that divide n of f(d), then f(n) = sum over all d that divide n of g(d)*mu(n/d)

Application:
- Sum of all coprime integers in range [1,n]:
    = \sum_{d=1}^n ( mu(d) * floor(n/d)^2 )
- 
Sources:
- https://codeforces.com/blog/entry/53925  (theory + examples)
- https://www.geeksforgeeks.org/program-mobius-function/  (code)

*/

// O(sqrt(n)), not tested
ll mobius(ll n) { 
    ll p = 0; 
    
    if (n%2 == 0) {  // Handling 2 separately 
        n = n/2; 
        p++; 
        // If 2^2 also divides N 
        if (n % 2 == 0) 
           return 0; 
    } 
  
    // Check for all other prine factors 
    for (ll i = 3; i <= sqrt(n); i = i+2) {
        // If i divides n 
        if (n%i == 0) { 
            n = n/i; 
            p++; 
            // If i^2 also divides N 
            if (n % i == 0) 
               return 0; 
        } 
    }
    return (p % 2 == 0) ? -1 : 1; 
}


// O(n) - find mobius function value for all from 1-N (example: math/coprimeintegers.cpp)
void least_prime_factor(ll N, vector<ll> &lpf) {  // from sieve of eratosthenes code
    lpf.resize(N+1);
    fill(lpf.begin(), lpf.end(), 0); 
    for (ll i = 2; i <= N; i++) {
        // If it is a prime number 
        if (!lpf[i]) {
            for (ll j = i; j <= N; j += i) {
                // For all multiples which are not 
                // visited yet. 
                if (!lpf[j]) lpf[j] = i; 
            }
        }
    }
}
void mu_1_to_n(ll n, vector<ll> &mu) {
    mu.resize(n+1);
    mu[0] = 1;
    mu[1] = 1;
    vector<ll> lpf;
    least_prime_factor(n, lpf);
    for (ll i = 2; i <= n; ++i) {
        // if number has a squared prime factor
        if (lpf[i / lpf[i]] == lpf[i]) {
            mu[i] = 0LL;
        } else {
            mu[i] = -1LL * mu[i / lpf[i]];
        }
    }
}