/*
2D fenwick tree (easier to use segment trees for 1D)
O(nm log nm) to build, O(log(n)log(m)) per query
Can do submatrix sum queries with modifications
Can extend to higher dimensions (see cp-algs)
Example: cses/range_queries/forest_queries2
*/

struct FenwickTree2D {
    typedef ll T;
    const T unit = 0;
    vector<vector<T>> bit;
    int n, m;

    FenwickTree2D(int n, int m) : n(n), m(m) {
        bit.resize(n, vector<T>(m,unit));
    }

    // sum 0<=i<=x, 0<=j<=y of v[i][j]
    T sum(int x, int y) {
        if (x<0||y<0)return 0;
        T ret = unit;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    /* sum of submatrix (assuming 0<=x1<=x2<n, 0<=y1<=y2<m) */
    T submatrixSum(int x1, int y1, int x2, int y2) {
        return sum(x2,y2) - sum(x1-1,y2) - sum(x2,y1-1) + sum(x1-1,y1-1);
    }

    // v[x][y]+=delta
    void add(int x, int y, T delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};
