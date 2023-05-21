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

int magic(string A, string B, string C)
{
  int n=sz(A);
  int ans=MOD;

  map<string,int> m;
  rep(i,0,n)
  {
    string c(n,' ');
    rep(j,0,n)
    c[(j+i)%n]=C[j];
    if(m.find(c)==m.end()) m[c]=min(i,n-i);
    else m[c]=min(m[c],min(i,n-i));
  }

  rep(i,0,n)
  {
    bool good=true;
    rep(j,0,n)
    if(A[j]==B[(j+i)%n]) good=false;
    if(!good) continue;

    string c(n,' ');
    rep(j,0,n)
    {
      if(A[j]!='A' && B[(j+i)%n]!='A') c[j]='A';
      if(A[j]!='B' && B[(j+i)%n]!='B') c[j]='B';
      if(A[j]!='C' && B[(j+i)%n]!='C') c[j]='C';
    }

    if(m.find(c)!=m.end())
    {
      ans=min(ans,min(i,n-i)+m[c]);
      // dbg(i,c,m[c]);
    }
  }
  return ans;
}


void solve() {
  string A,B,C;
  cin>>A>>B>>C;

  int ans=MOD;
  ans=min(ans,magic(A,B,C));
  ans=min(ans,magic(B,C,A));
  ans=min(ans,magic(C,A,B));

  if(ans==MOD) ans=-1;
  cout<<ans<<"\n";
  
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
}