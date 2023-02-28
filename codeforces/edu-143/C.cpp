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

void run() {
    int n; cin >> n;
    VLL a(n); INP(a,n);
    VLL b(n); INP(b,n);
    VLL pf(n,0); pf[0] = b[0]; rep(i,1,n) pf[i]=b[i]+pf[i-1];
    VI segs(n); // segs i = [i,y)  -> player i..y-1 all drink i fully
    rep(i,0,n) {
        int lo = i;
        int hi = n;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            if (mid == 0) { segs[i] = 0; lo = mid+1; continue; }
            ll amt = pf[mid-1] - (i == 0 ? 0 : pf[i-1]);
            if (amt <= a[i]) { segs[i] = mid; lo = mid+1; continue; }
            else hi = mid-1;
        }
    }
    dbg(segs);
    VVI seglist(n+1);
    rep(i,0,n) seglist[segs[i]].pb(i);
    VLL ans(n,0);
    ll op = 0;
    rep(i,0,n) {
        op++;
        for (int x : seglist[i]) op--;
        ans[i] += b[i]*op;
    }
    dbg(ans);
    rep(i,0,n) {
        if (segs[i] != n) {
            ans[segs[i]] += a[i] - ((segs[i] == 0 ? 0 : pf[segs[i]-1]) -  (i == 0 ? 0 : pf[i-1]));
        }
    }
    for (ll x : ans) cout << x << ' '; cout << endl;
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