#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef long long ll;

int main() {
  ll au, bu, ar, br;
  cin >> au >> bu >> ar >> br;
  ll res = 0;
  if (br != 0) res += au;
  if (ar != 0) res += bu;
  if (ar == 0 && br == 0) res += min(au,bu);
  res += ar*br;
  cout << res << "\n";
}