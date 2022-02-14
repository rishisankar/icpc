#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;

const ld pi= 3.1415926535897932384626;
void run () {
  ll r, n; cin >> r >> n;
  vector<pair<ld,ld>> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
  }
  ld cx = 0, cy = 0;
  for (int i = 0; i < n; ++i){
    cx += v[i].first/n;
    cy += v[i].second/n;
  }
  ld md = 2* r * pi;
  ld pem = 0;
  for (int i = 0; i < n; ++i) {
    int j = (i+1)%n;
    ld xx = v[j].first - v[i].first;
    ld yy = v[j].second - v[i].second;
    pem += sqrt(xx*xx+yy*yy);
  }

  // vector<pair<ld,ld>> vecs(n);
  // for (int i = 0; i < n; ++i) {
  //   int j = (i+1)%n;
  //   ld xx = v[j].first - v[i].first;
  //   ld yy = v[j].second - v[i].second;
  //   vecs[i] = {yy,-xx};
  // }
  // for (int i = 0; i < n; ++i) {
  //   ld dt = vecs[i].first * vecs[(i+1)%n].first + vecs[i].second * vecs[(i+1)%n].second;
  //   dt /= sqrt(vecs[i].first*vecs[i].first + vecs[i].second *vecs[i].second);
  //   dt /= sqrt(vecs[(i+1)%n].first * vecs[(i+1)%n].first + vecs[(i+1)%n].second * vecs[(i+1)%n].second);
  //   ld ang = acos(dt);
  //   md += r * r * pi;
  // }
  // cout << md << ' ' << pem << '\n';
  if (md > pem) {
    cout << "Not possible\n";
    return;
  }
  ld rest = pem - md;
  ld scale = rest / pem;
  cout << scale << '\n';
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(15);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    run();
  }
}