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

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

// persistent segtree
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi; // segment size
    ll val = 0;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of 0s
	Node(vector<ll>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = l->val + r->val;
		}
		else val = v[lo];
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		return l->query(L, R) + r->query(L, R);
	}
	Node* set(int pos, int x) {
		if (lo <= pos && pos < hi) {
            Node* newNode = new Node(lo, hi);
            if (pos == lo && pos+1 == hi) {
                newNode->l = l;
                newNode->r = r;
                newNode->val = x;
            } else {
                newNode->l = l->set(pos,x);
                newNode->r = r->set(pos,x);
                newNode->val = newNode->l->val + newNode->r->val;
            }
            return newNode;
		} else return this;
	}
};

void run() {
    int n, q; cin >> n >> q;
    VLL v(n); INP(v,n);
    vector<Node*> trees;
    Node* first = new Node(v,0,n);
    trees.pb(first);
    rep(i,0,q) {
        int t; cin >> t;
        if (t == 1) {
            int k,a; ll x;
            cin >> k >> a >> x;
            --k; --a;
            trees[k] = trees[k]->set(a, x);
        } else if (t == 2) {
            int k,a,b; cin >> k >> a >> b; --k;--a;
            print(trees[k]->query(a,b));
        } else {
            int k; cin >> k; --k;
            trees.pb(trees[k]);
        }
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