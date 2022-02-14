#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int low=-1,big=1001;
    for (int i = 0; i <n;i++){
        int a,b;
        cin>>a>>b;
        low=max(low,a);
        big=min(big,b);
    }
 //   cout<<low<<" "<<big<<"\n";
    if(low<=big){
        cout<<"gunilla has a point"<<"\n";
    }else{
        cout<<"edward is right"<<"\n";
    }
}