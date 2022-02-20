#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  string s;
  while (getline(cin, s)) {
    ll sm = 0;
    stringstream ss;
    ss << s;
    ll x;
    while (ss >> x) {
      sm += x;
    }
    cout << (sm/2) << '\n';
  }
}