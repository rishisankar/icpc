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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;

void solve() {
  unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
  auto engine = std::default_random_engine(seed);
  int n, m; cin >> n >> m;
  vector<set<int>> v(n);
  rep(i,0,m) {
    int a,b; cin >> a >> b;--a; --b;
    v[a].insert(b);
    v[b].insert(a);
  }
  vector<int> p(n);
  rep(i,0,n) p[i]=i;
  rep(t, 0, 1000000) {
    shuffle(p.begin()+1,p.end(), engine);
    vector<int> pth;
    rep(j, 1, n) {
      if (v[p[j-1]].count(p[j])) {
        pth.push_back(0);
      } else pth.push_back(1);
    }
  
    vi sp(pth);
    sort(all(sp));
    bool flag = true;
    rep(i,0,n-1) {
      if (sp[i] != pth[i]) flag = false;
    }
    if (flag) {
      rep(i,0,n) {
        cout << (p[i]+1) << ' ';
      }
      cout << '\n';
      exit(0);
    }
    reverse(all(sp));
    flag = true;
    dbg(pth,sp);
    rep(i,0,n-1) {
      if (sp[i] != pth[i]) flag = false;
    }
    if (flag) {
      rep(i,0,n) {
        cout << (p[i]+1) << ' ';
      }
      cout << '\n';
      exit(0);
    }
  }
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}