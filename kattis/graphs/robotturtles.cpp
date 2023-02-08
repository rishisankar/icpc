#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<pair<int, int>,int> piii;
typedef pair<pair<int, int>,pair<int, int>> p4i;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NIKIL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(_VA_ARGS_)
#else
#define dbg(...)
#endif

const int MOD = 1000000000 + 7;
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};
vector<string> grid(8);
char parc[8][8][1024][4];

bool in_mask(int mask, int i)
{
  return ((mask&(1<<i))!=0);
}

void solve()
{
  rep(i,0,8)
  cin>>grid[i];

  map<pii,int> castle_idx;
  rep(i,0,8)
  rep(j,0,8)
  if(grid[i][j]=='I')
  {
    castle_idx[{i,j}]=sz(castle_idx);
  }

  int n=sz(castle_idx);

  vector<vector<vector<vector<bool>>>> vis(8,vector<vector<vector<bool>>>(8,vector<vector<bool>>((1<<n),vector<bool>(4,false))));
  vector<vector<vector<vector<p4i>>>> par(8,vector<vector<vector<p4i>>>(8,vector<vector<p4i>>((1<<n),vector<p4i>(4,{{-1,-1},{-1,-1}}))));

  vis[7][0][0][1]=true;
  queue<p4i> q;
  q.push({{7,0},{0,1}});

  while(!q.empty())
  {
    p4i x=q.front();
    dbg(x,par[x.F.F][x.F.S][x.S.F][x.S.S]);
    q.pop();

    if(grid[x.F.F][x.F.S]=='D')
    {
      string res;
      while(par[x.F.F][x.F.S][x.S.F][x.S.S].F.F!=-1)
      {
        res+=parc[x.F.F][x.F.S][x.S.F][x.S.S];
        x=par[x.F.F][x.F.S][x.S.F][x.S.S];
      }
      reverse(all(res));
      cout<<res<<"\n";
      return;
    }

    int nx=x.F.F+xd[x.S.S];
    int ny=x.F.S+yd[x.S.S];

    if(nx>7 || nx<0) continue;
    if(ny>7 || ny<0) continue;
    // if(grid[nx][ny]=='C') continue;

    // try moving forward
    p4i nxt={{nx,ny},x.S};
    if(!vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S])
    {
      if(grid[nx][ny]=='D' || grid[nx][ny]=='.' || (grid[nx][ny]=='I' && in_mask(x.S.F,castle_idx[{nx,ny}])))
      {
        vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=true;
        par[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=x;
        parc[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]='F';
        q.push(nxt);
      }
    }

    if(grid[nx][ny]=='I' && !in_mask(x.S.F,castle_idx[{nx,ny}]))
    {
      int new_mask=x.S.F^(1<<(castle_idx[{nx,ny}]));
      nxt={{x.F.F,x.F.S},{new_mask,x.S.S}};
      if(!vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S])
      {
        vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=true;
        par[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=x;
        parc[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]='X';
        q.push(nxt);
      }
    }

    // now turning L
    nxt={{x.F.F,x.F.S},{x.S.F,(x.S.S+1)%4}};
    if(!vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S])
    {
      vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=true;
      par[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=x;
      parc[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]='L';
      q.push(nxt);
    }

    // now turning R
    nxt={{x.F.F,x.F.S},{x.S.F,(x.S.S-1+4)%4}};
    if(!vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S])
    {
      vis[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=true;
      par[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]=x;
      parc[nxt.F.F][nxt.F.S][nxt.S.F][nxt.S.S]='R';
      q.push(nxt);
    }
  }

  cout<<"no solution\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  rep(i,0,t)
    solve();
}