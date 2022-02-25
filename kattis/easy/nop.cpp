#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool isup(char c) {
  return c >= 'A' && c <='Z';
}
int main() {
  string s; cin >> s;
  int ct = 1;
  int res = 0;
  for (int i = 1; i < s.size(); ++i) {
    if (isup(s[i])) {
      ct%=4;
      int z = (4-ct)%4;
      res+=z;
      ct = 1;
    } else {
      ++ct;
    }
  }
  cout << res<<'\n';
}