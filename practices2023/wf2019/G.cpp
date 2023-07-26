
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
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

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef NIKIL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(_VA_ARGS_)
#else
#define dbg(...)
#endif

const int MOD = 1000000000 + 7;

struct AhoCorasick {
	enum {alpha = 26, first = 'A'};
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], dptr=-1, start = -1, end = -1, nmatches = 0,dp=0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(1, -1) {
		rep(i,0,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i,0,alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	// nearest word you can reach by following suffix links
	int get_dptr(int v){
		if(N[v].dptr!=-1) return N[v].dptr;
		if(v==0) return N[v].dptr=0;
		int f_ptr=N[v].back;
		return N[v].dptr=(N[f_ptr].end!=-1)?f_ptr:get_dptr(f_ptr);
	}
};

void solve()
{
  int n,k;
  cin>>n>>k;

  vector<vector<pair<char,int>>> g(n+1);
  rep(i,1,n+1)
  {
    char ch; int p;
    cin>>ch>>p;
    g[p].pb(mp(ch,i));
  }

  // 0 is dummy root

  map<string,int> ans_idx;
  set<string> ss;
  vector<string> v,orig;
  rep(i,0,k)
  {
    string s;
    cin>>s;
    reverse(all(s));
    if(ss.find(s)==ss.end())
    {
      ss.insert(s);
      ans_idx[s]=sz(v);
      v.pb(s);
    }
    orig.pb(s);
  }

  AhoCorasick AC=AhoCorasick(v);
  int NN=sz(AC.N);

  queue<pii> q; // {tree node, AC node}
  q.push(mp(0,0));

  // also build graph of the word nodes
  vector<int> acg(NN);
  vi indeg(NN,0);
  rep(i,0,NN)
  {
    int x=AC.get_dptr(i);
    indeg[x]++;
    acg[i]=x;
  }

  // dbg(acg);

  while(!q.empty())
  {
    pii x=q.front();
    q.pop();

    int tn=x.F;
    int acn=x.S;

    AC.N[acn].dp++;

    trav(a,g[tn])
    {
      int ntn,nacn;
      ntn=a.S;
      nacn=AC.N[acn].next[a.F - 'A'];
      q.push(mp(ntn,nacn));
    }
  }

  // accumulate answer
  queue<int> qq;
  rep(i,0,NN)
  if(indeg[i]==0)
  qq.push(i);

  vi ans(sz(v),0);

  while(!qq.empty())
  {
    int x=qq.front();
    qq.pop();

    // dbg(x,AC.N[x].end);

    if(AC.N[x].end!=-1)
    ans[AC.N[x].end]=AC.N[x].dp;

    // only one child, but meh

    {
      int a=acg[x];
      // dbg(a,x,AC.N[a].dp,AC.N[x].dp);
      AC.N[a].dp+=AC.N[x].dp;
      indeg[a]--;
      if(indeg[a]==0)
      qq.push(a);
    }
  }

  trav(a,orig)
  cout<<ans[ans_idx[a]]<<"\n";

}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll t=1;

  rep(i,0,t)
    solve();
}