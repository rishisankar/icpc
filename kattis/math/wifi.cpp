#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;

int n,m;

bool test(ld dist, vector<int>& v) {
  int ct = 1, i = 1;
  ld fst = v[0] + dist;
  while (i < v.size()) {
    ld eps = 1e-6;
    if (abs(v[i] - fst) <= dist + eps) {
      ++i;
    } else {
      fst = v[i] + dist;
      ++i; ++ct;
      if (ct > n) return false;
    }
  }
  return (ct <= n);
}

void run() {

  cin >> n >> m;
  vector<int> v(m);
  for (int i = 0; i < m; ++i) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());

  if (n >= m) {
    cout << "0.0\n";
    return;
  }

  ld lo = 0, hi = 1000001;
  ld eps = 1e-8;
  while (abs(hi-lo) > eps) {
    ld mid = (lo + hi) / 2;
    if (test(mid,v)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }

  ll vv = round(lo*10);
  cout << vv/10 << '.' << vv%10 << '\n';

}


int main() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    run();
  }
}