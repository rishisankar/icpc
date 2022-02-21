#include <bits/stdc++.h>
using namespace std;

const int INF = (int)(1e9) + 5;
const int MAXN = (int)(1e5) + 5;
int mn[4* MAXN];

void pull(int n) {
  mn[n] = min( mn[2*n], mn[2*n+1]);
}
void upd(int i, int val, int n = 1, int tl = 0, int tr = MAXN-1) {
  if (tl == tr) {
    mn[n] = min(mn[n], val);
  }
  else {
    int tm = (tl + tr)/2;
    if (i <= tm) {
      upd(i, val, 2*n, tl, tm);
    }
    else {
      upd(i, val, 2*n+1, tm+1, tr);
    }
    pull(n);
  }
}
int get(int r, int n = 1, int tl = 0, int tr = MAXN-1) {
  if (tr <= r) return mn[n];
  if (tl > r) return INF;

  int tm = (tl + tr)/2;
  return min(get(r, 2*n, tl, tm), get(r, 2*n+1, tm+1, tr));
}
void run() {
  int n; cin >> n;
  vector<pair<int, pair<int, int>>> v;
  for (int i = 0; i < n; ++i) {
    int a,b,c; cin >> a >> b >> c;
    v.push_back({a,{b ,c}});
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < 4*MAXN; i++) mn[i] = INF;
  int cnt = n;
  for (auto[x, temp] : v) {
    auto[y, z] = temp;
    if (get(y) <= z) {
      // cout << x << " " << y << " " << z << " " << get(y) << endl;
      cnt--;
    }
    // cout << "UPD: " << y << " " << z << endl;
    upd(y, z);
  }
  cout << cnt << '\n';



}


int main() {
  int tests;
  cin >> tests;
  for (int te = 0; te < tests; ++te) {
    run();
  }
}