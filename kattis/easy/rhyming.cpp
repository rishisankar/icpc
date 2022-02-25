#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool endsWith(string s, string x) {
  if (s.size() < x.size()) {
    return false;
  }
  for (int i = 0; i < x.size(); ++i) {
    if (s[s.size()-1-i] != x[x.size()-1-i]) return false;
  }
  return true;
}
int main() {
  string s; cin >> s;
  int e; cin >> e;
  cin.ignore(10000,'\n');
  vector<string> endings;
  for (int i = 0; i < e; ++i) {
    string ln;
    getline(cin, ln);
    stringstream ss;
    ss << ln;
    string x;
    vector<string> vx;
    bool valid = false;
    while (ss >> x) {
      vx.push_back(x);
      if (endsWith(s, x)) valid = true;
    }
    if (valid) {
      for (string xx : vx) {
        endings.push_back(xx);
      }
    }
  }
  // for (string xxx : endings) {
  //   cout << xxx << '\n';
  // }
  int p; cin >> p;
  cin.ignore(10000,'\n');

  for (int i = 0; i < p ; ++i) {

    string ln;
    getline(cin , ln);
    string x;
    stringstream ss; ss << ln;
    while (ss >> x) {}
    bool done = false;
    for (string endd : endings) {
      if (endsWith(x, endd)) {
        cout << "YES\n";
        done = true;
        break;
      }
    }
    if (!done) cout <<"NO\n";
  }
}