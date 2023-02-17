#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define pb push_back
using namespace std;
typedef long long ll;

const int MOD=1000000000+7;


bool ya(int mask, int i)
{
  return (mask&(1<<i))!=0;
}

bool valid(int mask)
{
  vector<int> v;
  rep(i,0,12)
  if(ya(mask,i)) v.push_back(i);

  rep(i,1,v.size())
  {
    if(v[i]==v[i-1]+1) return false;
  }
  return true;
}


int main() {

  int n,m;
  cin>>n>>m;

  vector<string> grid(n);
  rep(i,0,n)
  cin>>grid[n-i-1];

  n/=2;

  vector<vector<int>> g(1<<(m-1));
  rep(i,1,(1<<(m-1)))
  {
    if(!valid(i)) continue;
  rep(j,1,(1<<(m-1)))
    {
       if(!valid(j)) continue;
       bool ok=true;
      rep(k,0,m-1)
      {
        if(!ya(i,k)) continue;
        bool gd=false;
        if(k-1>=0 && ya(j,k-1))
        {
          gd=true;
        }
        if(ya(j,k))
        {
          gd=true;
        }
        if(k+1<m-1 && ya(j,k+1))
        {
          gd=true;
        }
        if(!gd) ok=false;
      }
      if(ok) g[i].pb(j);
    }
  }

  vector<vector<int>> dp(n,vector<int>((1<<(m-1)),MOD));
  int highest=-1;
  rep(i,0,n)
  {
    int total_stars=0;
    rep(j,0,m)
    {
      if(grid[2*i][j]=='#') total_stars++;
      if(grid[2*i+1][j]=='#') total_stars++;
    }

    if(total_stars!=0) highest=i;

    rep(mask1,1,(1<<(m-1)))
    {
      if(!valid(mask1)) continue;
      int covered=0;
      rep(j,0,m-1)
      {
        if(!ya(mask1,j)) continue;
        if(grid[2*i][j]=='#') covered++;
        if(grid[2*i+1][j]=='#') covered++;
        if(grid[2*i][j+1]=='#') covered++;
        if(grid[2*i+1][j+1]=='#') covered++;
      }
      if(covered!=total_stars) continue;

      if(i==0)
      {
         dp[i][mask1]=min(dp[i][mask1],__builtin_popcount(mask1));
      }
      else
      {
        for(auto mask2:g[mask1])
        {
          dp[i][mask1]=min(dp[i][mask1],dp[i-1][mask2]+__builtin_popcount(mask1));
        }
      }

    }
  }

  if(highest==-1)
  {
    cout<<0<<endl;
    return 0;
  }
  
  int ans=MOD;
  rep(mask,1,(1<<(m-1)))
  ans=min(ans,dp[highest][mask]);

  cout<<ans<<endl;

  }