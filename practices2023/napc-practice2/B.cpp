#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
#define rep(i,a,b) for(int i=a; i<(b) ; ++i)
#define trav(a,x) for(auto &a:x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
  int n; cin >> n;
  Tree<pii> t;
  unordered_set<int> numsEx;
  rep(i,0,n) {
    int x; cin >> x;
    t.insert({x,i});
    numsEx.insert(x);
  }
  for (int i : numsEx) t.insert({i,n});
  int q; cin >> q;
  rep(Q,0,q) {
    int k, m; cin >> k >> m; --k;
    unordered_set<int> nums; 
    rep(i,0,m) {
      int x; cin >> x; 
      if (!numsEx.count(x)) continue;
      nums.insert(x);
    }
    int lo = k, hi = n-1, bst=  lo-1;
    while (lo <= hi) {
      int mid= (lo+hi)/2;
      int ct =0 ;
      for (int num : nums) {
        pii k1 = {num,k}, k2 = {num,mid};
        int o1 = t.order_of_key(*(t.lower_bound(k1)));
        int o2 = t.order_of_key(*(t.upper_bound(k2)));
        ct += (o2-o1);
      }

      if (ct == mid - k +1) {
        bst = mid; lo = mid+1;
      } else hi = mid-1;
    }

    cout << (bst-k+1) << '\n';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}