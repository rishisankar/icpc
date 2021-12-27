/*
Combinations mod p
(not tested... can test on edu-120 D)

Source: https://www.geeksforgeeks.org/queries-of-ncrp-in-o1-time-complexity/
Precomputation: O(N)
Query: O(1)

Precompute: void precompute(N, p);
Query: ll Binomial(ll N, ll R, ll p);
*/
 
// array to store inverse of 1 to N
vector<ll> factorialNumInverse;
 
// array to precompute inverse of 1! to N!
vector<ll> naturalNumInverse;
 
// array to store factorial of first N numbers
vector<ll> fact;

void precompute(int N, ll p) {
  naturalNumInverse.resize(N+1);
  factorialNumInverse.resize(N+1);
  fact.resize(N+1);
  InverseofNumber(p);
  InverseofFactorial(p);
  factorial(p);
}
 
// Function to precompute inverse of numbers
void InverseofNumber(ll p) {
  int N = naturalNumInverse.size();
  naturalNumInverse[0] = naturalNumInverse[1] = 1;
  for (int i = 2; i <= N; i++)
    naturalNumInverse[i] = naturalNumInverse[p % i] * (p - p / i) % p;
}

// Function to precompute inverse of factorials
void InverseofFactorial(ll p) {
  int N = factorialNumInverse.size();
  factorialNumInverse[0] = factorialNumInverse[1] = 1;

  // precompute inverse of natural numbers
  for (int i = 2; i <= N; i++)
    factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % p;
}
 
// Function to calculate factorial of 1 to N
void factorial(ll p) {
  fact[0] = 1;

  // precompute factorials
  for (int i = 1; i <= N; i++) {
    fact[i] = (fact[i - 1] * i) % p;
  }
}
 
// Function to return nCr % p in O(1) time
ll Binomial(ll N, ll R, ll p) {
  // n C r = n!*inverse(r!)*inverse((n-r)!)
  ll ans = ((fact[N] * factorialNumInverse[R]) % p * factorialNumInverse[N - R]) % p;
  return ans;
}
