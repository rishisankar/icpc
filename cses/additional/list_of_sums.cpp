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

b[0] = a0 + a1
b[1] = a0 + a2
b[2] = min(a0+a3, a1+a2)
b[k] = a1+a2 with k = O(n) 

knowing a0 gives us entire array in n^2 log n
    a1 = b0 - a0
    repeatedly: ai = smallest remaining val - a0
        iterate through j = 1...{i-1}
            remove sum ai+aj if possible, else fail
        

iterate over all possible values for a1+a2.
    try to generate array, if successful return
*/

void run() {
    ll n; cin >> n;
    ll m = n*(n-1)/2;
    VLL v(m); INP(v,m);
    sort(all(v));
    // iterate over possible positions for a1+a2
    for (int l = 2; l <= min(m-1, n+3); ++l) {
        if ((v[0] + v[1] - v[l]) &1) continue;
        VLL arr(n);
        multiset<ll> s;
        for (ll x : v) s.insert(x);
        arr[0] = (v[0] + v[1] - v[l])/2;
        bool valid = true;
        rep(i,1,n) {
            arr[i] = (*s.begin()) - arr[0];
            rep(j,0,i) {
                auto it = s.find(arr[i] + arr[j]);
                if (it == s.end()) {
                    valid = false;
                    break;
                } else s.erase(it);
            }
            if (!valid) break;
        }
        if (valid) {
            for (ll x : arr) cout << x << ' ';
            cout << '\n';
            return;
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