// broken idk

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

// maybe a combination approach works? for each self contained segment, try both and see if it works
/*
Fail cases for n=9 (on both approaches) - bf on all finished
{2, 9, 7, 1, 4, 6, 3, 8, 5}
{5, 2, 4, 1, 9, 7, 3, 8, 6}
{5, 9, 2, 4, 1, 7, 3, 8, 6}
{8, 2, 4, 1, 9, 6, 3, 7, 5}
{8, 2, 7, 4, 1, 5, 3, 9, 6}

maybe store all possible top values (allow going on either stack)






{6,5,4,3,2,1}
problem with greedy: run into problems when you put u somewhere, then v opposite, 
  then u gets cleared and would be better if v was where u was

==> if you assume u will get cleared, then irrelevant which stack?
==> if you assume u won't get cleared, greedy approach is valid
==> option: either merge w top opts, or match to smallest opt


54,5
6         54,4


543,5
6         543,43

approach: either store all terms monotonically in same stack, or break off at some point
- store all terms in stack for as long as possible
- when larger # comes in, forced to break off
    => option 1: push larger # to other stack
    => option2 : move everything smaller than # to other stack, then put # on first stack
        => is this always optimal? stuff on first stack is going to clear out first which will eventually yield empty stack! so i think yes
- when next # comes in
    => larger than both stack heads: fail
    => smaller than both stack heads: add to smaller one (ex 3 5 2 4)
        - optimality idk
    => in btwn both heads: only have one option :)

next idea: if you know you won't fail before clear from either order, put on larger (so that after you clear its as high as possible!)
- does this maintain optimal state? if so then we can just assume optimal state to know top of two stacks prior.. sus
- can you check if you will fail or not

    suppose stack state is [a,b]
    we're considering range where eventually b will get cleared
        - assume everything in range is larger than b (otherwise it will get cleared before)
            - this is alr sus..
        - when you add larger things, they must go on top of a
            - when you add smaller thing x, you now want to test validity of range where x gets cleared (subset range)
        - put everything larger in other stack (make sure montonic decreasing in order)
        - everything smaller is in a subset active range (can we do something with that)?
        - 
*/

inline int gt(stack<int>& s) {
    if (s.empty()) return -1;
    else return s.top();
}

// greedy approach 1: maintain monotonicity, pop if posisble, always push to smaller top if can do both
bool run3(vi v) {
    int n = sz(v);
    stack<int> s1, s2;
    int cur = 1;
    for (int i : v) {
        while (gt(s1) == cur || gt(s2) == cur) {
            if (gt(s1) == cur) s1.pop(); else s2.pop();
            ++cur;
        }
        if (s1.empty()) {
            if (s2.empty() || s2.top() > i) s2.push(i);
            else s1.push(i);
        } else if (s2.empty()) {
            if (s1.top() > i) s1.push(i); else s2.push(i);
        } else {
            if (s1.top() > s2.top()) {
                if (s2.top() > i) s2.push(i);
                else if (s1.top() > i) s1.push(i);
                else return false;
            } else {
                if (s1.top() > i) s1.push(i);
                else if (s2.top() > i) s2.push(i);
                else return false;
            }
        }
    }
    return true;
}


bool run2(vi v) {
    int n = sz(v);
    vi tm(n);
    rep(i,0,n) {
        v[i]--;
        tm[v[i]] = i;
    }
    vector<pair<bool,int>> ops; // true = regular, false = clear
    int cur = 0;
    VB vis(n,0);
    rep(i,0,n) {
        ops.pb({1,v[i]});
        vis[v[i]] = 1;
        while (cur < n && vis[cur]) {
            ops.pb({0,cur++});
        }
    }
    vi stack_id(n,-1);
    stack<int> s1,s2;
    // dbg(ops);
    assert(sz(ops)==2*n);
    s1.push(-1); s2.push(-1); // -1 for empty
    for (int i = sz(ops)-1; i >= 0; --i) {
        auto p = ops[i];
        if (p.F) {
            // regular --> pop from stack!
            assert(stack_id[p.S] != -1);
            if (stack_id[p.S] == 1) s1.pop();
            else s2.pop();
        } else {
            int t = tm[p.S];
            if (s1.top() < s2.top()) {
                // s2 is later
                if (t > s2.top()) {
                    s2.push(t);
                    stack_id[p.S] = 2;
                } else if (t > s1.top()) {
                    s1.push(t);
                    stack_id[p.S] = 1;
                } else {
                    return false;
                }
            } else {
                // s1 is later
                if (t > s1.top()) {
                    s1.push(t);
                    stack_id[p.S] = 1;
                } else if (t > s2.top()) {
                    s2.push(t);
                    stack_id[p.S] = 2;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

bool chk(vi& v) {
    int n = sz(v);
    rep(i,0,(1<<n)) {
        int cur = 1;
        stack<int> s1,s2;
        rep(j,0,n) {
            // dbg("adding", v[j]);
            if ((i >> j) & 1) s1.push(v[j]);
            else s2.push(v[j]);
            while (gt(s1) == cur || gt(s2) == cur) {
                if (gt(s1) == cur) {
                    // dbg("pop s1", cur);
                    s1.pop();
                } else {
                    // dbg("pop s2", cur);
                    s2.pop();
                }
                ++cur;
            }
        }
        if (s1.empty() && s2.empty()) {
            // dbg(v, bitset<N>(i).to_string());
            return true;
        }
    }
    // dbg(v, "fail");
    return false;
}

void run() {
    int n; cin >> n;
    vi v(n);
    iota(all(v),1);
    do {
        // dbg(v);
        bool b1 = chk(v);
        bool b2 = run2(v);
        bool b3 = run3(v);
        // dbg(v,b1,b2,b3);
        if (!(b1 == (b2||b3))) {
            dbg(v);
            dbg(b1,b2,b3);
        }
        // assert(b1==(b2||b3));
    } while (next_permutation(all(v)));
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