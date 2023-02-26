#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i  < (b); i++)
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{
  os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}'; 
}



const int MOD = 1e9+7;
void solve()
{
  int S, N;
  cin >> S >> N;
  int seats[N+1];
  rep(i, 0, N) cin >> seats[i];
  seats[N] = seats[0]+S;
  int ans = 0;
  rep(i, 0, N) {
    ans += (seats[i+1]-seats[i]-2)/2;
  }
  cout << ans << endl;
}

int main()
{
  solve();
}