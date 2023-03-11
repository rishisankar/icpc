/*
Implicit Li Chao tree for lines (y=mx+b represented by pll {m.b})
Custom impl, based on:
- https://cp-algorithms.com/geometry/convex_hull_trick.html
- https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html
Operations:
  insert(pll line, int l, int r)  // insert line in range [a,b]
  query(int x) // query min y at point x in [a,b]

Example: cses/advanced/monster_game
(note: not fully tested (hasn't been tested on non-positive a/b))
*/
struct Node {
    const pll DEF = {LLONG_MAX, LLONG_MAX};
    int a, b;
    pll val;
    Node *l_ptr, *r_ptr;
    Node(int a, int b) : a(a), b(b), l_ptr(0), r_ptr(0), val(DEF) {}
    ll f(pll line, int x) { return (val == DEF) ? LLONG_MAX : line.F*x+line.S; }
    void insert(pll line, int l, int r) {
        if (r < l) return;
        if (r < a || l > b) return; // not in this segment
        if (l <= a && b <= r) {
            // segment part of the interval
            if (val == DEF) {
                val = line;
                return;
            }
            if (a == b) {
                // single point
                if (f(line,a) < f(val,a)) val = line;
                return;
            }
            if (f(line,a) <= f(val,a) && f(line,b) <= f(val,b)) {
                // new line is better everywhere, get rid of old
                val = line;
                return;
            }
            if (f(line,a) >= f(val,a) && f(line,b) >= f(val,b)) {
                // old line is better everywhere, do nothing
                return;
            }
            // from here, guaranteed that one is better at end, other better at beginning
            if (val.F > line.F) swap(val,line); // line now has larger slope
            if (!l_ptr) {
                int mid = (a+b)/2;
                l_ptr = new Node(a,mid); r_ptr = new Node(mid+1, b);
            } 
            int mid = (a+b)/2;
            if (f(val,mid) > f(line,mid)) {
                // new line optimal at mid (and left) => store + upd right
                r_ptr->insert(val, l, r);
                val = line;
            } else {
                // old line optimal at mid (and right) => upd left
                l_ptr->insert(line, l, r);
            }
        } else  {
            if (!l_ptr) {
                int mid = (a+b)/2;
                l_ptr = new Node(a,mid); r_ptr = new Node(mid+1, b);
            } 
            l_ptr->insert(line, l, r);
            r_ptr->insert(line, l, r);
        }
    }
    ll query(int x) {
        if (x < a || x > b) return LLONG_MAX;
        if (a == b) return f(val,x); // can modify to return line
        ll ans1 = f(val,x); // possible line #1
        int mid =  (a+b)/2;
        if (x <= mid && l_ptr) return min(ans1, l_ptr->query(x));
        else if (x > mid && r_ptr) return min(ans1, r_ptr->query(x));
        else return ans1;
    }
};

// ############################################################
// BELOW IMPLEMENTATION PROBABLY BROKEN (NEVER TESTED)

/*
Original implementation (not tested, probably broken) allows queries for x in [0,n) only...
Maybe faster but implicit more general

Li Chao tree for lines (y=mx+b represented by pll {m.b})
Custom impl, based on:
- https://cp-algorithms.com/geometry/convex_hull_trick.html
- https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html
Operations:
  insert(pll line, int l, int r)  // insert line in range [0,n)
  query(int x) // query min y at point x in [0,n)
*/
struct LiChaoTree {
    const pll DEF = {LLONG_MIN,LLONG_MIN};
    int n;
    vector<pll> t;
    LiChaoTree(int n) : n(n), t(4*n, DEF) {}
    ll f(pll line, int x) { return line.F*x+line.S; }
    void insert(pll line, int l, int r, int v=0) {
        if (r <= l) return;
        if (l+1 == r) {
            // single point
            if (f(line,l) < f(t[v],l)) t[v] = line;
            return;
        }
        if (f(line,l) <= f(t[v],l) && f(line,r-1) <= f(t[v],r-1)) {
            // new line is better everywhere, get rid of old
            t[v] = line;
            return;
        }
        if (f(line,l) >= f(t[v],l) && f(line,r-1) >= f(t[v],r-1)) {
            // old line is better everywhere, do nothing
            return;
        }
        // from here, guaranteed that one is better at end, other better at beginning
        if (t[v].F > line.F) swap(t[v],line); // line now has larger slope
        int mid = (l+r)/2;
        if (f(t[v],mid) > f(line,mid)) {
            // new line optimal at mid (and left) => store + upd right
            insert(t[v], mid, r, v*2+2);
            t[v] = line;
        } else {
            // old line optimal at mid (and right) => upd left
            insert(line, l, mid, v*2+1);
        }
    }
    ll query_(int x, int l, int r, int v) {
        if (r <= l || x < l || x >= r) return LLONG_MAX;
        if (l+1 == r) return f(t[v],x); // can modify to return line
        ll ans1 = f(t[v],x); // possible line #1
        int mid =  (l+r)/2;
        if (x < mid) return min(ans1, query_(x,l,mid,v*2+1));
        else return min(ans1, query_(x,mid,r,v*2+2));
    }
    ll query(int x) {
        return query_(x,0,n,0);
    }
};