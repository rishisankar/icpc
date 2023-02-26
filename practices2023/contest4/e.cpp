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


struct Node {
  string s;
  Node* next;
};

void solve()
{
  string s;
  getline(cin, s);
  int r = 1;
  rep(i,0,s.size()) {
    if (s[i] == ' ') ++r;
  }
  dbg(r);
  int n;
  cin >> n;
  vector<string> v(n);

  vector<Node*> vn;
  rep(i,0,n) {
    cin >> v[i];
    Node* x = new Node;
    x->next = nullptr;
    x->s = v[i];
    vn.push_back(x);
    if (i > 0) vn[i-1]->next = x;
  }
  vn[n-1]->next = vn[0];
  Node* head = vn[0];
  Node* prev = vn[n-1];

  vector<vector<string>> t(2);
  int cur = 0;
  while (true) {
    rep(i,0,r-1) {
      prev = head;
      head = head->next;
    }
    t[cur].push_back(head->s);
    if (prev == head) break;
    prev->next = head->next;
    head = head->next;
    cur = (cur+1)%2;
  }

  cout << t[0].size() << '\n';
  rep(i,0,t[0].size()) {
    cout << t[0][i] << '\n';
  }
  cout << t[1].size() << '\n';
  rep(i,0,t[1].size()) {
    cout << t[1][i] << '\n';
  }

}

int main()
{
  
  solve(); 
}