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

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi;
    ll val = 0; // store sum
    pll data = {0,0};
	Node(int lo,int hi):lo(lo),hi(hi){}
	Node(VLL& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = l->val + r->val;
		}
		else val = v[lo];
	}

	ll query(int L, int R) {
		if (R <= lo || hi <= L) return 0LL;
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}

	void addPoly(int L, int R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            data.F += (lo-L);
            data.S += 1;
            val += ((ll)lo-L)*(hi-lo); // first part
			val += ((ll)hi-lo) * ((ll)hi-lo+1) / 2LL; // second part
		}
		else {
			push(), l->addPoly(L, R), r->addPoly(L, R);
			val = l->val + r->val;
		}
	}

    void upd(pll d) {
        // update lazy propagation
        val += d.F*((ll)hi-lo); // first part
		val += d.S*((ll)hi-lo) * ((ll)hi-lo+1) / 2LL; // second part
        data.F += d.F;
        data.S += d.S;
    }

	void push() {
        int mid = lo + (hi - lo)/2;
		if (!l) {
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (data.S > 0) {
			l->upd(data);
            r->upd({data.S*(mid-lo)+data.F, data.S});
            data = {0,0};
        }
	}
};

void run() {
    int n, q; cin >> n >> q;
    VLL v(n); INP(v,n);
    Node tree(v, 0, n);
    rep(i,0,q) {
        int t; cin >> t;
        if (t == 1) {
            int a,b; cin >> a >> b; --a; --b;
            tree.addPoly(a,b+1);
        } else {
            int a,b; cin >> a >> b; --a; --b;
            print(tree.query(a,b+1));
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