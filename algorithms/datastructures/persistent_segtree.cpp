/*
Persistent segtree configured to do range sum / set at point.
Initialize: Node* tree = new Node(v,0,n);
Each call to set returns a new tree (adds O(logn) nodes)
Example: cses/range_queries/range_queries_and_copies
*/
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
