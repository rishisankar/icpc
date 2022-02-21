#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll val(char c) {
  if (c >= '0' && c <= '9') return (c - '0');
  if (c >= 'A' && c <= 'F') return (c - 'A') + 10;
  return (c - 'a')+10;
}

void test(string& s, int i) {
  if (i == 0) return;
  if (s[i-1] != '0') return;
  string x = "";
  for (int j = i+1; j < s.size(); ++j) {
    if ((s[j] >= '0' && s[j] <= '9') || (s[j] >= 'A' && s[j] <= 'F') || (s[j] >= 'a' && s[j] <= 'f')) {
      x += s[j];
    } else {
      if (x == "") return;
      break;
    }
  }
  ll res = 0;
  ll sc = 1;
  for (int j = x.size()-1; j >= 0; --j) {
    res += val(x[j])*sc;
    sc*=16;
  }
  cout << '0' << s[i] << x << ' ' << res << '\n';
}

void parse(string s) {
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'x' || s[i] == 'X') {
      test(s,i);
    }
  }
}

int main() {
  string line;
  while (getline(cin, line)) {
    parse(line);
  }
}