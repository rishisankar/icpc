#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i  < (b); i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define trav(a, x) for(auto& a: x)
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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ")";
}

void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;

int n;
vector<vi> childs;
vector<ll> cap, val;
vector<set<pair<ll,int>>> sets;

set<pair<ll,int>>* merge(set<pair<ll,int>>* p1, set<pair<ll,int>>* p2) {
  if (p1->size() > p2->size()) {
    // push p2 into p1
    for (auto x : (*p2)) {
      p1->insert(x);
    }
    return p1;
  } else {
    // push p1 into p2
    for (auto x : (*p1)) {
      p2->insert(x);
    }
    return p2;
  }
}

set<pair<ll,int>>* test(int t) {
  sets[t].insert({val[t], t});
  set<pair<ll,int>>* mergeptr = &(sets[t]);
  for (int chd : childs[t]) {
    auto res = test(chd);
    mergeptr = merge(mergeptr, res);
  }
  if (mergeptr->size() > cap[t]) {
    int amtToErase = mergeptr->size() - cap[t];
    auto it = mergeptr->begin();
    advance(it, amtToErase);
    mergeptr->erase(mergeptr->begin(), it);
  }
  return mergeptr;
}

void solve()
{
  cin >> n;
  childs.resize(n);
  rep(i,0,n-1) {
    int x; cin >> x; --x;
    childs[x].pb(i+1);
  }
  cap.resize(n); val.resize(n);
  rep(i,0,n) { cin >> cap[i]; }
  rep(i,0,n) { cin >> val[i]; }
  sets.resize(n);

  auto ptr = test(0);
  ll ans = 0;
  for (auto x : (*ptr)) {
    ans += x.F;
  }
  cout << ans << '\n';
  cout << (*ptr).size();
  vector<int> answers;
  for (auto x : (*ptr)) {
    answers.pb(x.S+1);
  }
  sort(all(answers));
  for (int x : answers) { cout << ' ' << x; }
  cout << '\n';
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}