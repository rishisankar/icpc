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
Approach 2: use some sort of interval dp/store approach

needed: (retcon)
- for each push, loc of next smallest push (can do w monotonic stack)
- test if range is montonically decreasing (can do w rmq, segtree, etc)
- for each #, number of smaller #s required before clear
    => if 1, base case!

need all direct subranges for each range (no)
*/


vi v; // input permutation
vector<pair<bool,int>> ops; // true = regular, false = clear
vector<pii> ranges; // for each value, store {index of push, index of clear}
vi largestUncleared; // after each operation, what is the smallest uncleared value (n+1 if none)

VB onStack1; // answer (built up)

/*
Check how to place id to optimize after push(id)....clear(id)
key idea: should only need to call twice per id at most
- why?
    each call to test returns a single state.
    assume that the root call to test is called twice (per the two options)
        sequential calls called twice since test condenses output to 1 result
        recursive calls will be called many times? might be a problem...
            suppose start w [s t] --> options [s i], [t i] (with s > t > i)
                IF theres a value k>i before j, only input state is [k i] which is good
                if not, need to try [t i] and [s i] ==> [t j] [s j] [j i]
    maybe instead, figure out smallest value required to succeed? this might avoid future passes too
        in particular, assume input is [x,i] for arbitrary x > i
            possible return values:
                [x,i] indicating that you will be able to get [x,i] back
        idk sus
    OR within range of [pi, ci] let K be first elt larger than i with pK in the range. !!!!! smarter approach lol
        - if t > K, it is optimal to use [t i]
        - if K > t, it is optimal to use [s i] (might be impossible, particularly if K > s also).
        - if K doesn't exist, it is optimal to use [t i] since it is irrelevant whether you use [s i] or [t i]
            => when you clear i, state will be [s t] again guaranteed
        how to compute K for each i quickly?
            option 1: can be done in nlogn using segtree (probably good enough) actually idk
            option 2: technically, only care about largest value in this range since we need to be able to
                support it. monotonicity can be figured out as we go !!

Return vals:
- pair returns new state
- int returns -1 if impossible to clear, 0 if better to push to smaller, 1 if better to push to larger.

make sure to memoize! ie store map {initial, id} -> {result -1..1} for eventual simulation down the line

how to handle a clear if you only store piis instead of full stacks?
    (assume inside interval pj, cj)
    we MUST have one elt >= j, the other is presumably less than j and will be the cleared value
    we then need to know the next smallest # already pushed by a certain index
        small-large merging and generating set during each test is one way (kinda gross)
        easier approach: precompute for each index in ops the current smallest non-cleared # !!
*/
pair<pii,int> test(pii initial, int id) {
    // first try pushing to smaller and simulate

}

void run() {
    int n; cin >> n;
    v.resize(n); INP(v,n);
    rep(i,0,n) v[i]--; // make 0-indexed
    onStack1.resize(n);
    ranges.resize(n);
    largestUncleared.resize(2*n);
    int cur = 0;
    VB vis(n,0);
    rep(i,0,n) {
        ops.pb({1,v[i]});
        vis[v[i]] = 1;
        while (cur < n && vis[cur]) {
            ops.pb({0,cur++});
        }
    }
    priority_queue<int> largestUnclearedStk;
    largestUnclearedStk.push(n+1);
    rep(i,0,2*n) {
        // populate ranges
        if (ops[i].F) ranges[ops[i].S].F = i;
        else ranges[ops[i].S].S = i;
        // populate largest uncleared
    }

    pii state = {n+1, n+2}; // initial state (both #s larger than anything that will ever appear)
    stack<int> s1; s1.push(n);
    stack<int> s2; s2.push(n+1);
    // go through operations and solve
    cur = 0;
    while (cur < 2*n) {
        auto op = ops[cur];
        if (op.F) {
            // push operation
            if (s1.top() > s2.top()) {
                if (s2.top() > op.S) {
                    // can put on either
                    int res = test({s1.top(),s2.top()}, op.S);
                    if (res == -1) {
                        print("IMPOSSIBLE");
                        return;
                    } else if (res == 0) {
                        s2.push(op.S);
                    } else {
                        s1.push(op.S);
                    }
                } else if (s1.top() > op.S) {
                    // no choice.. must put on s1
                    s1.push(op.S);
                    onStack1[op.S] = true;
                } else {
                    // impossible - no stack to push to
                    print("IMPOSSIBLE");
                    return;
                }
            } else {
                // todo
            }
        } else {
            // clear operation is easy: only one option
            if (onStack1[op.S]) s1.pop();
            else s2.pop();
        }
    }
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