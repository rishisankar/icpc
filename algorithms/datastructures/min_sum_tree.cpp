/*
Answers queries of sum in range [L,R] of min(vi, C)
(where C changes with the query)

O(logn) query, O(nlogn) space/build time, update not supported

uses persistent segtree and updates value by value (at most n distinct values)
*/


// persistent sum segtree initialized to all 0s, stores #s + set positions
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



/*
testing:

8
1 3 2 -5 9 15 -5 3
6
0 2 5
0 2 2
0 4 1
0 8 30
0 8 -30
0 8 3

should output 4 3 -2 23 -240 5

tester:
void run() {
    int n; cin >> n; VLL v(n); INP(v,n);
    MinTree mt(v);
    int q; cin >> q;
    rep(i,0,q) {
        int a,b; ll c; cin >> a >> b >> c;
        print(mt.query(a,b,c));
    }
}
*/