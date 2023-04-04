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
Binary search: for a given number, how many times do you press {max dig 1?} typing 1...n

examples:

69394
    how many times does 1 appear in digit 1: 10000 - 19999 = 10000 times
    how many times does 1 appear in digit 2: 1000-1999, 11000-11999, ..., 61000-61999 ==> 1000*7 = 7000 times
    how many times does 1 appear in digit 3: 00100-00199, ..., 69100-69199 ==> 70*100 = 7000 times
    how many times does 1 appear in digit 4: 00010-00019, ..., 69310-69319 ==> 694*10 = 6940 times
    how many times does 1 appear in digit 5: 00001, ..., 69391 ==> 6940*1 = 6940 times


603
    how many times does 1 appear in digit 1: 100-199 ==> 100 times
    how many times does 1 appear in digit 2: 010-019, ..., 510-519 ==> 6*10 = 60 times
    how many times does 1 appear in digit 3: 001, ..., 601 ==> 61 times

611
    how many times does 1 appear in digit 1: 100-199 ==> 100 times
    how many times does 1 appear in digit 2: 010-019, ..., 510-519, 610,611 ==> 6*10+2 = 62 times
    how many times does 1 appear in digit 3: 001, ..., 611 ==> 62 times


for each digit l-->r:
    if digit > 1: ans += (prev digits+1) * 10^k
    if digit = 1: ans += (prev digits)*10^k + 1 + remaining digits
    if digit = 0: ans += (prev digits) * 10^k
*/

/*
count number of times 1 appears in 1...n
*/
ll ct(ll n) {
    ll ans = 0;
    ll p = 1;
    while (n/p) {
        int dig = (n/p)%10;
        if (dig > 1) ans += (n/p/10 +1) * p;
        else if (dig == 1) ans += (n/p/10)*p + 1 + (n%p);
        else ans += (n/p/10)*p;
        p*=10;
    }
    return ans;
}

void run() {
    ll n; cin >> n;
    ll lo = 1, hi = 1000000000000000000LL;
    ll bst = -1;
    while (lo <= hi) {
        ll mid = lo + (hi-lo)/2;
        if (ct(mid) > n) hi = mid-1;
        else {
            bst = mid;
            lo = mid+1;
        }
    }
    print(bst);
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