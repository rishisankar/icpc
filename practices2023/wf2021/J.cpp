
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

vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	queue<int> q; // use priority_queue for lexic. largest ans.
	rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (int x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}

vector<pii> pars;
vector<ll> lens;
vi type;
ll m;
int n,q,N;

ll query(int x, ll k) {
    if (k > lens[x]) return -1;
    if (type[x] == 2 || type[x] == 3) {
        // gen by split
        if (type[x] == 2) {
            return query(pars[x].F, 2*k - 1);
        } else {
            return query(pars[x].F, 2*k);
        }
    }
    else if (type[x] == 1) {
        int LL = lens[pars[x].F], LR = lens[pars[x].S];
        if (k <= 2 * min(LL,LR)) {
            if (k&1) {
                return query(pars[x].F, (k+1)/2);
            } else {
                return query(pars[x].S, k/2);
            }
        } else {
            int bp = (LL > LR ? pars[x].F : pars[x].S);
            return query(bp, k - min(LL,LR));
        }
    }
    else if (type[x] == 4) {
        return k;
    }

    return -1;
}

void solve() {
    cin >> m >> n >> q;
    N = 3*n+10;
    type.resize(N); // 0 = nonexistent, 1 = merge, 2 = left split, 3 = right split, 4 = root
    pars.resize(N);
    lens.resize(N);
    vector<vi> gr(N);
    type[0] = 4;
    lens[0] = m;
    rep(i,0,n) {
        char c; cin >> c;
        int A,B,C; cin >> A >> B >> C;
        --A;--B;--C;
        if (c == 'S') {
            pars[B].F = A;
            pars[C].F = A;
            gr[A].pb(B);
            gr[A].pb(C);
            type[B] = 2;
            type[C] = 3;
        } else {
            pars[C].F = A;
            pars[C].S = B;
            gr[A].pb(C);
            gr[B].pb(C);
            type[C] = 1;
        }
    }
    vi ts = topoSort(gr);
    for (int i : ts) {
        if (i == 0) continue;
        if (type[i] == 0) continue;
        if (type[i] == 1) {
            lens[i] = lens[pars[i].F] + lens[pars[i].S];
        } else if (type[i] == 2) {
            lens[i] = (lens[pars[i].F] + 1)/2;
        } else if (type[i] == 3) {
            lens[i] = (lens[pars[i].F])/2;
        }
    }
    dbg(type);
    dbg(lens);
    rep(i,0,q) {
        int a; ll b; cin >> a >> b; -- a;
        ll res = query(a,b);
        if (res == -1) {
            cout << "none\n";
        } else {
            cout << res << '\n';
        }
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
}
