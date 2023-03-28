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

const long long INF = 10000000000000000LL;

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if ((a - b) % g == 0) return -1;
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}

ll gcd(ll a, ll b) {
    if (a == 0) return b; 
    return gcd(b % a, a); 
} 

ll lcm(ll a, ll b) {
  return a*b/gcd(a,b);
}

ll transTime(ll t, int L1, int R1, int L2, int R2) {
    ll opt = LLONG_MAX;
    for (int i = L1; i <= R1; ++i) {
        if (i < L2 || i > R2) continue;
        vi pts1, pts2;
        if (i == L1) pts1.pb(0);
        else if (i == R1) pts1.pb(R1-L1);
        else {
            pts1.pb(i-L1);
            pts1.pb(2*(R1-L1) - i);
        }
        if (i == L2) pts2.pb(0);
        else if (i == R2) pts2.pb(R1-L1);
        else {
            pts2.pb(i-L2);
            pts2.pb(2*(R2-L2) - i);
        }
        for (int x : pts1) {
            for (int y : pts2) {
                dbg(x,y);
                ll ans = crt(x, 2*(R1-L1), y, 2*(R2-L2));
                if (ans == -1) continue;
                ll L = lcm(2*(R1-L1),2*(R2-L2));
                ans %= L;
                ans += (t/L-1) * L;
                while (ans < t) ans += L;
                opt = min(opt, ans);
            }
        }
    }
    return (opt == LLONG_MAX) ? -1 : opt;
}

void run() {
    int n,w; cin >> n >> w;
    VPII boats(n);
    VLL earliest(n,INF);
    VB marked(n,false);
    rep(i,0,n) {
        cin >> boats[i].F >> boats[i].S;
        if (boats[i].F == 0) {
            earliest[i] = 0;
        }
    }
    while (true) {
        int nd = -1;
        rep(j,0,n) {
            if (marked[j] || earliest[j]==INF) continue;
            if (nd == -1 || earliest[j] < earliest[nd]) nd = j;
        }
        if (nd == -1) {
            // no more nodes to perform relaxation from
            break;
        }
        marked[nd] = true;
        rep(i,0,n) {
            if (marked[i]) continue;
            // for each other unfinalized node i, figure out how to reach from nd after time t
            ll t = earliest[nd];
            ll tp = transTime(t, boats[nd].F, boats[nd].S, boats[i].F, boats[i].S);
            if (tp == -1) continue;
            else {
                earliest[i] = min(tp, earliest[i]);
            }
        }
    }
    // iterate through possible last boats
    ll optTime = LLONG_MAX;
    rep(i,0,n) {
        if (boats[i].S != w || earliest[i] == INF) continue; // cant reach boat or boat can't be last
        ll t = earliest[i];
        int L = boats[i].F, R = boats[i].S;
        t %= (2*(R-L));
        ll tm = ((R-L-t) + 2*(R-L)) % (2*(R-L));
        optTime = min(optTime, tm);
    }

    if (optTime == LLONG_MAX) {
        print("IMPOSSIBLE");
    } else {
        print(optTime);
    }

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