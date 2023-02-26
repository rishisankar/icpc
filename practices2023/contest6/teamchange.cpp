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

struct Edge {
  int to, rev;
  ll c, oc;
  ll flow() { return max(oc - c, 0LL); } // if you need flows
};

struct Dinic {
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

/*
A=true, B=false

Left side of graph:
A->B
B->A
?(A->B)
?(B->A)

Right side of graph:
A->A
B->B
?(A->A)
?(B->B)
*/

void solve() {
  int n, r; cin >> n >> r;
  string s1,s2; cin >> s1 >> s2;
  vector<bool> orig(n);

  unordered_map<int, int> gl, gr; // map graph node -> actual index
  unordered_map<int, int> lrm, rrm; // reverse: actual index -> graph node

  rep(i,0,n) {
    orig[i] = (s1[i] == 'A');
  }
  rep(i,0,n) {
    if (s2[i] == '?' || s2[i] != s1[i]) {
      // want to change...
      lrm[i] = gl.size();
      gl[gl.size()] = i;
    }
    if (s2[i] == '?' || s2[i] == s1[i]) {
      // dont want to change...
      rrm[i] = gr.size();
      gr[gr.size()] = i;
    }
  }

  int L = gl.size();
  int R = gr.size();
  dbg(L,R);
  int N = L+R+2;
  // nodes 0..{L-1} for left nodes, nodes L..{L+R-1} for right, nodes L+R, L+R+1 for s/t
  Dinic d(N);

  // add edge btwn nodes for a qm
  rep(i,0,n) {
    if (s2[i] == '?') {
      d.addEdge(lrm[i],L+rrm[i],1);
    }
  }
  // add nodes from source
  rep(i,0,L) {
    d.addEdge(L+R, i, 1);
  }
  // add nodes to sink
  rep(i,0,R) {
    d.addEdge(L+i,L+R+1, 1);
  }

  // process each rivalry!
  rep(i,0,r) {
    int a,b; cin >> a >> b;
    --a; --b;
    if (s2[a] == '?' && s2[b] == '?') {
      // two edges to add
      d.addEdge(lrm[a],L+rrm[b],1);
      d.addEdge(lrm[b],L+rrm[a],1);
    } else if (s2[a] == '?') {
      if (s1[b] == s2[b]) {
        // b on right side
        d.addEdge(lrm[a],L+rrm[b],1);
      } else {
        d.addEdge(lrm[b],L+rrm[a],1);
      }
    } else if (s2[b] == '?') {
      if (s1[a] == s2[a]) {
        // a on right side
        d.addEdge(lrm[b],L+rrm[a],1);
      } else {
        d.addEdge(lrm[a],L+rrm[b],1);
      }
    } else {
      if ((s1[a] == s2[a]) && (s1[b] != s2[b])) {
        // b on left, a on right
        d.addEdge(lrm[b],L+rrm[a],1);
      } else if ((s1[a] != s2[a]) && (s1[b] == s2[b])) {
        // a on left, b on right
        d.addEdge(lrm[a],L+rrm[b],1);
      }
    }
  }

  ll res = d.calc(L+R,L+R+1);
  dbg(res);

  // for (Edge e : d.adj[0]) {
  //   dbg(e.to, e.flow());
  // }
  // for (Edge e : d.adj[2]) {
  //   dbg(e.to, e.flow());
  // }

  // next construct new graph to figure out max ind set
  vector<vector<int>> adj(L+R);
  unordered_set<int> unmatched;
  rep(i,0,L) {
    bool matched = false;
    for (Edge e : d.adj[i]) {
      if (e.to == L+R) continue;
      if (e.flow() == 0) {
        adj[i].pb(e.to);
      } else {
        dbg(i,e.to);
        matched = true;
        adj[e.to].pb(i);
      }
    }
    if (!matched) unmatched.insert(i);
  }

  dbg(adj);

  // run dfs
  unordered_set<int> visited;
  stack<int> st;
  for (int x : unmatched) {
    st.push(x);
    visited.insert(x);
  }
  while (!st.empty()) {
    int t = st.top();
    st.pop();
    for (int x : adj[t]) {
      if (visited.count(x)) continue;
      st.push(x);
      visited.insert(x);
    }
  }
  
  // maxIS = visited stuff on left + unvisited stuff on right
  unordered_set<int> maxIS;
  rep(i,0,L) {
    if (visited.count(i)) maxIS.insert(i);
  }
  for (int i = L; i < L+R; ++i) {
    if (!visited.count(i)) maxIS.insert(i);
  }
  
  for (int x : maxIS) dbg(x, gl[x-L]);

  vector<char> ans(n, 'X');
  for (int i : maxIS) {
    if (i < L) {
      // picked left node --> swap team
      ans[gl[i]] = (s1[gl[i]] == 'A' ? 'B' : 'A');
    } else {
      int j = i-L;
      ans[gr[j]] = s1[gr[j]];
    }
  }

  // dbg(ans);
  for (char c : ans) cout << c;
  cout << '\n';

}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}