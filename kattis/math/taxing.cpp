#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;

int b, f;
ld p;
vector<pair<ld,ld>> v;
vector<pair<ld,ld>> v2;

ld eps = 1e-11;

ld compute(ld bal, ld amt) {
  int bd = 0;
  ld gain = 0;
  while (bd < b && bal > v[bd].first) ++bd;
  while (amt > eps && bd < b) {
    ld cost = min(v[bd].first - bal, amt);
    amt -= cost;
    bal += cost;
    ld r = (100-v[bd].second);
    r/=100;
    gain += cost * r;
    ++bd;
  }
  if (amt > eps) {
    ld r = (100-p);r/=100;
    gain += r * amt;
  }
  return gain;
}

int main() {
  cout.setf(ios::fixed);
  cout.precision(15);
  cin >> b;
  v.resize(b);
  for (int i = 0; i < b; ++i) {
    cin >> v[i].first >> v[i].second;
    if (i != 0)v[i].first = v[i].first + v[i-1].first;
  }
  cin >> p;
  cin >> f;
  v2.resize(f);
  for (int i = 0; i < f; ++i) {
    cin >> v2[i].first >> v2[i].second;
  }

  for (int i = 0; i < f; ++i) {
    ld lo = 0, hi = 100000000000000000000000000000.;
    while (abs(hi-lo) > eps && abs((hi-lo)/lo) > eps) {
      ld mid = (hi+lo)/2;
      ld res = compute(v2[i].first, mid);
      if (res > v2[i].second) {
        hi = mid;
      } else {
        lo = mid;
      }
    }
    cout << lo << '\n';
  }

}