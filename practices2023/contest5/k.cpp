#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for (auto& a: x)
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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

int query(ull u1, ull u2) {
  cout << "q " << u1 << ' ' << u2 << endl;
  int x; cin >> x;
  return x;
}

void solve(ull ri, ull rf, int sb, unordered_set<ull>& bits) {
  if (sb == 0) return;
  if (ri == rf) {
    bits.insert(ri);
    return;
  }
  ull mid = (ri+rf)/2;
  int x = query(ri, mid);
  solve(ri,mid, x, bits);
  solve(mid+1,rf,sb-x,bits);
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ull mx = 1;
  rep(i,0,63){mx *= 2;}
  mx-=1;
  int sb = query(0,mx);
  unordered_set<ull> bits;
  solve(0, mx, sb, bits);
  vector<ull> v;
  for (ull x : bits) {
    v.push_back(x);
  }
  sort(all(v));
  cout << "a ";
  cout << v.size();
  for (ull x : v) {
    cout << ' ' << x;
  }
  cout << '\n';
}
