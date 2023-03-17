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

0001 (0000, 0001)

0011 (0001, 0010) => 

To compute dp[i]:

j<i:
    aj ^ i < ai ^ j
    XOR both by (i^j) to get aj^j, ai^i
    first k-1 terms are equal in aj^i, ai^j ==> first k terms are equal in aj^j, ai^i
    Need kth bit = 0 in aj^i, = 1 in ai^j

    Iterate k (1...log(C)) :
        kth bit not set in ai ==> need kth bit set in j
        kth bit not set in i ==> need kth bit not set in aj
        For each prefix of length k-1, store:
            LIS for each of 4 cases of kth bit set/unset in j,aj

Implementation via bit trie
*/

struct T {
    int p0,p1;
    int dp[4]; 
    T() : p0(-1), p1(-1) {
        rep(i,0,4)dp[i]=0;
    }
};

const int C = 31;
vector<T> trie;
int nxt = 1;

// get kth bit from left
inline int kb(int x, int k) {
    return (x >> (C-1-k))&1;
}

void run() {
    nxt = 1;
    trie.clear();
    int n; cin >> n;
    VLL v(n); INP(v,n);
    vi ans(n);
    trie.pb(T());
    rep(i,0,n) {
        ans[i] = 1;
        // try to improve
        int cur = 0;
        rep(k,0,C) {
            // k = first bit that differs (l->r)
            int jv = (kb(v[i],k))^1;
            int ajv = kb(i,k);
            int kv = kb(v[i]^i,k);
            dbg(i,k,jv,ajv,kv);
            if (kv && trie[cur].p0 != -1) {
                ans[i] = max(ans[i], 1 + trie[trie[cur].p0].dp[jv*2+ajv]);
            } else if (kv == 0 && trie[cur].p1 != -1) {
                ans[i] = max(ans[i], 1 + trie[trie[cur].p1].dp[jv*2+ajv]);
            }
            cur = (kv ? trie[cur].p1 : trie[cur].p0);
            if (cur == -1) break;
        }
        // fill in trie
        cur = 0;
        rep(k,0,C) {
            int iv = kb(i,k);
            int aiv = kb(v[i],k);
            int tridx = kb(v[i]^i, k);
            dbg(i,k,iv,aiv,tridx);
            if (tridx == 1) {
                if (trie[cur].p1 == -1) {
                    trie[cur].p1 = nxt++;
                    trie.pb(T());
                }
                cur = trie[cur].p1;
            } else {
                if (trie[cur].p0 == -1) {
                    trie[cur].p0 = nxt++;
                    trie.pb(T());
                }
                cur = trie[cur].p0;
            }
            trie[cur].dp[iv*2+aiv] = max(trie[cur].dp[iv*2+aiv], ans[i]);
        }
    }
    dbg(ans);
    print(maxe(ans));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    rep(tests,0,t) run();
}