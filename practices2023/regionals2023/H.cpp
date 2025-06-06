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

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os<< '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream & operator<<(ostream &os, const vector<T> &v) {
  os << '{';
  string sep;
  for(const auto &x: v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
  cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;

void solve() {
  int a,b,c,d;
  cin>>a>>b>>c>>d;

  vi s;
  int cur=b-a;
  while(cur<6000)
  {
    s.pb(cur);
    cur+=b;
  }
  vi m;
  cur=d-c;
  while(cur<6000)
  {
    m.pb(cur);
    cur+=d;
  }

  rep(i,0,6000)
  if(find(all(s),i)!=s.end() && find(all(m),i)!=m.end())
  {
    cout<<i<<"\n";
    return;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}