/*
https://cp-algorithms.com/data_structures/segment_tree.html
Use kactl instead for most stuff
This is somewhat less efficient but allows top-down query fns
*/

struct Tree {
    typedef int T;
    T unit = INT_MIN;
    vector<T> t; int n;
	Tree(vector<T>& v, int n) : t(4*n+1), n(n) {
        build(v, 1, 0, n-1);
    }

    // associative function
    T combine(const T& t1, const T& t2) {
        return max(t1,t2);
    }

    void build(vector<T>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    /* query on inclusive range [l,r] */
    T query(int l, int r) {
        return query_(1, 0, n-1, l, r);
    }
    T query_(int v, int tl, int tr, int l, int r) {
        if (l > r) return unit;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return combine(query_(v*2, tl, tm, l, min(r, tm)),
            query_(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    /* update pos (0-indexed) */
    void update(int pos, T new_val) {
        return update_(1,0,n-1,pos,new_val);
    }
    void update_(int v, int tl, int tr, int pos, T new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update_(v*2, tl, tm, pos, new_val);
            else
                update_(v*2+1, tm+1, tr, pos, new_val);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    /* ################ */
    // optional stuff...
    /* ################ */

    /*
    Return index of first elt >= k (-1 if none)
    (requires max segtree!)
    Example: cses/range_queries/hotel_queries
    */
    int findFirstGreater(T k) {
        return ffg_(1,0,n-1,k);
    }
    int ffg_(int v, int tl, int tr, T k) {
        if (t[v] < k) return -1;
        if (tl == tr) return tl;
        int tm = (tl + tr) / 2;
        if (t[v*2] >= k) {
            return ffg_(v*2, tl, tm, k);
        } else {
            return ffg_(v*2+1, tm+1, tr, k);
        }
    }

    /*
    Find index of kth 1 (k is 1-indexed!)
    Requires sum segtree containing n 0s and 1s
    Example: cses/range_queries/list_removals
    */
    int indexOfKth(T k) {
        return iok_(1,0,n-1,k);
    }
    int iok_(int v, int tl, int tr, T k) {
        if (t[v] < k) return -1;
        if (tl == tr) return tl;
        int tm = (tl + tr) / 2;
        if (t[v*2] >= k) {
            return iok_(v*2, tl, tm, k);
        } else {
            return iok_(v*2+1, tm+1, tr, k-t[v*2]);
        }
    }

};

/*
Max subarray segment tree (see cp-algs)
(mx in query equals max subarray on query region)
ex: cf/edu-144/D
*/
struct D {
    D() : sum(0), pref(0), suff(0), mx(0) {}
    ll sum;
    ll pref;
    ll suff;
    ll mx;  
};

struct Tree {
	typedef D T;
	const T unit;
	T f(T a, T b) { 
        T ans;
        ans.sum = a.sum+b.sum;
        ans.pref = max(a.pref, a.sum+b.pref);
        ans.suff = max(a.suff+b.sum, b.suff);
        ans.mx = max(max(a.mx, b.mx), a.suff + b.pref);
        return ans;
    }
	vector<T> s; int n;
	Tree(int n = 0) : s(2*n, unit), n(n) {}
	void update(int pos, ll val) {
        T x; x.sum = val; x.pref = x.suff = x.mx = max(0LL,val);
		for (s[pos += n] = x; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
