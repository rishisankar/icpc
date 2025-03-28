/*
Combination of kactl + cp-alg templates (tested on cses)
Examples:
- cses/advanced/cut_and_paste (move only)
- cses/advanced/substring_reversals2 (reverse only)
- cses/advanced/reversals_and_sums2 (reversals + sums)

Supports ints, range sums, range reverse, move subarray
*/


struct Node {
	Node *l = 0, *r = 0;
	int y, c = 1;
    bool rev = false;
    // to change type: only required change is next two lines + build func
    // note that you can also store array indices and have the array have arbitrary indices    
    int val; ll s = 0;
	Node(int val) : val(val), y(rand()) {}
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
ll sm(Node* n) { return n ? n->s : 0; }
void Node::recalc() {
    c = cnt(l) + cnt(r) + 1;
    s = sm(l) + sm(r) + val;
}

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
        if (pa.first) pa.first->recalc();
		return {pa.first, n};
	} else {
		auto pa = split(n->r, k - cnt(n->l) - 1); // and just "k"
		n->r = pa.first;
		n->recalc();
        if (pa.second) pa.second->recalc();
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
        r->recalc();
        l->recalc();
		return l;
	} else {
		r->l = merge(l, r->l);
        l->recalc();
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
Node* build(vector<int> v) {
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

/*
Range sum in interval [a,b)
*/
ll rangeSum(Node*& t, int a, int b) {
    Node *l,*r;
    tie(l,r) = split(t, b);
    Node *ll, *rr;
    tie(ll,rr) = split(l, a);
    long long ans = sm(rr);
    l = merge(ll, rr);
    t = merge(l, r);
    return ans;
}
