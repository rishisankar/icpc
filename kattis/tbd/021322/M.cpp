#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;

const int MOD = 1000000007;
int main()
{
  int n, p;
  cin >> n >> p;
  ll pSum[n + 1];
  pSum[0] = 1;
  // pSum[i]=ways[0]+...+ways[i]
  ll ways[n + 1];
  ways[0] = 1;
  // numbers of ways given length i
  vector<array<int, 2>> v;
  for (int i = 0; i < p; i++)
  {
    int a, b;
    cin >> a >> b;
    a--,b--;
    if(a>b)
      swap(a,b);
    v.push_back({b, a});
  }
  sort(v.begin(), v.end());
  int bigS = -1;
  int vIdx = 0;

  for (int i = 0; i < n; i++)
  {
    while (vIdx < p && v[vIdx][0] <= i)
    {
      bigS = max(bigS, v[vIdx][1]);
      vIdx++;
    }
    if (bigS == -1)
    {
      ways[i + 1] = pSum[i];
    }
    else
      ways[i + 1] = (pSum[i] - pSum[bigS] + MOD) % MOD;
    pSum[i + 1] = (pSum[i] + ways[i + 1]) % MOD;
  }
  // for(int i=0;i<=n;i++)
  //   cout<<ways[i]<<' ';
  // cout<<"\n";
  cout << ways[n] << "\n";
}
