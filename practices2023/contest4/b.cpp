#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for(auto &a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define int ll

template<typename T> ostream& operator << (ostream &os, const vector<T> &v) { os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;

struct rect
{
  int a;
  int b;
  void rot() {swap(a, b);}
};
const int INF = 9e18;
int minA(rect r1, rect r2, rect r3)
{
  int A = INF;
  rep(i, 0, 8) {
    rect c1 = r1, c2 = r2, c3 = r3;
    if(i&1) c1.rot();
    if(i&2) c2.rot();
    if(i&4) c3.rot();
    if(c1.b > c2.b) swap(c1, c2);
    if(c3.a <= c1.a) {
      //cout << (c1.a+c2.a) << ' ' << max(c1.b + c3.b, c2.b) << endl;
      A = min(A, (c1.a+c2.a)*max(c1.b+c3.b, c2.b));
    }
    //cout << max(c1.a+c2.a, c3.a) << ' ' << (c2.b+c3.b) << endl;
    A = min(A, max(c1.a+c2.a, c3.a)*(c2.b+c3.b));
    A = min(A, (c1.a+c2.a+c3.a)*max(max(c1.b, c2.b), c3.b));
  }
  return A;
}

void solve()
{
  int a1, b1, a2, b2, a3, b3;
  cin >>  a1 >> b1 >> a2 >> b2 >> a3 >> b3;
  rect r1{a1, b1}, r2{a2, b2}, r3{a3, b3};
  int A = INF;
  A = min(A, minA(r1, r2, r3));
  A = min(A, minA(r1, r3, r2));
  A = min(A, minA(r3, r2, r1));
  cout << A << endl;
}

int32_t main()
{
  int t;
  cin >> t;
  rep(i, 0, t) {
    solve(); 
  }
}