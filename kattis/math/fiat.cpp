#include <bits/stdc++.h>
using namespace std;

typedef long long ll; // shouldn't be unsigned bc modular inverse returns -1!

// O(log(min(a,b)))
ll gcd(ll a, ll b) 
{ 
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 


// return gcd(a,b) and solve for integer x,y: ax+by=gcd(a,b)
ll euclidean(ll a, ll b, ll &x, ll &y) {\

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

int main() {

    int N; cin >> N;

    // catalan #s

    const ll MOD = 1000000007;

    ll res = 1;
    for (int i = N+1; i <= 2*N; ++i) {
        res *= i;
        res %= MOD;
    }

    // multiply by modular inverse instead of dividing by divisor

    ll divisor = 1;
    for (int i = 2; i <= N+1; ++i) {
        divisor *= i;
        divisor %= MOD;
    }

    ll inv = modularInverse(divisor, MOD);

    res *= inv;
    res %= MOD;

    cout << res << '\n';

}