#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

void run() {
  int n; cin >> n;
  vector<pair<ld, int>> v;
  for (int i = 0; i < n; ++i) {
    ld a,b,c; cin >> a >> b >> c;
    ld x = b/2/a;
    ld y = -a*x*x + b*x + c;
    v.push_back({y,i});
  }
  sort(v.begin(), v.end());

  cout << (v[v.size()-1].second + 1) << '\n';
}


int main() {
  int tests;
  cin >> tests;
  for (int te = 0; te < tests; ++te) {
    run();
  }
}