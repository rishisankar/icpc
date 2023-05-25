#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); ++i)
#define trav(a,x) for(auto& a:x)
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

void solve() {
  int n,q; cin >> n >> q;
  map<string,int> nm;
  rep(i,0,n) {
    string s; cin >> s;
    nm[s] = sz(nm);
  }
  rep(i,0,q) {
    string a,b;cin >> a >> b;
    int x=nm[a], y = nm[b];
    cout << (llabs(x-y)-1) << '\n';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}