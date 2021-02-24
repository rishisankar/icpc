// example: math/musicalchairs.cpp

class SegmentTree {
public:

    SegmentTree(int n_, vector<int>& arr) {
        n = n_;
        t.resize(4*n);
        build(arr, 1, 0, n-1);
    }

    /** inclusive sum of elements in [l, r] */
    int sum(int l, int r) {
        return sum_helper(1, 0, n-1, l, r);
    }

    /** 0-indexed updated */
    void update(int pos, int new_val) {
        return update_helper(1, 0, n-1, pos, new_val);
    }

private:
    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
        }
    }
    
    int sum_helper(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return sum_helper(v*2, tl, tm, l, min(r, tm))
            + sum_helper(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    void update_helper(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update_helper(v*2, tl, tm, pos, new_val);
            else
                update_helper(v*2+1, tm+1, tr, pos, new_val);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    int n;
    vector<int> t;
};