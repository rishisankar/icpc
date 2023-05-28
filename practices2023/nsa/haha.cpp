#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair
typedef long double ld;
#define double ld
typedef __int128_t ll;
#define int ll
typedef pair<int, int> pii;
typedef vector<int> vi;

    unordered_map<string,int> vm;
    vector<string> vmr;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
	return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
	os << '{';
	string sep;
	for (const auto &x: v) os << sep << x, sep = ", ";
	return os << '}';
}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
	cerr << ' ' << H; dbg_out(T...);
}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;


  vector<vector<double>> A;
  vector<double> b;
  vector<vector<ll>> AA;
  vector<ll> bb;


bool check(vector<ll> &x)
{
  for (ll l : x) {
    if (l > INT_MAX || l < INT_MIN) return false;
  }
  int m=sz(AA);
  int n=sz(AA[0]);
  vector<ll> res(m,0);
  rep(i,0,m)
  {
    rep(j,0,n)
    res[i]+=AA[i][j]*x[j];
  }
  bool ok=true;
  rep(i,0,m) ok=ok&&(res[i]<=bb[i]);
  return ok;
}

vector<ll> vals;
int num_vars;

void dfs(int idx,vector<ll> &v, vector<vector<ll>> &sol)
{
  if(idx==num_vars)
  {
    if(check(v))
    sol.pb(v);
    return;
  }

  trav(a,vals)
  {
    v.pb(a);
    dfs(idx+1,v,sol);
    if(sz(sol)!=0) return;
    v.pop_back();
  }
}


void vector_print(){


    // now try a bucnh og values
    vector<ll> v;
    vector<vector<ll>> sol;
    dfs(0,v,sol);

    if(sz(sol)==0)
    {
      cout << "No solution\n";
      exit(0);
    }
    

    for (int i = 0; i<num_vars; i++){
        cout << vmr[i] << " := " << (long long)sol[0][i] << "\n";
    }
    exit(0);
}

int32_t main()
{
  signal(SIGSEGV, [](int32_t) { _Exit(0); });
     /*
    -------------------------------------------------------------------
            Get Input
    -------------------------------------------------------------------
    */

    string t;
    int n;

    rep(i,0,25) vals.pb(i);
    rep(i,1,25) vals.pb(-i);
    vals.pb(INT_MAX);
    vals.pb(INT_MAX-1);
    vals.pb(INT_MIN);
    vals.pb(INT_MIN+1);



    while (cin >> t) {
      if (t == "V") {
        string v; cin >> v;
        vm[v] = sz(vm);
        vmr.pb(v);
      } else if (t == "R") {
        n = sz(vm);
        vector<ll> Av;
        rep(i,0,n) {
          long long x; cin >> x;
          Av.pb(x);
        }
        string op; cin >> op;
        if (op == ">=") {
          rep(i,0,n) Av[i]*=-1;
        }
        long long bx; cin >> bx;
        if (op == ">=") bx*=-1;
        bb.pb(bx);
        AA.pb(Av);
      }
    }
    num_vars=n;
    rep(i,0,n) {
      bb.pb(INT_MAX);
      vector<ll> Av;
      rep(j,0,n) {
        if (j == i) Av.pb(1); else Av.pb(0);
      }
      AA.pb(Av);
    }
    rep(i,0,n) {
      bb.pb(-(ll)INT_MIN);
      vector<ll> Av;
      rep(j,0,n) {
        if (j == i) Av.pb(-1); else Av.pb(0);
      }
      AA.pb(Av);
    }

    int m = sz(AA);

    A=vector<vector<double>>(m,vector<double>(n));
    b=vector<double>(m);
    rep(i,0,m) rep(j,0,n) A[i][j]=AA[i][j];
    rep(i,0,m) b[i]=bb[i];
    vector_print();
}