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
5 1 5 9 --> 13

0101
0001
0101
1001

reduces to max xor of 2 numbers in the array, which can be solved using a bit trie?

for each number:
    go from msb to lsb, if number exists with opposite bit take it
*/

/*
Returns the max XOR value of any pair of numbers in the array
B = max # of bits in value
*/
struct bt {
    int p0 = -1;
    int p1 = -1;
};
ull max_xor_pair(vector<ull>& v, int B) {
    int n = sz(v), nxt = 1;
    vector<bt> trie(B*n+1);
    ull bst = 0;
    rep(i,0,n) {
        if (i>0) {
            // check stuff currently in trie
            int cur = 0;
            ull nv = 0;
            rep(j,0,B) {
                nv<<=1;
                bool g1 = false;
                if (((v[i] >> (B-1-j))&1)) {
                    // val is a 1
                    if (trie[cur].p0 == -1) g1 = true;
                } else {
                    // val is a 0
                    if (trie[cur].p1 != -1) g1 = true;
                }
                if (g1) {
                    nv++;
                    cur = trie[cur].p1;
                } else cur = trie[cur].p0;
            }
            bst = max(bst,nv^v[i]);
        }
        // insert into trie
        int cur = 0;
        rep(j,0,B) {
            int& ptr = ((v[i] >> (B-1-j))&1) ? trie[cur].p1 : trie[cur].p0;
            if (ptr == -1) ptr = nxt++;
            cur = ptr;
        }
    }
    return bst;
}

void run() {
    int n; cin >> n;
    vector<ull> v(n+1);
    rep(i,0,n) {
        cin >> v[i+1];
        v[i+1] ^= v[i];
    }
    print(max_xor_pair(v, 32));
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