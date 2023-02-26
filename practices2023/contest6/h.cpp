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
typedef pair<ll,ll> pll;

void sht(ll x, char c, int shift) {
  dbg(x,c,shift);
  char cp;
  if (shift == 0) {cp = c;}
  else if (shift == 1) {
    if (c == 'A') cp = 'B';
    else if (c == 'B') cp = 'C';
    else cp = 'A';
  } else {
    if (c == 'A') cp = 'C';
    else if (c == 'B') cp = 'A';
    else cp = 'B';
  }
  cout << cp << ' ' << x << '\n';
}


void sim(ll& a, ll& b, ll& c) {
  ll ap = a,bp = b,cp = c;
  if (a > 0) {
    if (b >= c) {
      if (bp>0)bp--;
    } else {
      if (cp>0)cp--;
    }
  }
  if (b > 0) {
    if (c >= a) {
      if (cp>0)cp--;
    } else {
      if (ap>0)ap--;
    }
  }
  if (c > 0) {
    if (a >= b) {
      if (ap>0)ap--;
    } else {
      if (bp>0)bp--;
    }
  }
  a=ap;
  b=bp;
  c=cp;
}

void bfwz(ll a, ll b, ll c, int shift) {
  if (a == 0) {
    if (b == c) {
      cout << "Rubble!\n";
      return;
    } else if (b > c) {
      sht(b-c, 'B', shift);
    } else sht(c-b, 'C', shift);
  } else if (b == 0) {
    if (a == c) {
      cout << "Rubble!\n";
      return;
    } else if (a > c) {
      sht(a-c, 'A', shift);
    } else sht(c-a, 'C', shift);
  } else {
    if (b == a) {
      cout << "Rubble!\n";
      return;
    } else if (b > a) {
      sht(b-a, 'B', shift);
    } else sht(a-b, 'A', shift);
  }
}

void bf(ll a, ll b, ll c, int shift) {
  map<pll, pair<int, tuple<ll,ll,ll>>> cyc;
  cyc[{a-b,a-c}] = {0, {a,b,c}};
  int da, db, dc;
  dbg("starting cycle scan", a,b,c);
  for (int i = 1; ; ++i) {
    sim(a,b,c);
    pll np = {a-b,a-c};
    if (cyc.count(np)) {
      da = get<0>(cyc[np].S) - a;
      db = get<1>(cyc[np].S) - b;
      dc = get<2>(cyc[np].S) - c;
      break;
    } else {
      cyc[np] = {i, {a,b,c}};
    }
  }
  if (a == 0 || b == 0 || c == 0) {
    bfwz(a,b,c,shift);
  } else {
    ll iters = a/da;
    iters = min(iters, b/db);
    iters = min(iters, c/dc);
    a -= iters*da;
    b -= iters*db;
    c -= iters*dc;
    rep(i,0,1000) sim(a,b,c);
    bfwz(a,b,c,shift);
  }
}

void solve()
{
  ll a,b,c; cin >> a >> b >> c;
  int shift;
  if (a >= b && a >= c) shift = 0;
  else if (b >= a && b >= c) {
    shift = 1;
    swap(a,b);
    swap(b,c);
  }
  else {
    shift = 2;
    swap(a,c);
    swap(b,c);
  }

  assert(a>=b && a>=c);
  if (a==b && b == c) {
    cout << "Rubble!\n";
    return;
  }

  if (a > b && b > c) {
    if (c == 0) {
      sht(a-b, 'A', shift);
      return;
    }
    ll y = b-c;
    ll x = a-b;
    ll iters = min(x,y);
    a -= 2*iters;
    b -= iters;
  } else if (a > c && c > b) {
    if (b == 0) {
      sht(a-c, 'A', shift);
      return;
    }
    ll y = c-b;
    ll x = a-c;
    ll iters = min(x,y);
    a -= 2*iters;
    c -= iters; 
  }

  if (a==b && b == c) {
    cout << "Rubble!\n";
    return;
  }

  dbg("equality case",a,b,c);

  // must be in the case of a=b>c, a=c>b, or a>(b=c)
  if (b == c) {
    ll x = a-b; // 5 1 1 -> 3 0 1 -> 2 0 0
    ll y = b;
    ll iters = min(x/3, b-1);
    a -= 4*iters;
    b -= iters;
    c -= iters;
  } else if (a == b) {
    ll x = a-c;
    ll iters = x/3;
    a -= iters*3;
    b -= iters*3;
  } else {
    ll x = a-b;
    ll iters = x/3;
    a -= iters*3;
    c -= iters*3;
  }

  dbg("prior to bf",a,b,c);

  rep(i,0,1000) sim(a,b,c);
  bf(a,b,c, shift);
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}