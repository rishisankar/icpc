#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string lcs(const string &s, const string &t) {
  int m=s.size(); int n=t.size();
  vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

  for(int i=0;i<m+1;i++) {
    for(int j=0;j<n+1;j++) {
      if (i == 0 || j == 0) {
        dp[i][j] = 0;
      } else if (s[i-1] == t[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  int len = dp[m][n];
  string res(len, ' ');

  int i = m, j = n, idx=len-1;
  while (i > 0 && j > 0) {
    if (s[i-1] == t[j-1]) {
      res[idx] = s[i-1];
      i--; j--; idx--;
    } else if (dp[i-1][j] > dp[i][j-1]) i--;
    else j--;
  }
  return res;
}


int main() {

  int n;
  cin>>n;

  string s,t;
  cin>>s>>t;

  int nt=n/10;
  string ans;
  for(int i=0;i<nt;i++)
  {
    ans+=lcs(s.substr(i*10,10),t.substr(i*10,10));
  }
  if(n%10)
  ans+=lcs(s.substr(nt*10),t.substr(nt*10));

  cout<<ans<<endl;
}