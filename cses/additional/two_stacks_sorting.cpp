// broken on {2, 6, 4, 1, 5, 3}

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
(v, bitset<6>(i).to_string()): {4, 5, 2, 1, 3, 6} 000001
4 5 2 1 c1 c2 3 c3 c4 c5 6 c6

idea: augment with clear operations (asap) then work in reverse
clear corresponds to pushing to stack
- can place u on top of v if u appears after v in perm
- greedy: 
    1) prefer placing on top of something else than empty stack
    2) if something in both + can place on either, place on the later one

*/

void fail() {
    print("IMPOSSIBLE");
    exit(0);
}

void run() {
    int n; cin >> n;
    vi v(n); INP(v,n);
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
    assert(sz(ops)==2*n);
    dbg(ops);
    s1.push(-1); s2.push(-1); // -1 for empty
    for (int i = sz(ops)-1; i >= 0; --i) {
        auto p = ops[i];
        if (p.F) {
            dbg("reg", p.S, stack_id[p.S]);
            // regular --> pop from stack!
            assert(stack_id[p.S] != -1);
            if (stack_id[p.S] == 1) s1.pop();
            else s2.pop();
            dbg(s1.top(),s2.top());
        } else {
            int t = tm[p.S];
            dbg("clr",p.S, t, s1.top(), s2.top());
            if (s1.top() < s2.top()) {
                // s2 is later
                if (t > s2.top()) {
                    s2.push(t);
                    stack_id[p.S] = 2;
                } else if (t > s1.top()) {
                    s1.push(t);
                    stack_id[p.S] = 1;
                } else {
                    dbg("fail case 1");
                    dbg(s1.top(), s2.top());
                    dbg(t, p.F, p.S);
                    fail();
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
                    dbg("fail case 2");
                    dbg(s1.top(), s2.top());
                    dbg(t, p.F, p.S);
                    fail();
                }
            }
            dbg(s1.top(),s2.top());
        }
    }
    rep(i,0,n) {
        cout << (stack_id[v[i]]) << ' ';
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