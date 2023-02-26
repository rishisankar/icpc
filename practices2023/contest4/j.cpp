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
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;

bool toyprefers(int c1, int c2, int ty, vector<vector<int>>& tp) {
  for (int i : tp[ty]) {
    if (i == c1) return true;
    if (i == c2) return false;
  }
  return false; // never should get here
}

void solve()
{

  int n,m; cin >> n >> m; // n: children, m: toys
  ll d; int e; cin >> d >> e; // d = end; e = # events
  vector<vector<ll>> inp(e, vector<ll>(3)); // (s, k, t)
  rep(i,0,e) {
    rep(j,0,3) {
      cin >> inp[i][j];
      if (j>0) --inp[i][j]; //0-index
    }
  }

  dbg(inp);

  // case 1: impossible
  if (n > m) {
    cout << "impossible\n";
    return;
  }

  // generate kid preferences:
  vector<vector<int>> kp(n);  // kp[i]: toys in preference order
  vector<unordered_set<int>> child_taken(n); //which toys has each child ranked
  rep(i,0,e) {
    int chl = inp[i][1];
    int ty = inp[i][2];
    if (ty == -1) continue;
    if (child_taken[chl].count(ty)) continue;
    kp[chl].push_back(ty);
    child_taken[chl].insert(ty);
  }
  rep(chl,0,n) {
    rep(ty,0,m) {
      if (!child_taken[chl].count(ty)) kp[chl].push_back(ty);
    }
  }

  // generate toy preferences:
  vector<vector<int>> tp(m);
  vector<vector<ll>> toy_dur(m, vector<ll>(n, 0));  //toy_dur[ty][chl] = amount toy ty played with child chl yesterday
  
  vector<pii> curtoy(n, {-1,0}); // represents {curtoy, when got it}
  rep(i,0,e) {
    int s = inp[i][0];
    int chl = inp[i][1];
    int ty = inp[i][2];  
    if (curtoy[chl].F != -1) {
      // end playing with another toy
      int cty = curtoy[chl].F;
      toy_dur[cty][chl] += (s - curtoy[chl].S);
    }
    curtoy[chl] = {ty, s};
  }
  // each child stop playing w their toy at time d
  rep(i,0,n) {
    if (curtoy[i].F != -1) {
      toy_dur[curtoy[i].F][i] += (d - curtoy[i].S);
    }
  }
  rep(ty,0,m) {
    vector<pii> toydur_sort;
    rep(i,0,n) {
      toydur_sort.push_back({toy_dur[ty][i],i});
    }
    sort(all(toydur_sort));
    rep(i,0,n) {
      tp[ty].push_back(toydur_sort[i].S);
    }
  }

  dbg(kp);
  dbg(tp);
  // run stable matching: kp(n), tp(m)
  vector<int> kid_matches(n, -1);
  vector<int> toy_matches(m, -1);
  stack<int> unmatched_kids;
  vector<int> kid_prop(n,0); // next toy kid proposes to on proposal list
  rep(i, 0, n) {
    unmatched_kids.push(i);
  }
  while (!unmatched_kids.empty()) {
    int chl = unmatched_kids.top();
    unmatched_kids.pop();
    while (kid_prop[chl] < m) {
      // try proposing to toy
      int ty = kp[chl][kid_prop[chl]];
      dbg("case1", chl, ty);
      ++kid_prop[chl];
      if (toy_matches[ty] == -1) {
        // toy not matched --> match to child
        kid_matches[chl] = ty;
        toy_matches[ty] = chl;
        break;
      } else {
        // check if better match (i.e. toy prefers child chl to current match)
        int cur_mch = toy_matches[ty];
        dbg("case2", chl, ty, cur_mch);
        if (toyprefers(chl, cur_mch, ty, tp)) {
          kid_matches[chl] = ty;
          toy_matches[ty] = chl;
          kid_matches[cur_mch] = -1;
          unmatched_kids.push(cur_mch);
          break;
        }
      }
    }
    dbg(chl, kid_matches[chl]);
    if (kid_prop[chl] == m && kid_matches[chl] == -1) {
      assert(false);
      return;
    }
  }

  rep(i, 0, n) {
    cout << (kid_matches[i]+1) << ' ';
  }
  cout << '\n';

}

int main()
{
  solve(); 
}