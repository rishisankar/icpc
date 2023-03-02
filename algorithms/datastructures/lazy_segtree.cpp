/*
Lazy segtree (can work implicitly? not tested) ; based on kactl
Example: cses/range_queries/range_updates_and_sums
Initialization: Node tree(v, 0, n);
O(nlogn) build, O(logn) set/add/query
*/

struct Node {
    typedef ll T;
    const T unit = 0;
    const T inf = LLONG_MIN; // value that is not present in segtree
    T f(T a, T b) { return a+b; } // associative
    T rangeF(T x) {
        // represents value from setting everything on range to x
        // or value to add to segment value when adding x on range
        return x*(hi-lo); // for addition ()
        // return x; // for max/min
    }
	Node *l = 0, *r = 0;
	int lo, hi;
    T mset = inf, madd = 0, val = unit;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of unit
	Node(vector<T>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = f(l->val, r->val);
		}
		else val = v[lo];
	}
  /* query on range [L,R) */
	T query(int L, int R) {
		if (R <= lo || hi <= L) return unit;
		if (L <= lo && hi <= R) return val;
		push();
		return f(l->query(L, R), r->query(L, R));
	}
  /* set on range [L,R) */
	void set(int L, int R, T x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = x, val = rangeF(x), madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = f(l->val, r->val);
		}
	}
  /* add on range [L,R) */
	void add(int L, int R, T x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += rangeF(x);
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = f(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};
