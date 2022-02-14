#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld pi= 3.1415926535897932384626;

ld j, p, H, L, v0;
const ld g = 9.81;

ld h(ld l) {
  if (l < 0) return H;
  if (l < L/2) return H*(1-2*(l/L)*(l/L));
  if (l < L) return 2*H*(l/L-1)*(l/L-1);
  return 0;
}

ld flgh(ld l) {
  return -g/2*(l/v0)*(l/v0) + H + p;
}

ld df(ld l) {
  return -g*(l/v0)/v0;
}

ld dh(ld l) {
  if (l < 0) return 0;
  if (l < L/2) return H*(-4*(l/L)/L);
  if (l < L) return 4*H*(l/L-1)/L;
  return 0;
}

// approximation to find max of unimodal function f on some interval
// to switch to min, negate f
// [l,r] = beginning interval
// returns (x, f(x)), where x is the point where f is maximized

// define function f:
ld f(ld x) {
  return -abs(flgh(x) - h(x));
}

pair<ld,ld> ternary_search(ld l, ld r) {
    ld eps = 1e-9;              //set the error limit here
    while (r - l > eps) {
        ld m1 = l + (r - l) / 3;
        ld m2 = r - (r - l) / 3;
        ld f1 = f(m1);      //evaluates the function at m1
        ld f2 = f(m2);      //evaluates the function at m2
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return {l,f(l)};                    //return the maximum of f(x) in [l, r]
}


void run() {
  cin >> j >> p >> H >> L;

  v0  = sqrt(2 * g * j );
  // cout << v0 << '\n';

  ld tst = 104.8808848;
  // cout << "hi " << flgh(tst) << " " << h(tst) << "\n"; 

  pair<ld,ld> res = ternary_search(0, L/2);
  // cout << "tern " << res.first << ' ' << res.second << '\n'; 
  pair<ld,ld> res2 = ternary_search(L/2, L);
  // cout << "tern2 " << res.first << ' ' << res.second << '\n'; 
  ld x;
  if (abs(res.second) < 1e-6) {
    x = res.first;
  } else if (abs(res2.second) < 1e-6) {
    x = res2.first;
  } else {
    x = sqrt((-p-H)*2/(-g))*v0;
  }

  // cout << x << '\n';

  ld lh = (H+p+j) - flgh(x);
  ld ls = sqrt(2*g*lh );
  // cout << ls << '\n';

  ld hvx = 1;
  ld hvy = dh(x);
  ld fvx = 1;
  ld fvy = df(x);
  ld dt = hvx*fvx + hvy*fvy;
  ld ang = acos(dt / sqrt(fvx*fvx+fvy*fvy) / sqrt(hvx*hvx+hvy*hvy));
  cout << x << ' ' << ls << ' ' << (ang*180/pi) << '\n';


  

}

int main() {
      cout.setf(ios::fixed);
    cout.precision(15);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    run();
  }

}