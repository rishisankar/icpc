#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

bool works(ull n, ull x, ull ct) {
  if (ct == 0) return true;
  if (n%x != 0) {
    return false;
  }
  return works(n/x,x, ct-1);
}

int main() {
ull n; cin >> n;
for (ull i = 100000; i>= 1; --i) {
    if (works(n,i,9)) {
      cout << i << '\n';
      exit(0);
    }
}
}