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
  int n;
  cin>>n;

  vi v(n);
  rep(i,0,n)
  cin>>v[i];

  ll s=accumulate(v.begin(),v.end(),0LL);
  sort(v.begin(),v.end());
  ll x=0;
  rep(i,0,(n+1)/2)
  x+=(v[i]+1)/2;

  cout<<s-x<<endl;
}

int main()
{
  solve();
}