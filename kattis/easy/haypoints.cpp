#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
int m; cin >>m;
int n; cin >> n;
  unordered_map<string, ll> pm;
  for (int i = 0; i < m; ++i ){
    string s; cin >> s;
    ll x; cin >> x;
    pm[s] = x;
  }

  string ln;
  for (int i = 0; i < n; ++i) {
    ll ct = 0;
    while (true) {
      cin >> ln;
      if (ln == ".") break;
      if (pm.count(ln))ct += pm[ln];
    }
    cout << ct << '\n';
  }

}