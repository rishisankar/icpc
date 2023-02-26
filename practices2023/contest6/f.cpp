#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(long long i = a; i  < (b); i++)
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
const ll maxf = 1e6;
void solve()
{
  ll A, B;
  cin >> A >> B;
  if(gcd(A, B) != 1) {
    cout << "no credit" << endl;
    return;
  }
  bool full = true;
  rep(i, 2, maxf) {
    if(i < A && A%i == 0) {
      full = false;
      if(A%(i*i) == 0) {
        cout << "no credit" << endl;
        return;
      }
    }
    if(i < B && B%i == 0) {
      full = false;
      if(B%(i*i) == 0) {
        cout << "no credit" << endl;
        return;
      }
    }
  }
  if(full) {
    cout << "full credit" << endl;
    return;
  }
  cout << "partial credit" << endl;
}

int main()
{
  solve();
}