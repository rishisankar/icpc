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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

bool run4(vi v) {
    int n = sz(v);
    rep(i,0,n) v[i]--; // make 0-indexed
    int cur = 0;
    VB vis(n,0);
    vector<pair<bool,int>> ops;
    rep(i,0,n) {
        ops.pb({1,v[i]});
        vis[v[i]] = 1;
        while (cur < n && vis[cur]) {
            ops.pb({0,cur++});
        }
    }
    VPII ranges(n);
    vector<int> rmqVals(2*n);
    rep(i,0,2*n) {
        // populate ranges
        if (ops[i].F) ranges[ops[i].S].F = i;
        else ranges[ops[i].S].S = i;
        // populate rmq vector (can optimize)
        rmqVals[i] = ops[i].S;
    }
    RMQ rmq(rmqVals);
    VB is1(n); // is assigned to stack 1?
    stack<int> s1,s2;
    s1.push(n); s2.push(n+1);
    rep(i,0,2*n) {
        if (ops[i].F) {
            // push operation
            int t = ops[i].S;
            if (s1.top() > s2.top()) {
                if (s2.top() > t) {
                    if (ranges[t].F+1 == ranges[t].S) {
                        s1.push(t);
                        is1[t] = true;
                    } else {
                        int K = rmq.query(ranges[t].F+1, ranges[t].S);
                        if (s2.top() > K) {
                            s1.push(t);
                            is1[t] = true;
                        } else {
                            s2.push(t);
                            is1[t] = false;
                        }
                    }
                } else if (s1.top() > t) {
                    s1.push(t);
                    is1[t] = true;
                } else {
                    return false;
                }
            } else {
                if (s1.top() > t) {
                    if (ranges[t].F+1 == ranges[t].S) {
                        s1.push(t);
                        is1[t] = true;
                    } else {
                        int K = rmq.query(ranges[t].F+1, ranges[t].S);
                        if (s1.top() > K) {
                            s2.push(t);
                            is1[t] = false;
                        } else {
                            s1.push(t);
                            is1[t] = true;
                        }
                    }
                } else if (s2.top() > t) {
                    s2.push(t);
                    is1[t] = false;
                } else {
                    return false;
                }
            }
        } else {
            // clear operation
            if (is1[ops[i].S]) s1.pop(); else s2.pop();
        }
    }
    return true;
}


// complement set
inline int compzl(VVI& adj, UF& dsu, int c) {
    if (sz(adj[c]) > 0) return dsu.find(adj[c][0]);
    else return -1;
}

bool rundsu(vi v) {
    int n = sz(v);
    rep(i,0,n) v[i]--; // make 0-indexed
    int cur = 0;
    VB vis(n,0);
    vector<pair<bool,int>> ops;
    rep(i,0,n) {
        ops.pb({1,v[i]});
        vis[v[i]] = 1;
        while (cur < n && vis[cur]) {
            ops.pb({0,cur++});
        }
    }
    VPII ranges(n);
    vector<int> rmqVals(2*n);
    rep(i,0,2*n) {
        // populate ranges
        if (ops[i].F) ranges[ops[i].S].F = i;
        else ranges[ops[i].S].S = i;
        // populate rmq vector (can optimize)
        rmqVals[i] = ops[i].S;
    }
    RMQ rmq(rmqVals);
    VB is1(n); // is assigned to stack 1?
    VB assgn(n);
    // constraint graph
    VVI adj(n);
    rep(i,0,n) {
        // if (ranges[i].F+1 < ranges[i].S) {
        //     int K = rmq.query(ranges[i].F+1, ranges[i].S);
        //     if (K > i) {
        //         adj[i].pb(K);
        //         adj[K].pb(i);
        //     }
        // }
        int rf = ranges[i].F+1;
        while (rf < ranges[i].S) {
            int K = rmq.query(rf, ranges[i].S);
            if (K > i) {
                adj[i].pb(K);
                adj[K].pb(i);
                rf = ranges[K].F+1;
            } else break;
        }
    }
    UF dsu(n);
    rep(i,0,n) {
        for (int x : adj[i]) dsu.join(adj[i][0], x);
    }

    stack<int> s1,s2;
    s1.push(n); s2.push(n+1);
    rep(i,0,2*n) {
        if (ops[i].F) {
            // push operation
            int t = ops[i].S;
            if (s1.top() > s2.top()) {
                if (s2.top() > t) {
                    if (is1[dsu.find(t)]) {
                        s1.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = false;
                        assgn[t] = true;
                    } else {
                        s2.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = true;
                        assgn[t] = false;
                    }
                } else if (s1.top() > t) {
                    s1.push(t);
                    is1[dsu.find(t)] = true;
                    int cm = compzl(adj,dsu,dsu.find(t));
                    if (cm != -1) is1[cm] = false;
                    assgn[t] = true;
                } else {
                    return false;
                }
            } else {
                if (s1.top() > t) {
                    if (is1[dsu.find(t)]) {
                        s1.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = false;
                        assgn[t] = true;
                    } else {
                        s2.push(t);
                        int cm = compzl(adj,dsu,dsu.find(t));
                        if (cm != -1) is1[cm] = true;
                        assgn[t] = false;
                    }
                } else if (s2.top() > t) {
                    s2.push(t);
                    is1[dsu.find(t)] = false;
                    int cm = compzl(adj,dsu,dsu.find(t));
                    if (cm != -1) is1[cm] = true;
                    assgn[t] = false;
                } else {
                    return false;
                }
            }
        } else {
            // clear operation
            if (assgn[ops[i].S]) s1.pop(); else s2.pop();
        }
    }
    return true;
}

void run() {
    int n; cin >> n;
    vi v(n);
    iota(all(v),1);
    do {
        // dbg(v);
        bool b1 = chk(v);
        // bool b2 = run2(v);
        // bool b3 = run3(v);
        // bool b4 = run4(v);
        bool b4 = rundsu(v);
        // dbg(v,b1,b2,b3);
        if (!(b1 == b4)) {
        // if (!(b1 == (b2||b3))) {
            dbg(v);
            dbg(b1,b4);
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