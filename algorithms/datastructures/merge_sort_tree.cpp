/*
Merge sort tree (described in cp-algs for segtree)
https://cp-algorithms.com/data_structures/segment_tree.html

Stores elements in a multiset for each segments
Can also use a vector (but then you cant do updates)
Usecases: if answer can be found by combining answer from all segments
  - note: you can't merge the segments together for a query

Query/update is log^2 time, building is nlog^2n time (but nlogn space)
(if you use a vector, logn query and nlogn build; but no update)

Examples:
- find the smallest number greater or equal to a specified number (answer is smallest answer from all the segments)

Never been tested but compiles :)
*/

struct Tree {
    typedef int D;
    typedef pair<D, multiset<D>> T;
    D unit = INT_MIN;

    vector<T> t; int n;
	Tree(vector<T>& v, int n) : t(4*n+1), n(n) {
        build(v, 1, 0, n-1);
    }

    // associative function
    D combineD(const D& d1, const D& d2) {
        return d1+d2;
    }

    T combineT(const T& t1, const T& t2) {
        T nw;
        nw.F = combineD(t1.F, t2.F);
        for (D d : t1.S) nw.S.insert(d);
        for (D d : t2.S) nw.S.insert(d);
        return nw;
    }

    void build(vector<T>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combineT(t[v*2], t[v*2+1]);
        }
    }

    /* query on inclusive range [l,r] */
    D query(int l, int r) {
        return query_(1, 0, n-1, l, r);
    }
    D query_(int v, int tl, int tr, int l, int r) {
        if (l > r) return unit;
        if (l == tl && r == tr) {
            return t[v].F;
        }
        int tm = (tl + tr) / 2;
        return combineD(query_(v*2, tl, tm, l, min(r, tm)),
            query_(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    /* update pos (0-indexed) */
    void update(int pos, D new_val) {
        D old = query(pos,pos);
        return update_(1,0,n-1,pos,new_val,old);
    }
    void update_(int v, int tl, int tr, int pos, D new_val, D old) {
        t[v].S.erase(t[v].S.find(old));
        t[v].S.insert(new_val);
        if (tl == tr) {
            t[v].F = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update_(v*2, tl, tm, pos, new_val, old);
            else
                update_(v*2+1, tm+1, tr, pos, new_val, old);
            t[v].F = combineD(t[v*2].F, t[v*2+1].F);
        }
    }
};