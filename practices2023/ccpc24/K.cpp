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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1000000000 + 7;
int n,m;

const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1};

void expand(set<vector<vi>> &starts, set<vector<vi>> &ends, set<vector<vi>> &seen)
{
  trav(a,starts)
  {
    rep(i,0,n)
    rep(j,0,m)
    {
      if(a[i][j]==0)
      {
        rep(k,0,4)
        {
          int x=i+xd[k];
          int y=j+yd[k];

          if(x>=0 && x<n && y>=0 && y<m)
          {
            vector<vi> next=a;
            swap(next[i][j],next[x][y]);
            if(seen.find(next)==seen.end())
            {
              seen.insert(next);
              ends.insert(next);
            }
          }
        }
      }
    }
  }
}

vector<set<vector<vi>>> search(vector<vi> &start, int steps)
{
  vector<set<vector<vi>>> state(steps+1);
  state[0].insert(start);

  set<vector<vi>> seen;
  seen.insert(start);

  rep(i,1,steps+1)
  {
    expand(state[i-1], state[i],seen);
  }

  return state;
}

void solve()
{
  cin>>n>>m;

  vector<vi> v(n,vi(m));
  rep(i,0,n) rep(j,0,m) cin>>v[i][j];

  vector<vi> goal(n,vi(m));
  int zzz=1;
  rep(i,0,n) rep(j,0,m) goal[i][j]=zzz++;
  goal[n-1][m-1]=0;

  int best=42;
  vector<set<vector<vi>>> forward=search(v,10);
  vector<set<vector<vi>>> backward=search(goal,10);

  rep(i,0,11)
  {
    trav(a,forward[i])
    rep(j,0,11)
    if(backward[j].find(a)!=backward[j].end())
    best=min(best,i+j);
  }

  cout<<best<<"\n";


}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t;
  cin>>t;

  rep(i,0,t)
    solve();
}
