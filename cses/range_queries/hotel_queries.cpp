#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) 
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) 
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; 
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;


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
    void update(int pos, int new_val) {
        return update_(1,0,n-1,pos,new_val);
    }
    void update_(int v, int tl, int tr, int pos, int new_val) {
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

    /* return index of first elt >= k (-1 if none) */
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

};

void run() {
    int n,m; cin >> n >> m;
    VI v(n); INP(v,n);
    VLL v2(m); INP(v2,m);
    Tree st(v,n);
    rep(i,0,m) {
        ll g = v2[i];
        int idx = st.findFirstGreater(g);
        cout << (idx+1) << ' ';
        if (idx != -1) {
            v[idx] -= g;
            st.update(idx,v[idx]);
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}