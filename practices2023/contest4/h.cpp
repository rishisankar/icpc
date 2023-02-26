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

template<typename T> ostream& operator << (ostream &os, const vector<T> &v) { os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; db_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #___VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;
void solve()
{
  int n;
  cin>>n;

  vi v(n);
  rep(i,0,n)
  cin>>v[i];

  vector<pii> cand;
  rep(i,0,n-2)
  cand.pb({max(v[i],v[i+2]),i});

  sort(all(cand));

  cout<<cand[0].S+1<<" "<<cand[0].F<<endl;
  
}

int main()
{
  
  solve(); 
}