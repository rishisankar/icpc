/*
Source: https://github.com/kth-competitive-programming/kactl/blob/f6a97d9e5766c90ee71a97a90cd3faf6cff0ca72/content/data-structures/Treap.h
Time: log(n).

Maybe recopy lol

Applications: (see implicit treap...)
- Insert at position
- Get at position
- Range sum / min / max
- Cyclic shift
- Reverse
*/


struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
	Node(int val) : val(val), y(rand()) {}
	void recalc();
};

int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }

template<class F> void each(Node* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
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

Node* merge(Node* l, Node* r) {
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

Node* ins(Node* t, Node* n, int pos) {
	auto pa = split(t, pos);
	return merge(merge(pa.first, n), pa.second);
}
/*
Example usage:

int main() {
	Node* tree = new Node(5);

	// insert at pos
	tree = ins(tree, new Node(2), 0);
	tree = ins(tree, new Node(15), 0);
	tree = ins(tree, new Node(12), 1);
	tree = ins(tree, new Node(5), 2);

	each(tree, [](int val) {
		cout << val << '\n';
	});
	// prints 15,12,5,2,5
}
*/