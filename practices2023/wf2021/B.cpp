
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

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C, int r) : time(sz(C)), rmq((dfs(C,r,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	ll dist(int a, int b, vector<ll> &depth) {
        return depth[a] + depth[b] - 2*depth[lca(a,b)];
    }
};

int n,q;
vector<ll> queryAnswers;

vector<vi> adj;
vector<vector<pair<int,ll>>> adjW;

ll sumEdges;

void btDFS(int t, int p, vi &par, vector<vector<pair<int,ll>>> &chdW, vector<ll> &depth) {
    par[t] = p;
    for (auto x : adjW[t]) {
        if (x.F == p) continue;
        chdW[t].pb(x);
        depth[x.F] = depth[t] + x.S;
        btDFS(x.F, t, par, chdW, depth);
    }
}

void optDFS(int t, int p, vi &par, vector<vector<pair<int,ll>>> &chdW, vector<vector<pair<int,ll>>> &optW) {
    for (auto x : chdW[t]) {
        optDFS(x.F, t, par, chdW, optW);
        ll amtSaved = x.S;
        if (sz(optW[x.F]) > 0) amtSaved += optW[x.F][0].S;
        optW[t].pb({x.F, amtSaved});
    }
    sort(all(optW[t]), [](auto p1, auto p2) {
        return p1.S > p2.S; // biggest savings first
    });
}

void prefDFS(int t, int p, vi &par, vector<vector<pair<int,ll>>> &chdW, vector<vector<pair<int,ll>>> &optW, vector<ll> &pref) {
    pref[t] = LLONG_MAX; if (sz(optW[t]) >= 2) pref[t] = optW[t][0].S - optW[t][1].S;
    if (p != -1) {
        pref[t] = min(pref[t], pref[p]);
    }
    for (auto ch : chdW[t]) {
        prefDFS(ch.F, t, par, chdW, optW, pref);
    }
}

void run(int r, vector<pair<pii,int>> &queries) {
    LCA lca(adj, r);
    vi par(n);
    vector<ll> depth(n);
    vector<vector<pair<int,ll>>> chdW(n);
    btDFS(r, -1, par, chdW, depth);
    vector<vector<pair<int,ll>>> optW(n);
    optDFS(r, -1, par, chdW, optW);

    ll bestSol = 2*sumEdges - optW[r][0].S;
    dbg(r+1, bestSol);
    dbg(optW[r]);

    // want for each node the amount u can save by not hitting that path
    vector<ll> pref(n);
    prefDFS(r,-1,par,chdW,optW,pref);

    for (auto query : queries) {
        int K = query.F.F, T = query.F.S;
        int L = lca.lca(K,T);
        if (L == K) {
            // case 4
            queryAnswers[query.S] = bestSol;
            continue;
        }
        if (L == T) {
            // case 5
            queryAnswers[query.S] = -1;
            continue;
        }
        if (lca.lca(K, optW[r][0].F) == r) {
            // case 6
            queryAnswers[query.S] = bestSol;
            continue;
        }
        if (lca.lca(K, optW[L][0].F) == L) {
            // case 7
            queryAnswers[query.S] = bestSol;
            continue;
        }

        ll optWK = 0; if (sz(optW[L]) > 0) optWK = optW[L][0].S;
        if (optWK + lca.dist(L,r,depth) != optW[r][0].S) {
            queryAnswers[query.S] = bestSol;
            continue;
        }

        // case 8
        ll opt1 = bestSol + 2 * lca.dist(L, K, depth);
        // ll opt2 = bestSol + optW[L][0].S - optW[L][1].S;
        ll opt2 = pref[L] == LLONG_MAX ? LLONG_MAX : bestSol + pref[L];
        queryAnswers[query.S] = min(opt1, opt2);
    }
}

void solve() {
    cin >> n >> q;
    queryAnswers.resize(q);
    vector<vector<pair<pii, int>>> queriesByStart(n);

    adj.resize(n);
    adjW.resize(n);

    sumEdges = 0;

    rep(i,0,n-1) {
        int a,b; ll w;
        cin >> a >> b >> w; --a; --b;
        adj[a].pb(b);
        adj[b].pb(a);
        adjW[a].pb({b,w});
        adjW[b].pb({a,w});
        sumEdges += w;
    }

    rep(i,0,q) {
        int a,b,c; cin >> a >> b >> c;
        --a; --b; --c;
        queriesByStart[a].pb({{b,c},i});
    }

    rep(i,0,n) {
        run(i, queriesByStart[i]);
    }

    for (ll ans : queryAnswers) {
        if (ans == -1) {
            cout << "impossible\n";
        } else {
            cout << ans << '\n';
        }
    }

}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
