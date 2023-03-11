// works for both monster game 1 and monster game 2
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

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

/*
Implicit Li Chao tree for lines (y=mx+b represented by pll {m.b})
Custom impl, based on:
- https://cp-algorithms.com/geometry/convex_hull_trick.html
- https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html
Operations:
  insert(pll line, int l, int r)  // insert line in range [a,b]
  query(int x) // query min y at point x in [a,b]
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

/*
dp[i]: cost of completing assuming u kill monster i
dp[i] = min{j>i} (f[i]*s[j] + dp[j])

use li chao tree
*/

void run() {
    int n; cin >> n;
    ll x; cin >> x;
    VLL s(n); INP(s,n);
    VLL f(n); INP(f,n);
    Node* lct = new Node(1, 1000000);
    VLL dp(n);
    dp[n-1] = 0;
    if (n > 1) {
        dp[n-2] = f[n-2]*s[n-1];
        lct->insert({s[n-2], dp[n-2]}, 1, 1000000);
    }
    for (int i = n-3; i >= 0; --i) {
        dp[i] = lct->query(f[i]);
        dp[i] = min(dp[i], f[i]*s[n-1]);
        lct->insert({s[i],dp[i]}, 1, 1000000);
    }
    rep(i,0,n) {
        dp[i] += x * s[i];
    }
    print(mine(dp));
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