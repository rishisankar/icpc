#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int) (x).size()
#define rep(i,a,b) for(int i = a; i < (b); ++i)

typedef long long ll;

int main() {

  string s1 = "qwertyuiop";
  string s2 = "asdfghjkl";
  string s3 = "zxcvbnm";

  unordered_map<char, int> hz, vz;
  for (int i = 0; i < s1.size(); ++i) {
    hz[s1[i]] = i;
    vz[s1[i]] = 0;
  }
  for (int i = 0; i < s2.size(); ++i) {
    hz[s2[i]] = i;
    vz[s2[i]] = 1;
  }
  for (int i = 0; i < s3.size(); ++i) {
    hz[s3[i]] = i;
    vz[s3[i]] = 2;
  }


  vector<vector<ll>> adj(26, vector<ll>(26));

  for (int i = 0; i < 26; ++i) {
    for (int j = 0; j < 26; ++j) {
      char c1 = i + 'a';
      char c2 = j + 'a';
      adj[i][j] = adj[j][i] = abs(hz[c1] - hz[c2]) + abs(vz[c1] - vz[c2]);
    }
  }

  int t; cin >> t;

  for (int tests = 0; tests < t; ++tests) {
    string s; cin >> s;
    int l; cin >> l;
    vector<pair<int, string>> ans;
    for (int ent = 0; ent < l; ++ent) {
      string x; cin >> x;
      int ct = 0;
      for (int i = 0; i < x.size(); ++i) {
        ct += adj[(x[i]-'a')][(s[i]-'a')];
      }
      ans.push_back({ct, x});
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
      cout << ans[i].second << ' ' << ans[i].first << '\n';
    }

  }

}