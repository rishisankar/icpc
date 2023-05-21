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
int TOT;

set<vi> seen;


void dfs(int idx,int n, int excess, int rem,vi &v, set<vi> &new_states, vi &b)
{
  if(idx==n)
  {
    if(rem<=excess)
    {
      vi c=b;
      sort(all(c));
      reverse(all(c));
      // if(c==vi({13,2,2,2,2})) dbg(v);
      // if(c==vi({15,3,3,2,2})) dbg(v);
      // if(c==vi({18,3,3,3})) dbg(v);
      // if(c==vi({21,4,4})) dbg(v);
      // if(c==vi({25,5})) dbg(v);
      if(seen.insert(c).S)
      new_states.insert(c);
      if(sz(c)==0) // you are done, so exit
      {
        cout<<TOT<<"\n";
        exit(0);
      }
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
      if(x>1) b.pb(x),added++;
      if(y>1) b.pb(y),added++;
      dfs(idx+1,n,excess,rem-i,v,new_states,b);
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

  sort(all(v));
  // reverse(all(v));

  set<vi> cur_states;
  cur_states.insert(vi(1,n));
  seen.insert(vi(1,n));

  vector<set<vi>> sols(m+1);
  sols[0]=cur_states;

  rep(j,0,5)
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
    sols[j+1]=cur_states;
    dbg(j+1,sz(seen));
    // trav(a,sols[j+1]) dbg(a);
    // trav(a,cur_states)
    // dbg(j,v[j],a);
  }

  cur_states.clear();
  seen.clear();
  cur_states.insert(vi(1,n));
  seen.insert(vi(1,n));
  rep(j,5,m)
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
    sols[j+1]=cur_states;
    dbg(j,sz(seen));
  }


  if(m<=5)
  {
      int ans=0;
      trav(a,sols[m])
      {
        int x=accumulate(all(a),0);
        ans=max(ans,n-x);
      }

      cout<<ans<<"\n";
  }
  else
  {
    int other=m;
    vector<vi> A,B;
    trav(a,sols[5])
    A.pb(a);
    trav(a,sols[other])
    B.pb(a);

    // sort(all(A),[&](const vi x, const vi y){return sz(x)<sz(y);});
    // sort(all(B),[&](const vi x, const vi y){return sz(x)<sz(y);});
    // reverse(all(B));
    dbg(sz(A),sz(B));
    // vi X=A[0];
    // vi Y=B[0];
    // dbg(X,Y);
    int anss=0;
    trav(x,A) trav(y,B)
    {
      while(accumulate(all(x),0)!=TOT) x.pb(1);
      sort(all(x));
      while(accumulate(all(y),0)!=TOT) y.pb(1);
      sort(all(y));
      reverse(all(y));

      vi X=x,Y=y;
      trav(a,Y)
      {
        int k=0;
        while(k<sz(X)&&a>0)
        {
          if(X[k]>0) X[k]--,a--;
          k++;
        }
      }

      int ansx=accumulate(all(X),0);
      int ansy=accumulate(all(Y),0);
      assert(ansx==ansy);
      if(ansx==11) dbg(x,y,X,Y);
      // dbg(X,Y,ans);
      anss=max(TOT-ansx,anss);
      }

    cout<<anss<<"\n";

  }


}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}