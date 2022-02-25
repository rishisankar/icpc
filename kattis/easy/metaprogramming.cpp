#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
  unordered_map<string, ll>  mp;
  string cm;
  while (cin >> cm) {
    if (cm == "define") {
      ll x; cin >> x;
      string vr; cin >> vr;
      mp[vr] = x;
    } else {
      string s1,s2, op;
      cin >> s1 >> op >> s2;
      if ((!mp.count(s1)) || (!mp.count(s2))) {
        cout << "undefined\n";
      } else {
        if (op == "<") {
          cout << ((mp[s1]<mp[s2]) ? "true" : "false") << '\n';
        } else if (op == ">") {
          cout << ((mp[s1]>mp[s2]) ? "true" : "false") << '\n';
        } else {
          cout << ((mp[s1]==mp[s2]) ? "true" : "false") << '\n';
        }
      }
    }
  }
}