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

struct Node {
	Node *l = 0, *r = 0;
	int y, c = 1;
    bool rev = false;
    // to change type: only required change is next two lines + build func
    // note that you can also store array indices and have the array have arbitrary indices    
    char val;
	Node(char val) : val(val), y(rand()) {}
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

void push(Node* n) {
    if (n && n->rev) {
        n->rev = false;
        swap(n->l, n->r);
        if (n->l) n->l->rev ^= true;
        if (n->r) n->r->rev ^= true;
    }
}

/* 
Run a function for each value in treap in order
O(nlogn)
*/
template<class F> void each(Node* n, F f) {
    push(n);
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

/*
Implicit treap split: first k elements in first elt of pair
*/
pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
    push(n);
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto pa = split(n->l, k);
		n->l = pa.second;
		n->recalc();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
		n->r = pa.first;
		n->recalc();
		return {n, pa.second};
	}
}

/*
Merge two treaps in O(logn)
*/
Node* merge(Node* l, Node* r) {
    push(l); push(r);
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		l->recalc();
		return l;
	} else {
		r->l = merge(l, r->l);
		r->recalc();
		return r;
	}
}

/*
Reverse nodes [a,b) in O(logn)
*/
Node* rev(Node* t, int a, int b) {
    Node *t1, *t2, *t3;
    tie(t1,t2) = split(t, a);
    tie(t2,t3) = split(t2, b-a);
    t2->rev ^= true;
    t = merge(t1,t2);
    t = merge(t,t3);
    return t;
}

/*
insert a treap at a position (0 indexed)
can be a single node or a treap!
O(logn)
*/
Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}

/* O(nlogn) build */
Node* build(vector<char> v) {
    if (v.size() == 0) return nullptr;
    Node* head = new Node(v[0]);
    rep(i,1,v.size()) {
        Node* nw = new Node(v[i]);
        head = merge(head, nw);
    }
    return head;
}

// Move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}



void run() {
    int n,m; cin >> n >> m;
    string s; cin >> s;
    vector<char> v(s.size()); rep(i,0,s.size()) v[i]=s[i];
    Node* treap = build(v);
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        --a;
        treap = rev(treap, a, b);
    }
    each(treap, [&](char i) {
        cout << i;
    });
    cout << "\n";
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