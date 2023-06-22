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

struct custom_hash { // https://codeforces.com/blog/entry/62393
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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
aabacab
(man[0]): {0, 1, 0, 0, 0, 0, 0, 0}
(man[1]): {0, 0, 1, 0, 2, 0, 0}


query [l,r]


ODD CASE:
m = (l+r)/2
X=man[1][i]+1

sum(i=l..r) min(X, i-l+1, r-i+1)
= sum(i=l...m) min(X, i-l+1) + sum(i=m+1..r) min(X, r-i+1)
= sum(i=l..m) i + sum(i=l...m) min(X-i, -l+1) 
  - sum(i=m+1..r) i + sum(i=m+1..r) min(X+i, r+1)


EVEN CASE:

query[0,3]: aaba (interested in man[0][1,2,3])
X=man[0][i]
m = (same)
sum(i=l+1..r) min(X, i-l, r+1-i)
= sum(i=l+1...m) min(X, i-l) + sum(i=m+1..r) min(X,r+1-i)
= sum(i=l+1...m) i + sum(i=l+1..m) min(X-i,-l) 
  - sum(i=m+1..r) i + sum(i=m+1..r) min(X+i, r+1)
*/

struct Node {
    using T = pair<ll,ll>;
	Node *l = 0, *r = 0;
	int lo, hi; // segment size
    T val = {0,0};
    T comb(T v1, T v2) { return mp(v1.F+v2.F,v1.S+v2.S); } 
    void init() { // initialize to all 0s, could modify to use vector
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
            l->init(); r->init();
			val = comb(l->val, r->val);
		}
		else val = {0,0};
    }
	Node(int lo, int hi) : lo(lo), hi(hi) {} // call init after
	T query(int L, int R) { // return pair {sum, # set entries}
		if (R <= lo || hi <= L) return {0,0};
		if (L <= lo && hi <= R) return val;
		return comb(l->query(L, R),r->query(L, R));
	}
	Node* set(int pos, ll x) {
		if (lo <= pos && pos < hi) {
            Node* newNode = new Node(lo, hi);
            if (pos == lo && pos+1 == hi) {
                newNode->val = {x,1};
            } else {
                newNode->l = l->set(pos,x);
                newNode->r = r->set(pos,x);
                newNode->val = comb(newNode->l->val,newNode->r->val);
            }
            return newNode;
		} else return this;
	}
};

struct MinTree {
    int n;
    vector<Node*> pst;
    map<ll,int> tree_ind; // ind of first segtree with that value set
    MinTree(vector<ll>& v) : n(sz(v)) {
        pst.pb(new Node(0,n)); pst[0]->init();
        map<ll,vi> ord; rep(i,0,n) ord[v[i]].pb(i);
        int ct = 0;
        for (auto& p : ord) {
            tree_ind[p.F] = ++ct;
            Node* tree = pst[ct-1];
            for (int i : p.S) tree = tree->set(i, p.F);
            pst.pb(tree);
        }
        tree_ind[LLONG_MAX] = ++ct;
    }
    // exclusive range, query sum of min(vi, C) over all vi in range
    ll query(int L, int R, ll C) {
        pair<ll,ll> seg_qry = pst[tree_ind.upper_bound(C)->S-1]->query(L,R);
        return seg_qry.F + C * (R-L-seg_qry.S);
    }
};

array<vi, 2> manacher(const string& s) {
	int n = sz(s);
	array<vi,2> p = {vi(n+1), vi(n)};
	rep(z,0,2) for (int i=0,l=0,r=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}

// return sum(i=l..r) i
inline ll smi(int l, int r) { if (r<l)return 0; return (r-l+1)*(ll)(l+r)/2; }

void run() {
    string s; cin >> s;
    int n = sz(s);
    array<vi,2> man = manacher(s);
    VLL Xmi(n), Xpi(n), Ymi(n), Ypi(n);
    rep(i,0,n) {
        Xmi[i] = man[1][i]+1-i;
        Xpi[i] = man[1][i]+1+i;
        Ymi[i] = man[0][i]-i;
        Ypi[i] = man[0][i]+i;
    }
    MinTree tmi(Xmi), tpi(Xpi), rmi(Ymi), rpi(Ypi);
    int q; cin >> q;
    rep(_,0,q) {
        int l,r; cin >> l >> r; --l; --r;
        int m = (l+r)/2;
        ll odd_ans = smi(l,m) + tmi.query(l,m+1,-l+1) - smi(m+1,r) + tpi.query(m+1,r+1,r+1);
        ll even_ans = smi(l+1,m)+rmi.query(l+1,m+1,-l)-smi(m+1,r)+rpi.query(m+1,r+1,r+1);
        print(odd_ans + even_ans);
    }
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