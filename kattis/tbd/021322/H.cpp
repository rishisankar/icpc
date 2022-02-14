#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// return gcd(a,b) and solve for integer x,y: ax+by=gcd(a,b)
// linear diophantine equations ax+by=c have a solution iff c divides gcd(a,b)
ll euclidean(ll a, ll b, ll &x, ll &y)
{

  if (a == 0)
  {
    x = 0;
    y = 1;
    return b;
  }

  ll x1, y1;
  ll gcd_ = euclidean(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd_;
}

// only exists if gcd(a,m) = 1 !! otherwise return -1
ll modularInverse(ll a, ll m)
{
  ll x, y;
  ll g = euclidean(a, m, x, y);
  if (g != 1)
    return -1;
  return (x % m + m) % m; // shift x to positive in case it is negative
}
int main()
{
  int t;
  cin >> t;
  while (t-- > 0)
  {
    ll k, c;
    cin >> k >> c;
    if (k==1&&c!=1) {
      cout << "1\n";
      continue;
    }
    // ll x,y;
    if(k==1000000000 && c ==1){
      cout<<"IMPOSSIBLE"<<"\n";
      continue;
    }
    if ( c == 1){
      cout << k+1 << "\n";
      continue;
    }
    ll save = modularInverse(c, k);
    if (save != -1 && save <= 1000000000)
    {
      cout << save << "\n";
    }
    else
    {
      cout << "IMPOSSIBLE"
           << "\n";
    }
  }
}