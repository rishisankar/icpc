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

  vi v1(n),v2(n);
  rep(i,0,n)
  cin>>v1[i];
  rep(i,0,n)
  cin>>v2[i];

  multiset<int> seen,need;
  rep(i,0,n)
  {
    cout<<v2[i]<<" ";
    seen.insert(v1[i]);
    need.insert(v2[i]);

    if(need.count(v1[i]))
    {
      seen.erase(seen.find(v1[i]));
      need.erase(need.find(v1[i]));
    }

    if(seen.count(v2[i]) && need.count(v2[i]))
    {
      seen.erase(seen.find(v2[i]));
      need.erase(need.find(v2[i]));
    }
    
    if(need.size()==0 && i!=(n-1)) cout<<"# ";
  }

  cout<<"\n";
}

int main()
{
  solve();
}