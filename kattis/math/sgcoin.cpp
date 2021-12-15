#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(cont) cont.begin(), cont.end()

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

typedef long long ll;
typedef long double ld;
typedef vector<int> VI;
typedef vector<vector<int>> VVI;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;

long long H(long long previousHash, string transaction) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7) % 1000000007;
}

long long res(long long previousHash, string transaction, long long token) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    string s1 = "charlie-pays-to-eve-9-sg-coins";
    string s2 = "icpc-sg-2018-at-nus";

    ll g1 = MOD + 10000000LL;
    ll g2 = 990000000LL;

    ll N; cin >> N;
    ll h1 = H(N, s1);
    ll t1, t2;
    if (h1 < g2) {
        t1 = g2 - h1;
    } else {
        t1 = g1 - h1;
    }
    
    ll r = res(N, s1, t1);

    ll h2 = H(r, s2);
    if (h2 < g2) {
        t2 = g2 - h2;
    } else {
        t2 = g1 - h2;
    }

    cout << s1 << " " << t1 << '\n';
    cout << s2 << " " << t2 << '\n';
}