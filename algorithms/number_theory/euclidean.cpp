// example: math/fiat.cpp (modular inverse for catalan numbers)

typedef long long ll; // shouldn't be unsigned bc modular inverse returns -1!

// O(log(min(a,b)))
ll gcd(ll a, ll b) {
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 

// note that lcm(i, j) = ij / gcd(i,j)
ll lcm(ll a, ll b) {
  return a*b/gcd(a,b);
}


// return gcd(a,b) and solve for integer x,y: ax+by=gcd(a,b)
ll euclidean(ll a, ll b, ll &x, ll &y) {

    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    ll x1,y1;
    ll gcd_ = euclidean(b%a, a, x1, y1);

    x = y1 - (b/a) * x1;
    y = x1;

    return gcd_;

}

// only exists if gcd(a,m) = 1 !! otherwise return -1
ll modularInverse(ll a, ll m) {
    ll x,y;
    ll g = euclidean(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m; // shift x to positive in case it is negative
}

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}
