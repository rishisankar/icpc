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
void solve()
{

  vector<char> actual(5, '_');
  vector<unordered_set<char>> imp(5);
  vector<pair<int,bool>> occ(26, {0, false}); //amt, exact 
  int n; cin >> n;
  int w; cin >> w;
  rep(i,0,n) {
    string guess; cin >> guess;
    string res; cin >> res;
    unordered_map<char, int> gyocc;
    unordered_set<char> gray;
    unordered_set<char> chars;
    rep(j,0,5) {
      chars.insert(guess[j]);
      if (res[j] == 'G') {
        actual[j] = guess[j];
      } else {
        imp[j].insert(guess[j]);
      }
      if (res[j] == 'G' || res[j] == 'Y') {
        if (gyocc.count(guess[j])) gyocc[guess[j]]++;
        else gyocc[guess[j]] = 1;
      }
      else {
        gray.insert(guess[j]);
      }
    }
    for (char c : chars) {
      if (gray.count(c)) {
        int ct = 0;
        if (gyocc.count(c)) ct =  gyocc[c];
        occ[(c-'A')] = {ct, true};
      } else {
        if (occ[(c-'A')].second == false) {
          occ[(c-'A')].first = max(occ[(c-'A')].first, gyocc[c]);
        }
      }
    }
  }

  dbg(actual);
  dbg(occ);
  dbg(occ['L'-'A']);

  rep(i,0,w) {
    string guess; cin >> guess;
    unordered_set<char> chars;
    unordered_map<char,int> occs;
    bool failed = false;
    rep(j, 0, 5) {
      chars.insert(guess[j]);
      if (occs.count(guess[j])) occs[guess[j]]++;
      else occs[guess[j]] = 1;
      if (actual[j] != '_' && actual[j] != guess[j]) { failed = true; break;}
      if (imp[j].count(guess[j])) { failed = true; break;}
    }
    if (failed) continue;
    for (char c : chars) {
      dbg(c, occ[(c-'A')], occs[c]);
      if (occ[(c-'A')].second) {
        if (occs[c] != occ[(c-'A')].first) {failed =true; break;}
      } else {
        if (occs[c] < occ[(c-'A')].first) {failed =true; break;}
      }
    }
    if (failed) continue;
    rep(j,0,26) {
      char test = ('A'+j);
      if (!occs.count(test)) occs[test] = 0;
      if (occ[(test-'A')].second) {
        if (occs[test] != occ[(test-'A')].first) {failed =true; break;}
      } else {
        if (occs[test] < occ[(test-'A')].first) {failed =true; break;}
      }
    }
    if (failed) continue;

    cout << guess << "\n";
    
  }
}

int main()
{
  solve();
}