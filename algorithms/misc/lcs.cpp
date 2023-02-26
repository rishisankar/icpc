/*
Longest Common Subsequence: O(|s|*|t|)
With >2 strings: careful of case (abcd bcdefgh efghbcd) -- instead extend recurrence
  - complexity for N strings is O(N*prod{string lengths})
Recurrence (for first i characters of X, j of Y):
  LCS(Xi, Yj) = {
    {} if i=0 or j=0
    LCS(Xi-1,Yj-1) ^ xi if i,j>0, xi=yj
    max{LCS(Xi-1,Yj), LCS(Xi,Yj-1)} if i,j>0, xi!=yj
  }
*/

string lcs(const string &s, const string &t) {
  int m=sz(s); int n = sz(t);
  vector<vi> dp(m+1,vi(n+1,0));
  rep(i,0,m+1) {
    rep(j,0,n+1) {
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  int len = dp[m][n];
  string res(len,' ');
  int i=m, j=n, idx=len-1;
  while(i>0 && j>0){
    if (s[i - 1] == t[j - 1]) {
      res[idx] = s[i - 1];
      i--; j--; idx--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) i--;
    else j--;
  }
  return res;
}
