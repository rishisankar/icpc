#include <bits/stdc++.h>

using namespace std;

int main() {
  int m, n; 
  cin >> n >> m; 
  vector<long long> canSizes(n); 
  vector<long long> amountPerColor(m); 
  for(int i = 0; i < n; i++){
    cin >> canSizes[i]; 
  }
  for(int i = 0; i < m; i++){
    cin >> amountPerColor[i]; 
  }

  sort(canSizes.begin(), canSizes.end()); 

  long long amountWasted =0; 

  for(int i = 0; i < m; i++){
    int low = 0; 
    int high = n - 1; 
    int med  = (low + high)/2; 
    while(low < high ){
      //printf("ASDF %d %d %d \n", med, low, high);
      if(canSizes[med] > amountPerColor[i]){
        high = med; 
        med = (low + high) /2; 
      }
      else if(canSizes[med] < amountPerColor[i]){
        low = med + 1; 
        med = (low + high) /2; 
      }
      else{
        break; 
      }
    }
    amountWasted += (canSizes[med] - amountPerColor[i]); 
  }

  cout << amountWasted << '\n';
}