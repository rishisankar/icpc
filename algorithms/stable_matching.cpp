//kattis:jealousyoungsters (stable matching of n children to toys)
bool toyprefers(int c1, int c2, int ty, vector<vector<int>>& tp) {
  for (int i : tp[ty]) {
    if (i == c1) return true;
    if (i == c2) return false;
  }
  return false; // never should get here
}

void gale_shapley() {
  // n: children, m: toys
  int n,m; cin >> n >> m; 

  // impossible only if not enough toys
  if (n > m) {
    cout << "impossible\n";
    return;
  }

  // kid/toy preferences (first elt = most preferred)
  // kids ordered 0..n-1, toys ordered 0..m-1
  vector<vector<int>> kp(n);  // kp[i]: toys in preference order
  vector<vector<int>> tp(m);

  // gale-shapley algorithm
  vector<int> kid_matches(n, -1);
  vector<int> toy_matches(m, -1);
  stack<int> unmatched_kids;
  vector<int> kid_prop(n,0); // next toy kid proposes to on proposal list
  rep(i, 0, n) {
    unmatched_kids.push(i);
  }
  while (!unmatched_kids.empty()) {
    int chl = unmatched_kids.top();
    unmatched_kids.pop();
    while (kid_prop[chl] < m) {
      // try proposing to toy
      int ty = kp[chl][kid_prop[chl]];
      ++kid_prop[chl];
      if (toy_matches[ty] == -1) {
        // toy not matched --> match to child
        kid_matches[chl] = ty;
        toy_matches[ty] = chl;
        break;
      } else {
        // check if better match (i.e. toy prefers child chl to current match)
        int cur_mch = toy_matches[ty];
        // CAN BE OPTIMIZED: 
        if (toyprefers(chl, cur_mch, ty, tp)) {
          kid_matches[chl] = ty;
          toy_matches[ty] = chl;
          kid_matches[cur_mch] = -1;
          unmatched_kids.push(cur_mch);
          break;
        }
      }
    }
    // should never get here, don't really need this case
    if (kid_prop[chl] == m && kid_matches[chl] == -1) {
      assert(false);
      return;
    }
  }

  rep(i, 0, n) {
    cout << (kid_matches[i]) << ' ';
  }
  cout << '\n';
}
