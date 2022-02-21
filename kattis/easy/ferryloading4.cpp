#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void run() {
  ll l,m; cin >> l >> m;l*=100;
  ll lc = 0, rc = 0;
  ll lv = 0, rv = 0;
  for (int i = 0; i < m; ++i) {
    ll x; cin >> x;
    string s; cin >> s;
    if (s == "left") {
      lv += x;
      if (lv > l) {
        lv = x;
        lc++;
      }
    } else {
      rv += x;
      if (rv > l) {
        rv = x;
        rc++;
      }
    }
  }
  if (lv>0)++lc;
  if (rv>0) ++rc;
  // cerr << lc << ' ' << rc << "\n";
  if (rc>=lc) {
    cout << rc*2 << '\n';
  } else {
    cout << 2*lc-1 << '\n';
  }

}

int main() {
  int c; cin >> c;
  for (int i = 0; i < c; ++i) {
    run();
  }
}