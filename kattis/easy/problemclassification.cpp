#include <bits/stdc++.h>
using namespace std;
int main() {

  int n; cin >> n;
  vector<string> cats(n);
  unordered_map<string,int> cm;
  unordered_map<string,vector<int>> qz;
  vector<int> cts(n,0);
  for (int i = 0; i < n; ++i) {
    string cat; cin >> cat;
    cats[i] = cat;
    cm[cat] = i;
    int w; cin >> w;
    for (int j = 0; j < w; ++j) {
      string s; cin >> s;
      qz[s].push_back(i);
    }
  }
  string s;
  while (cin >> s) {
    if (qz.count(s)) {
      for (int x : qz[s]) {
        ++cts[x];
      }
    }
  }

  vector<string> best;
  int mxc = -1;
  for (int x : cts) {
    mxc = max(mxc, x);
  }
  for (int i = 0 ;i <cts.size(); ++i) {
    if (cts[i] == mxc) {
      best.push_back(cats[i]);
    }
  }
  sort(best.begin(), best.end());
  for (string st : best) {
    cout << st << '\n';
  }


}