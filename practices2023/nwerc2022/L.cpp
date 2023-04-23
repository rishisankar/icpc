#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

void run() {
    int g,l; cin >> g >> l; --g;
    vector<pii> amts(26, {0, l+1}); // for each char, [a,b)
    VVB valid(l, VB(26, true)); // for each position, which characters are valid
    rep(i,0,g) {
        string s1, s2; cin >> s1 >> s2;
        vi numl(26,0); // number of times each letter appears in s1
        vi numb(26,0); // number of times each letter is given black verdict in s1
        rep(j,0,l) {
            int c = s1[j] - 'a';
            numl[c]++;
            if (s2[j] == 'G') {
                rep(k,0,26) {
                    if (k == c) continue;
                    valid[j][k] = false;
                }
            } else if (s2[j] == 'Y') {
                valid[j][c] = false;
            } else {
                valid[j][c] = false;
                numb[c]++;
            }
        }
        rep(c,0,26) {
            if (numb[c] != 0) {
                amts[c] = {numl[c]-numb[c], numl[c]-numb[c]+1};
            } else {
                amts[c].F = max(amts[c].F, numl[c]);
            }
        }
    }
    vi nm(l, 26);
    int curc = 0;
    rep(i,0,26) {
        rep(j,0,amts[i].F) {
            nm[curc++] = i;
        }
    }
    vi btoa(l, -1);
    vector<vi> G(l);
    vi unb(l,26);
    rep(i,0,l) {
        rep(c,0,26) {
            if (valid[i][c] && amts[c].S == l+1) {
                unb[i] = c;
                break;
            }
        }
    }
    rep(i,0,l) {
        rep(j,0,l) {
            if (nm[i] != 26) {
                if (valid[j][nm[i]]) G[i].pb(j);
            } else {
                if (unb[j] != 26) G[i].pb(j);
            }
        }
    }
    hopcroftKarp(G, btoa);
    string s(l, ' ');
    rep(i,0,l) {
        int c = nm[btoa[i]];
        if (c != 26) {
            s[i] = (char)('a'+c);
        } else {
            s[i] = (char)('a'+unb[i]);
        }
    }
    print(s);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}