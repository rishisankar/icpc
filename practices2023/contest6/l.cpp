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
typedef pair<long long, long long> pii;
typedef vector<long long> vi;

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

const int inf = 1e9;
struct Node {
  Node *l = 0, *r = 0;
  int lo,hi,mset = inf, madd=0,val=-inf;
  Node(int lo, int hi) : lo(lo),hi(hi){}
  Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
    if (lo+1 < hi) {
      int mid = lo+(hi-lo)/2;
      l = new Node(v,lo,mid); r = new Node(v,mid,hi);
      val = max(l->val, r->val);
    } else val = v[lo];
  }
  int query(int L, int R) {
    if (R <= lo || hi <= L) return -inf;
    if (L <= lo && hi <= R) return val;
    push();
    return max(l->query(L,R), r->query(L,R));
  }
  void set(int L, int R, int x) {
    if (R <= lo || hi <= L) return;
    if (L <= lo && hi <= R) mset = val=x, madd=0;
    else {
      push(), l->set(L,R,x), r->set(L,R,x);
      val=max(l->val,r->val);
    }
  }
  void add(int L, int R, int x) {
    if (R <= lo || hi <= L) return;
    if (L <= lo && hi <= R) {
      if (mset != inf) mset += x;
      else madd += x;
      val += x;
    } else {
      push(), l->add(L,R,x), r->add(L,R,x);
      val = max(l->val, r->val);
    }
  }
  void push() {
    if (!l) {
      int mid = lo + (hi-lo)/2;
      l = new Node(lo, mid); r = new Node(mid,hi);
    }
    if (mset != inf) {
      l->set(lo,hi,mset), r->set(lo,hi,mset), mset=inf;
    } else if (madd) l->add(lo,hi,madd), r->add(lo,hi,madd), madd=0;
  }
};

template <bool VALS_EDGES> struct HLD {
  int N, tim = 0;
  vector<vector<int>> adj;
  vi par, siz, depth, rt, pos;
  Node *tree;
  HLD(vector<vector<int>> adj_,vi cap) : N(sz(adj_)), adj(adj_), par(N,-1), siz(N,1), depth(N), rt(N), pos(N), tree(new Node(cap,0,N)) {
    dfsSz(0);
    dfsHld(0);
    tree->set(0,N,0);
  }
  void dfsSz(int v){
    if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
    for (int& u : adj[v]) {
      par[u] = v, depth[u] = depth[v] + 1;
      dfsSz(u);
      siz[v] += siz[u];
      if (siz[u] > siz[adj[v][0]]) swap(u,adj[v][0]);
    }
  }
  void dfsHld(int v) {
    pos[v] = tim++;
    for (int u : adj[v]) {
      rt[u] = (u == adj[v][0] ? rt[v] : u);
      dfsHld(u);
    }
  }
  template <class B> void process(int u, int v, B op) {
    for (; rt[u] != rt[v]; v = par[rt[v]]) {
      if (depth[rt[u]] > depth[rt[v]]) swap(u,v);
      op(pos[rt[v]], pos[v] +1);
    }
    if (depth[u] > depth[v]) swap(u,v);
    op(pos[u] + VALS_EDGES, pos[v]+1);
  }
  void modifyPath(int u, int v, int val) {
    process(u,v,[&](int l, int r) {tree->add(l,r,val);});
  }
  int queryPath(int u, int v) {
    int res = -1e9;
    process(u,v,[&](int l, int r) {res = max(res, tree->query(l,r));});
    return res;
  }
  int querySubtree(int v) {
    return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
  }
};

void accum(int x, vector<vector<int>> &dadj, vi &v, vi &val, ll xtra)
{
  val[x]=v[x]+xtra;
  trav(a,dadj[x])
  {
    accum(a,dadj,v,val,val[x]);
  }
}


void solve()
{
  int n;
  cin>>n;

  vi par(n,-1), cap(n,-1), v(n,-1), val(n,0);
  vector<vector<int>> dadj(n), adj(n);
  rep(i,1,n)
  {
    cin>>par[i];
    par[i]--;
    dadj[par[i]].pb(i);
    adj[par[i]].pb(i);
    adj[i].pb(par[i]);
  }



  rep(i,0,n)
  {
    cin>>cap[i];
    cap[i]=-cap[i];
    // hld.modifyPath(i,i,-cap[i]);
  }

  cap.pb(0);

  HLD<false> hld(adj,cap);

  rep(i,0,n)
  cin>>v[i];

  // accum(0,dadj,v,val,0);
  val=v;

  // dbg(v,val);

  vector<pii> ordering;
  rep(i,0,n) ordering.pb({val[i],i});
  sort(all(ordering));
  reverse(all(ordering));

  // dbg(ordering);

  vi ans;
  ll tot=0;

  rep(i,0,n)
  // dbg(i,hld.queryPath(i,i));

  rep(j,0,n)
  {
    int i=ordering[j].S;
    // dbg(i,hld.queryPath(i,0));
    if(hld.queryPath(i,0)<0)
    {
      ans.pb(i);
      tot+=val[i];
      hld.modifyPath(i,0,1);
    }
    // dbg(i,hld.queryPath(i,0));
  }

  cout<<tot<<"\n";
  sort(all(ans));
  cout<<sz(ans)<<" ";
  trav(a,ans)
  cout<<a+1<<" ";
  cout<<"\n";
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}