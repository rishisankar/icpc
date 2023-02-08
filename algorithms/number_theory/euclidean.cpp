// O(log(min(a,b))), can use __gcd instead
ll gcd(ll a, ll b) {
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 

// note that lcm(i, j) = ij / gcd(i,j)
ll lcm(ll a, ll b) {
  return a*b/gcd(a,b);
}

// return gcd(a,b) and solve for integer x,y: ax+by=gcd(a,b)
// linear diophantine equations ax+by=c have a solution iff c divides gcd(a,b)
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


VVI matmul(VVI& v1, VVI& v2, ll mod) {
  VVI res(90, VI(90, 0));
  for (int i = 0; i < 90; ++i) {
    for (int j = 0; j < 90; ++j) {
      for (int k = 0; k < 90; ++k) {
        res[i][j] += v1[i][k]*v2[k][j];
        res[i][j] %= mod;
      }
    }
  }
  return res;
}

VVI matmodpow(VVI base, int exp, ll mod) {
  VVI result(90,VI(90,0));
  for(int i=0; i<90;++i)result[i][i]=1;
  while (exp > 0) {
    if (exp & 1) result = matmul(result,base,mod);
    base = matmul(base, base,mod);
    exp >>= 1;
  }
  return result;
}