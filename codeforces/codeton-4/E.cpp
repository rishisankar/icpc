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

/*
if not connected,fail! or if no 0s ig

multisource bfs from each 0: (label each bfs id 0..k)
- each bfs has pq of unvisited nodes
- each unvisited node has list of 

use dsu to store connected group
if you ever fail, give up on that group


*/

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

typedef priority_queue<pii, vector<pii>, greater<pii>> PQ;

void mge(PQ& p1, PQ& p2) {
    if (p1.size() < p2.size()) {
        swap(p1,p2);
    }
    while (!p2.empty()) {
        p1.push(p2.top()); p2.pop();
    }
}

void run() {
    int n,m; cin >> n >> m;
    VLL vals(n);
    vector<int> stf;
    rep(i,0,n) {
        cin >> vals[i];
        if (vals[i] == 0) stf.pb(i);
    }
    dbg(vals);
    vector<PQ> pqs(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b; --a; --b;
        pqs[a].push({vals[b],b});
        pqs[b].push({vals[a],a});
    }
    UF dsu(n);
    for (int t : stf) {
        while (true) {
            int id = dsu.find(t);
            // get rid of anything already merged
            while (!pqs[id].empty() && dsu.find(pqs[id].top().S) == id) pqs[id].pop();
            if (pqs[id].empty()) break; // can't do anything more
            if (pqs[id].top().F <= dsu.size(id)) {
                // can merge
                pii p = pqs[id].top();
                pqs[id].pop(); // doing merge, don't need this edge anymore
                int oid = dsu.find(p.S);
                mge(pqs[id], pqs[oid]); //pqs[id] now stores merged result
                dsu.join(id,oid);
                int nid = dsu.find(id);
                if (nid != id) swap(pqs[nid], pqs[id]);
            } else {
                break;
            }
        }
    }
    if (dsu.size(0) != n) {
        print("NO");
    } else print("YES");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}