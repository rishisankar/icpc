#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define pb push_back
using namespace std;
typedef long long ll;
const ll mod = 1000000007;


int ask(vector<int> q)
{
  reverse(q.begin(),q.end());
  cout<<"? ";
  for(auto a: q)
  cout<<a<<" ";
  cout<<endl;
  int x;
  cin>>x;
  return x;
}


void go(vector<int> q)
{
  reverse(q.begin(),q.end());
  cout<<"! ";
  for(auto a: q)
  if(a)
  cout<<"x";
  else
  cout<<"+";
  cout<<endl;
  exit(0);
}
int main() {
  unordered_map<int,int> s;
  for (int x = 0; x < (1 << 15) ; ++x) {
    int i = x;
    ll ans = 0; 
    for (int j = 0; j < 15; ++j) {
      if ((i & 1)) {
        ans *= (1 << (j+1));
      } else {
        ans += (1 << (j+1));
      }
      ans %= mod;
      i >>= 1;
    }
    s[ans]=x;
  }

  // cout<<s.size();
  // exit(0);

  int n;
  cin>>n;

  vector<int> ans(n,1); // 1 *, 0 +
  int nn=n/15;
  rep(i,0,nn)
  {
    vector<int> query(n+1,0);
    rep(j,0,i)
    {
      rep(k,0,15)
      if(ans[j*15+k]) query[j*15+k]=1;
    }


    rep(k,0,16)
    query[i*15+15-k]=((k==0)?0:(1<<k));

    int mask=s[ask(query)];
    cerr<<mask<<endl;
    rep(j,0,15)
    ans[i*15+15-j-1]=((mask&(1<<j))?1:0);
    
  }

  s.clear();
  int r=n%15;
  if(r==0)
  {
    go(ans);
  }

  for (int x = 0; x < (1 << r) ; ++x) {
    int i = x;
    ll ans = 0; 
    for (int j = 0; j < r; ++j) {
      if ((i & 1)) {
        ans *= (1 << (j+1));
      } else {
        ans += (1 << (j+1));
      }
      ans %= mod;
      i >>= 1;
    }
    s[ans]=x;
  }

   vector<int> query(n+1,0);
    rep(j,0,nn)
    {
      rep(k,0,15)
      if(ans[j*15+k]) query[j*15+k]=1;
    }


    rep(k,0,r+1)
    query[n-k]=((k==0)?0:(1<<k));

    int mask=s[ask(query)];
    // cerr<<mask<<endl;
    rep(j,0,r)
    ans[n-j-1]=((mask&(1<<j))?1:0);






  go(ans);
  
}