#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i  < (b); i++)
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

// template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
// {
//   os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}'; 
// }



const int MOD = 1e9+7;
void solve()
{
  int n,c;
  cin>>n>>c;

  vi w(n+1,0),tin(n+1,0),tout(n+1,0);
  rep(i,1,n+1) cin>>w[i];

  int t=1;
  tin[1]=1;

  int s=1,e=1;
  ll sm=w[1];

  while(s<=n)
  {
    if(e+1>n)
    {
      tout[s]=t;
      sm-=w[s];
      s++;
    }
    else
    {
      if(sm+w[e+1]>c)
      {
        tout[s]=t;
        sm-=w[s];
        s++;
      }
      else
      {
        e++;
        tin[e]=t+1;
        sm+=w[e];
      }
    }
    t++;
  }

  rep(i,1,n+1)
  cout<<tout[i]-tin[i]+1<<"\n";
}

int main()
{
  solve();
}