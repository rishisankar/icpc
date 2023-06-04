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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const bool TESTING = false;

vi test(vi& guess) {
    cout << "test";
    for (int i : guess) cout << ' ' << (i+1);
    cout << endl;
    string s; cin >> s;
    vi ans;
    rep(i,0,sz(s)) {
        if (s[i] == '0') ans.pb(0);
        else if (s[i] == '1') ans.pb(1);
        else ans.pb(-1);
    }
    return ans;
}

void answer(vi& ans) {
    cout << "answer ";
    for (int i : ans) cout << i;
    cout << endl;
}

pair<VPII, int> pairup(vi& nodes) {
    shuffle(all(nodes), rng);
    VPII ans;
    rep(i,0,sz(nodes)/2) ans.pb({nodes[2*i], nodes[2*i+1]});
    return {ans, (sz(nodes)&1 ? nodes.back() : -1)};
}

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

void run() {
    int n; cin >> n;
    vector<int> know(n,2);
    vector<pair<vi,vi>> pairs;
    vi unknown(n); iota(all(unknown), 0);
    VVI leftover;
    UF dsu(n);
    vi pmap(n,-1);
    while (sz(unknown) > 0) {
        vi nw;
        auto [p, l] = pairup(unknown);
        vi ans(n,-1);
        if (sz(p) > 0) {
            vi guess(n,-1);
            for (auto pr : p) {
                guess[pr.F] = pr.S;
                guess[pr.S] = pr.F;
            }
            ans = test(guess);
        }
        for (auto pr : p) {
            if (ans[pr.F] == 1 && ans[pr.S] == 1) {
                dsu.join(pr.F, pr.S);
                nw.pb(dsu.find(pr.F));
            } else {
                pmap[pr.F] = pmap[pr.S] = sz(pairs);
                pairs.pb({{pr.F},{pr.S}});
            }
        }
        if (l != -1) {
            vi addl;
            rep(i,0,n) if (dsu.find(i) == l) addl.pb(i);
            leftover.pb(addl);
        }
        swap(unknown, nw);
    }
    rep(i,0,n) {
        int z = dsu.find(i), pz = pmap[z];
        if (z==i) continue;
        if (pz != -1) {
            if (pairs[pz].F[0] == z) pairs[pz].F.pb(i);
            else pairs[pz].S.pb(i);
        }
    }
    dbg(pairs);
    dbg(leftover);
    unordered_set<int> good;
    for (int x : leftover.back()) good.insert(x);
    leftover.pop_back();
    VVI qp;
    for (auto& pr : leftover) qp.pb(pr);
    for (auto& pr : pairs) { qp.pb(pr.F); qp.pb(pr.S); }
    sort(all(qp), [](vi& v1, vi& v2) { return v1.size() > v2.size(); });
    int p = 0;
    while (p < sz(qp)) {
        vi guess(n,-1), ind(n,-1);
        for (int x : good) {
            if (p>=sz(qp)) break;
            guess[x] = qp[p][0];
            ind[x] = p++;
        }
        vi ng;
        vi ans = test(guess);
        for (int x : good) {
            if (ind[x] != -1) {
                if (ans[x] == 1) {
                    ng.pb(ind[x]);
                }
            }
        }
        for (int i : ng) {
            for (int x : qp[i]) {
                good.insert(x);
            }
        }
    }
    vi result(n,0);
    for (int x : good) result[x] = 1;
    answer(result);
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