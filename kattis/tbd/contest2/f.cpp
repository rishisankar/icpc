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
const int MOD2 = 1e9+9;

vector<vector<string>> v;
vector<ll> pow43(1000005,1);
vector<ll> pow31(1000005,1);

void fail() {
  cout << "NONE\n";
  exit(0);
}

void check2() {
  int n=sz(v[0][1]);
  if(sz(v[1][0])!=n) fail();
  if(n==1) fail();
  
  vi h1(n,0),h2(n,0);
  ll cur=0;
  rep(i,0,n)
  {
    h1[i]=(cur*43+(v[0][1][n-i-1]-'a'+1))%MOD;
    cur=h1[i];
  }
  cur=0;
  rep(i,0,n)
  {
    cur=(cur+((v[1][0][i]-'a'+1)*pow43[i]))%MOD;
    h2[i]=cur;
  }
  vi h11(n,0),h22(n,0);
  cur=0;
  rep(i,0,n)
  {
    h11[i]=(cur*31+(v[0][1][n-i-1]-'a'+1))%MOD2;
    cur=h11[i];
  }
  cur=0;
  rep(i,0,n)
  {
    cur=(cur+((v[1][0][i]-'a'+1)*pow31[i]))%MOD2;
    h22[i]=cur;
  }

  vi f1(n,0),f2(n,0);
  cur=0;
  rep(i,0,n)
  {
    f1[i]=(cur*43+(v[1][0][n-i-1]-'a'+1))%MOD;
    cur=f1[i];
  }
  cur=0;
  rep(i,0,n)
  {
    cur=(cur+((v[0][1][i]-'a'+1)*pow43[i]))%MOD;
    f2[i]=cur;
  }
  vi f11(n,0),f22(n,0);
  cur=0;
  rep(i,0,n)
  {
    f11[i]=(cur*31+(v[1][0][n-i-1]-'a'+1))%MOD2;
    cur=f11[i];
  }
  cur=0;
  rep(i,0,n)
  {
    cur=(cur+((v[0][1][i]-'a'+1)*pow31[i]))%MOD2;
    f22[i]=cur;
  }
  vi ans;
  rep(i,0,n-1)
  if(h1[i]==h2[i] && h11[i]==h22[i] && f1[n-i-2]==f2[n-i-2] && f11[n-i-2]==f22[n-i-2]) ans.pb(i+1);

  int m=sz(ans);

  if(m==0) fail();
  if(m>1)
  {
    cout<<"MANY\n";
    exit(0);
  }


  cout<<"UNIQUE\n";

  rep(i,ans[0],n)
  cout<<v[1][0][i];
  cout<<endl;
  rep(i,0,ans[0])
  cout<<v[1][0][i];
  cout<<endl;


}

void solve() {
  int n; cin >> n;
  vector<int> len(n);
  v.assign(n, vector<string>(n));
  rep(i,0,n) {
    rep(j,0,n) {
      cin >> v[i][j];
    }
  }
  if (n == 2) {
    check2();
    return;
  }

  for (int i = 2; i < n; ++i) {
    int tlen = v[0][1].size() + v[0][i].size() + v[1][i].size();
    if (tlen % 2 != 0) fail();
    tlen /= 2;
    len[i] = tlen - v[0][1].size();
    if (i == 2) {
      len[0] = tlen - v[1][2].size();
      len[1] = tlen - v[0][2].size();
    }
  }

  dbg(len);

  rep(i,0,n) {
    if (len[i] <= 0) fail();
  }

  vector<string> sol(n, "");
  if (v[0][1].size() <= len[0]) fail();
  sol[0] = v[0][1].substr(0, len[0]);
  rep(i,1,n) {
    if (v[i][0].size() <= len[i]) fail();
    sol[i] = v[i][0].substr(0, len[i]);
  }

  dbg(sol);

  rep(i,0,n) {
    rep(j,0,n) {
      if (i==j) continue;
      if (v[i][j].size() != len[i] + len[j]) {dbg("f1",i,j);fail();}
      rep(k, 0, v[i][j].size()) {
        if (k < len[i]) {
          if (v[i][j][k] != sol[i][k]) {dbg("f2",i,j);fail();}
        } else {
          if (v[i][j][k] != sol[j][k-len[i]]){dbg("f3",i,j);fail();}
        }
      }
    }
  }

  cout << "UNIQUE\n";
  rep(i,0,n) {
    cout << sol[i] << '\n';
  }

}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  rep(i,1,1000005)
  pow43[i]=(43*pow43[i-1])%MOD;
  rep(i,1,1000005)
  pow31[i]=(31*pow31[i-1])%MOD2;
  solve();
}