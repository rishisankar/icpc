// https://open.kattis.com/contests/izu6n6/problems/vivoparc
// works on N <= 100, unbounded # of edges
// maybe faster to use adjacency list if bounded # of edges
// currently does 4 coloring, need to modify to support k coloring
// bf with backtracking (apparently runs p fast)

VVB adj;
int n;

bool val(int v, int c, vi& coloring) {
    rep(i,0,n) {
        if (adj[v][i] && c == coloring[i]) return false;
    }
    return true;
}

bool gc(vi& coloring, int v) {
    if (v == n) return true;
    for (int c = 1; c <= 4; ++c) {
        if (!val(v, c, coloring)) continue;
        coloring[v] = c;
        if (gc(coloring,v+1)) return true;
        coloring[v] = 0;
    }
    return false;
}

void run() {
    cin >> n;
    adj.resize(n, VB(n));
    string s;
    while (cin >> s) {
        int x,y;
        string a = "";
        rep(i,0,sz(s)) {
            if (s[i] == '-') {
                x = stoll(a);
                a = "";
            } else a += s[i];
        }
        y = stoll(a);
        --x; --y;
        adj[x][y] = adj[y][x] = 1;
    }
    vi coloring(n,0);
    coloring[0] = 1;
    bool b = gc(coloring,1);
    assert(b);
    rep(i,0,n) print(i+1, coloring[i]);
}
