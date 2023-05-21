#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <(b); i++)
#define trav(a,x) for(auto& a:x)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os <<'(' <<p.F << ", " << p.S << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
  os << '{';
  string sep;
  for(const auto &x: v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

ll INF=1e15;


void dfs(int idx,int n, int excess, int rem,vi &v, set<vi> &new_states, vi &b)
{
  if(idx==n)
  {
    if(rem<=excess)
    {
      vi c=b;
      sort(all(c));
      new_states.insert(c);
    }
    return;
  }
  rep(i,0,min(v[idx]+1,rem+1))
  {
    // dbg(idx,i,rem);
    if(i==0)
    {
      b.pb(v[idx]-i);
      dfs(idx+1,n,excess,rem-i,v,new_states,b);
      b.pop_back();
    }
    else
    {
      int added=0;
      int x=v[idx]-i;
      int y=i;
      if(x!=1) b.pb(x),added++;
      if(y!=1) b.pb(y),added++;
      dfs(idx+1,n,excess,rem-i,v,new_states,b);
      rep(j,0,added) b.pop_back();
    }
  }
}

void solve() {
  int n,m;
  cin>>n>>m;

  vi v(m);
  rep(i,0,m)
  {
    int x;
    cin>>x;
    v[i]=min(x,n-x);
  }

  set<vi> cur_states;
  cur_states.insert(vi(1,n));

  rep(j,0,m)
  {
    set<vi> new_states;
    trav(a,cur_states)
    {
      vi c=a;
      int x=accumulate(all(a),0);
      int excess=n-x;
      vi b;
      dfs(0,sz(a),excess,v[j],c,new_states,b);
    }
    cur_states=new_states;
    // trav(a,cur_states)
    // dbg(j,v[j],a);
  }

  int ans=0;
  trav(a,cur_states)
  {
    int x=accumulate(all(a),0);
    ans=max(ans,n-x);
  }

  cout<<ans<<"\n";
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}