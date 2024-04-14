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
typedef vector<int> vi;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NIKIL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1000000000 + 7;
const int N=205;
vector<pii> moves;

const int xd[4]={-1,0,1,0};
const int yd[4]={0,1,0,-1};

struct Node
{
  int l,r,ct;
};

void solve()
{
  int m,n;
  cin>>m>>n;

  vector<vi> g(2*N,vi(2*N,0));

  rep(i,0,n)
  {
    rep(j,0,m)
    {
      char ch;
      cin>>ch;

      if(ch=='X') g[i+N][j+N]=1;
    }

    cin.ignore(10000,'\n');
  }

  if(m==1 && n==1)
  {
    cout<<0<<"\n";
    cout<<0<<"\n";
    cout<<"(1,1)\n";
    exit(0);
  }


  vector<Node> trie;
  trie.pb({-1,-1,0});

  queue<pair<pii,pii>> q;

  rep(i,0,n) rep(j,0,m)
  {
    trie[0].ct++;
    q.push(mp(mp(i,j),mp(0,0)));
  }

  vector<vi> ans(n, vi(m,0));

  while(!q.empty())
  {
    auto z=q.front();
    q.pop();
    int i=z.F.F;
    int j=z.F.S;
    int step=z.S.F;
    int node=z.S.S;

    if(trie[node].ct==1) {ans[i][j]=step-1; continue;}

    pii pos=mp(i+N,j+N);
    pii a=moves[step];
    pii cur=mp(pos.F+a.F,pos.S+a.S);
    int nxt;
    if(g[cur.F][cur.S]==1)
    {
      nxt=trie[node].r;
      if(nxt==-1)
      {
        trie[node].r=sz(trie);
        trie.pb({-1,-1,0});
      }
      nxt=trie[node].r;
    }
    else
    {
      nxt=trie[node].l;
      if(nxt==-1)
      {
        trie[node].l=sz(trie);
        trie.pb({-1,-1,0});
      }
      nxt=trie[node].l;
    }

    node=nxt;
    trie[node].ct++;
    q.push(mp(mp(i,j),mp(step+1,node)));
  }

  ll tot=0;
  rep(i,0,n) tot+=accumulate(all(ans[i]),0LL);

  dbg(tot);

  long double ev=tot/(long double)(m*n);
  cout<<fixed<<setprecision(9)<<ev<<"\n";

  int longest=0;
  rep(i,0,n) rep(j,0,m) longest=max(longest,ans[i][j]);

  cout<<longest<<"\n";

  rep(j,0,m)
  for(int i=n-1;i>=0;i--)
  {
    if(ans[i][j]==longest)
    {
      cout<<'('<<j+1<<','<<n-i<<')'<<" ";
    }
  }

  cout<<"\n";



}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  moves.pb(mp(0,0));
  int dir=0;
  int len=1;
  pii cur=mp(0,0);
  while(sz(moves)<N*N)
  {
    rep(k,0,2)
    {
      rep(j,0,len)
      {
        pii nxt=cur;
        nxt.F+=xd[dir];
        nxt.S+=yd[dir];
        moves.pb(nxt);
        cur=nxt;
      }

      dir=(dir+1)%4;
    }
    len++;
  }

  rep(i,0,t)
    solve();
}
