#include <bits/stdc++.h>
 
#define MAXN 200005
 
typedef long long ll;
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string ops;
	cin >> ops;
	vector<int> stack;
	for (char a : ops) {
		if (a == '1')
			stack.push_back(1);
		else if (a == 'd')
			stack.push_back(stack.back());
		else {
			int a=stack.back();
			stack.pop_back();
			int b= stack.back();
			stack.pop_back();
			for(int& a:stack)
				a--;
			stack.push_back(a+b);
		}
	}
	for(int a:stack)
		cout<<a<<" ";
    
    cout<<'\n';
 
}
 