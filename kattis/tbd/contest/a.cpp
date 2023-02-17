#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {

  int n;
  cin>>n;

  vector<int> v(n),t(n);
  for(int i=0;i<n;i++)
  cin>>v[i];
  for(int i=0;i<n;i++)
  cin>>t[i];

  vector<pair<int,int>> s;
  for(int i=0;i<n;i++)
  if(t[i]!=-1) s.push_back({t[i],v[i]});

  sort(s.begin(),s.end());

  ll ans=1;
  ll total=0;

  for(int i=0;i<s.size();i++)
  {
    total+=s[i].second;
    // cout<<total<<" "<<s[i].first<<" "<<s[i].second<<endl;
    while(total>(s[i].first*ans)) ans++;
  }

  cout<<ans<<endl;


}