#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int) (x).size()
#define rep(i,a,b) for(int i = a; i < (b); ++i)

typedef long long ll;
int main(){
  int n;
  cin>>n;
  int l;
  cin>>l;
  vector<int> save(l);
  for(int &a:save)
    cin>>a;
  bool increasing=true;
  for(int i=0;i<save.size()-1;i++){
    if(save[i+1]<=save[i]){
      increasing=false;
    }
  }
  //cout<<save[save.size()-1]<<"\n";
  if(save[save.size()-1]!=n||!increasing){
    cout<<0<<"\n";
    return 0;
  }
  ll ways =1;
  ll fixed=0;
  ll placed=0;
  for(int i=save.size()-1-1;i>=0;i--){
    for(int imp=save[i]+1;imp<save[i+1];imp++){
      ways=(ways*(placed+fixed+1))%1000000007;
      placed++;
    }
    fixed++;
  }
  for(int left=1;left<save[0];left++){
    ways=(ways*(placed+fixed+1))%1000000007;
    placed++;
  }
  cout<<ways<<"\n";
}