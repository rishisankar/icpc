#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for(auto &a: x)
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

template<typename T> ostream& operator << (ostream &os, const vector<T> &v) { os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;
void solve()
{
  string s;
  cin>>s;

  char c=s[sz(s)-1];

  int n;
  cin>>n;

  map<char,vector<string>> words;
  rep(i,0,n)
  {
    string t;
    cin>>t;
    words[t[0]].pb(t);
  }

  if(sz(words[c])==0)
  {
    cout<<"?"<<endl;
    return;
  }

  trav(a,words[c])
  {
    if(sz(words[a[sz(a)-1]])==0)
    {
      cout<<a<<"!"<<endl;
      return;
    }
    if(a[sz(a)-1]==c && sz(words[a[sz(a)-1]])==1)
    {
      cout<<a<<"!"<<endl;
      return;
    }
  }

  trav(a,words[c])
  {
    cout<<a<<endl;
    return;
  }
}

int main()
{

  solve(); 
}