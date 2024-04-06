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

#ifdef NIKIL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1000000000 + 7;

int C=1231;
typedef int64_t H;
H hsh(string& s){H h{}; for(char c:s) h=h*C+c;return h;}
char ch='z'+1;
string wildcard(4,ch);

void solve()
{
  int N,A,M,B;
  cin>>N>>A>>M>>B;

  vector<string> rows(A),cols(B);
  rep(i,0,A) cin>>rows[i];
  rep(i,0,B) cin>>cols[i];

  if(A>B)
  {
    swap(A,B);
    swap(N,M);
    swap(rows,cols);
  }

  if(N!=4)
  {
    trav(a,rows)
    {
      int z=sz(a);
      rep(i,0,4-z) a+=ch;
    }
    cols.pb(wildcard);
  }

  if(M!=4)
  {
    trav(a,cols)
    {
      int z=sz(a);
      rep(i,0,4-z) a+=ch;
    }
    rows.pb(wildcard);
  }

  unordered_set<H> good;
  trav(a,rows) good.insert(hsh(a));

  vector<vector<vi>> cand(27,vector<vi>(27));
  rep(i,0,sz(cols))
  cand[cols[i][0]-'a'][cols[i][1]-'a'].pb(i);

  int ans=0;
  vector<string> pre(4,string(2,'a'));
  vector<string> check(2,string(4,'a'));
  rep(i,0,A)
  {
    if(rows[i]==wildcard) continue;
    rep(j,0,A)
    {
      if(rows[j]==wildcard) continue;
      rep(k,0,4) {pre[k][0]=rows[i][k];pre[k][1]=rows[j][k];}
      if(sz(cand[pre[0][0]-'a'][pre[0][1]-'a'])==0) continue;
      if(sz(cand[pre[1][0]-'a'][pre[1][1]-'a'])==0) continue;
      if(sz(cand[pre[2][0]-'a'][pre[2][1]-'a'])==0) continue;
      if(sz(cand[pre[3][0]-'a'][pre[3][1]-'a'])==0) continue;
      trav(a,cand[pre[0][0]-'a'][pre[0][1]-'a'])
      {
        check[0][0]=cols[a][2];
        check[1][0]=cols[a][3];
        trav(b,cand[pre[1][0]-'a'][pre[1][1]-'a'])
        {
          check[0][1]=cols[b][2];
          check[1][1]=cols[b][3];
          trav(c,cand[pre[2][0]-'a'][pre[2][1]-'a'])
          {
            check[0][2]=cols[c][2];
            check[1][2]=cols[c][3];
            trav(d,cand[pre[3][0]-'a'][pre[3][1]-'a'])
            {
              check[0][3]=cols[d][2];
              check[1][3]=cols[d][3];
              // now only need to check that the rows make sense
              bool ok=true;
              ok=ok&&(good.find(hsh(check[0]))!=good.end());
              ok=ok&&(good.find(hsh(check[1]))!=good.end());
              if(ok) ans++;
            }
          }
        }
      }
    }
  }

  cout<<ans<<"\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  rep(i,0,t)
    solve();
}