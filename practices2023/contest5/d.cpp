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

int L;
int S;

vector<vector<tuple<int, bool, bool>>> trans(100,vector<tuple<int, bool, bool>>(2));

bool countB(int bits, int b) {
  return (bits & (1<<b));
}

void setB(int& bits, int b) {
  if (!countB(bits,b)) bits += (1<<b);
}

void unsetB(int& bits, int b) {
  if (countB(bits,b)) bits -= (1<<b);
}

// returns true if halts
bool test(int tape) {
  int state = 0;
  int pos = 0;
  rep(step, 0, L) {
    tuple<int,bool,bool> tup = trans[state][countB(tape,pos)]; // (t,o,d)
    dbg(step, get<0>(tup), get<1>(tup), get<2>(tup));
    if (get<1>(tup) == 1) {
      setB(tape,pos);
    } else {
      unsetB(tape,pos);
    }
    state = get<0>(tup);
    if (get<2>(tup) == 0) {
      pos = max(0, pos-1);
    } else {
      ++pos;
    }
    if (state == -1) return true;
  }
  return false;
}

void solve() {

  cin >> L;
  cin >> S;

  rep(inp,0,2*S) {
    int s,t;
    int i,o,d;
    cin >> s >> i >> t >> o >> d;
    assert (s >= 0 && s < S);
    trans[s][i] = {t,o,d};
  }

  for (int i = 0; i < (1<<(L+1)); ++i) {
    if (!test(i)) {
      cout << "0\n";
      return;
    }
  }
  cout << "1\n";
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}