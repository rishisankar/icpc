#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int segT[4*300005][12][12];
vector<vector<int>> query(int idx,int lB,int rB,int l, int r){
  
  int mid=(lB+rB)/2;
  query(idx*2,lB,mid,l,r);
  query(idx*2+1, mid+1,rB,l,r);
}
void build(int idx,int lB,int rB){
  if(lB==rB)
    return;
  int mid=(lB+rB)/2;
  build(idx*2,lB,mid);
  build(idx*2+1, mid+1,rB);
}
int main(){
  int n;
  cin>>n;
  int info[n][12];
  for(int i=0;i<n;i++){
    for(int j=0;j<12;j++){
      cin>>info[i][j];
    }
  }
  int q;
  cin>>q;
  for(int i=0;i<q;i++){

  }
}