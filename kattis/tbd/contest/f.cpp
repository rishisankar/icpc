#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void bad()
{
  cout<<"impossible"<<endl;
  exit(0);
}

void good()
{
  cout<<"possible"<<endl;
  exit(0);
}

int main() {

  int n;
  cin>>n;

  
  vector<ll> B(n),P(n);
  multiset<pair<ll,ll>> players;
  for(int i=0;i<n;i++)
  {
    cin>>B[i]>>P[i];
    players.insert({B[i],P[i]});
  }

  if(n%2)bad();

  int t=n/2;

  ll tb=accumulate(B.begin(),B.end(),0LL);
  ll tp=accumulate(P.begin(),P.end(),0LL);

  if(tb%t) bad();
  if(tp%t) bad();

  tb/=t;
  tp/=t;

  
  while(!players.empty())
  {
    pair<ll,ll> p1=*players.begin();
    players.erase(players.find(p1));

    pair<ll,ll> p2={tb-p1.first,tp-p1.second};
    if(players.find(p2)==players.end()) bad();
    players.erase(players.find(p2));
  }
  good();
}