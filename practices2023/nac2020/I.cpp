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

int TOT;

map<vi,int> st;
unordered_map<int,vi> rst;


void dfs(int idx,int n, int &excess, int future, int rem,int &v, set<int> &new_states, vi &b)
{
  if(idx==n)
  {
    if(rem<=excess)
    {
      vi c=b;
      sort(all(c));
      reverse(all(c));
      if(st.find(c)==st.end())
      {
        int z=sz(st);
        st[c]=z;
        rst[z]=c;
        new_states.insert(z);
      }
      
      if(sz(c)==0) // you are done, so exit
      {
        cout<<TOT<<"\n";
        exit(0);
      }
    }
    return;
  }
  rep(i,max(0,rem-excess-future+rst[v][idx]),min(rst[v][idx]+1,rem+1))
  {
    // dbg(idx,i,rem);
    if(i==0)
    {
      b.pb(rst[v][idx]-i);
      dfs(idx+1,n,excess,future-rst[v][idx],rem-i,v,new_states,b);
      b.pop_back();
    }
    else
    {
      int added=0;
      int x=rst[v][idx]-i;
      int y=i;
      if(x!=1) b.pb(x),added++;
      if(y!=1) b.pb(y),added++;
      dfs(idx+1,n,excess,future-rst[v][idx],rem-i,v,new_states,b);
      rep(j,0,added) b.pop_back();
    }
  }
}

void solve() {
  int n,m;
  cin>>n>>m;
  TOT=n;

  vi v(m);
  rep(i,0,m)
  {
    int x;
    cin>>x;
    v[i]=min(x,n-x);
  }

  set<int> cur_states;
  set<int> seen;
  int z=sz(st);
  st[vi(1,n)]=z;
  rst[z]=vi(1,n);
  cur_states.insert(z);
  seen.insert(z);

  rep(j,0,m)
  {
    set<int> new_states;
    trav(a,cur_states)
    {
      int x=accumulate(all(rst[a]),0);
      int excess=n-x;
      vi b;
      int aa=a;
      dfs(0,sz(rst[a]),excess,x,v[j],aa,new_states,b);
    }
    cur_states=new_states;
    dbg(sz(st),j);
    // trav(a,cur_states)
    // dbg(j,v[j],a);
  }

  int ans=0;
  trav(a,cur_states)
  {
    int x=accumulate(all(rst[a]),0);
    ans=max(ans,n-x);
  }

  cout<<ans<<"\n";
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}