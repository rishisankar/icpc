#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int main() {

  ld r, s;
  while (cin >> r) {
  cin >> s;
  ld v = sqrt(r*(s+.16) / .067);
  cout << (ll)round(v) << '\n';}
}