#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  unordered_map<string, int> attrmap;
  int n; ll k;
  cin >> n >> k;
  vector<ll> init(n);
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    ll c; cin >> c;
    init[i] = c;
    attrmap[s] = i;
  }
  int l; cin >> l;
  vector<vector<ll>> costs(n);
  for (int i = 0; i < l; ++i) {
    string s; cin >> s;
    int at = attrmap[s];
    ll c; cin >> c;
    costs[at].push_back(c);
  }

  ll score = 0;

  vector<bool> exc(n, false);
  vector<int> amt(n, 0);
  priority_queue<pair<ll, pair<int,bool>>> pq;
  // 1: finish each event
  ll req = 0;
  for (int i = 0; i < n; ++i) {
    if (costs[i].size() == 0) {
      continue;
    }
    ll mx = *max_element(costs[i].begin(), costs[i].end());
    if (mx > init[i]) {
      req += (mx - init[i]);
    } else if (init[i] > mx) {
      exc[i] = true;
    }
    if (req > k) {
      cout << "0\n";
      return 0;
    }
    init[i] = max(mx, init[i]);

    // cerr << i << ' ' << init[i] << ' ' << costs[i][0] << '\n';
    for (int j = 0; j < costs[i].size(); ++j) {
      if (costs[i][j] < init[i]) {
        score += init[i];
      } else {
        amt[i]++;
      }
    }

    ll wgt = costs[i].size();
    if (!exc[i]) {
      wgt += amt[i] * mx;
      pq.push({wgt, {i, false}});
    } else {
      pq.push({wgt, {i, true}});
    }
  }
  k -= req;

  // cerr << score << ' ' << k << '\n';

  // 2: fill remainder
  while (k != 0) {
    pair<ll, pair<int,bool>> elt = pq.top();
    ll cst = elt.first;
    int attr = elt.second.first;
    bool b = elt.second.second;
    if (b) {
      // cant do better -- end w this
      score += k * cst;
      k = 0;
    } else {
      score += cst;
      k--;
      pq.pop();
      init[attr]++;
      pq.push({costs[attr].size(), {attr, true}});
    }
  }
  cout << score << '\n';
}