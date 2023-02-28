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

/*
Find max subarray sum of length a<=L<=b
Assumes 0<=a<=b<=n , runs in O(n)
*/
ll maxSubarraySumInRange(VLL& v, int a, int b) {
    int n = v.size();
    assert(0<=a && a<=b && b<=n);
    if (b == 0) return 0;
    VLL pf(n); pf[0]=v[0];
    for (ll i = 1; i < n; ++i) pf[i]=pf[i-1]+v[i];
    deque<int> d;
    // initial population of deque
    rep(j,0,b-1) {
        while (!d.empty() && pf[d.back()]<=pf[j]) d.pop_back();
        d.push_back(j);
    }
    ll ans = LLONG_MIN;
    if (a == 0) {
        ans = 0;
        a = 1;
    }
    // consider subarrays starting at i (of length at most b)
    rep(i,0,n-a+1) {
        // last index j must be in [a+i-1,b+i-1] , choose such j w max pf[j]
        while (!d.empty() && d.front()<a+i-1) d.pop_front();
        // b+i-1 now in range ==> add to deq; remove anything smaller
        if (b+i-1 < n) {
            while (!d.empty() && pf[d.back()]<=pf[b+i-1]) d.pop_back();
            d.push_back(b+i-1);
        }
        ans = max(ans, pf[d.front()]-(i==0?0:pf[i-1]));
    }
    return ans;
}

void run() {
    int n,k;
    ll x;
    cin >> n >> k >> x;
    VLL v(n); INP(v,n);
    VLL pf(n);
    pf[0] = v[0]; rep(i,1,n) pf[i] = pf[i-1] + v[i];
    ll best = 0;
    if (n==k) { k=0; x=-x; }
    if (x >= 0) {
        // bf for size <= k
        for (ll siz = 1; siz <= k; ++siz) {
            for (ll i = 0; i < n-siz+1; ++i) {
                ll val = pf[i+siz-1] - ((i == 0) ? 0 : pf[i-1]);
                best=max(best, val + x*siz);
            }
        }
        // scale entire array -= x => (max subarray of size > k) + x*k
        for(ll i = 0; i < n; ++i) v[i] -= x;
        ll ans = maxSubarraySumInRange(v,k,n) + x*2LL*k;
        best = max(ans,best);
    } else {
        // bf for size >= n-k
        for (ll siz = n-k; siz <= n; ++siz) {
            for (ll i = 0; i < n-siz+1; ++i) {
                ll val = pf[i+siz-1] - ((i == 0) ? 0 : pf[i-1]);
                best=max(best, val - x*(n-k) + x*(siz-(n-k)));
            }
        }
        // calc max subarray of size <= n-k (assume you apply -x on all)
        for (ll i = 0; i < n; ++i) v[i] -= x;
        best = max(best,maxSubarraySumInRange(v, 0, n-k));
    }
    print(best);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    ll t; cin >> t;
    // ll t=1;
    for(ll tests = 0; tests < t; ++tests) run();
}