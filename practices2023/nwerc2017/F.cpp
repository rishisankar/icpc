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

int sieve(int n, vector<bool>& is_prime, vector<int>& lpf) {
    int count = n-1;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                if (is_prime[j]) {
                    is_prime[j] = false;
                    lpf[j] = i;
                    --count;
                }
            }
        }
    }
    return count;
}

vi g, lg;
int solve(int l, int r, vi& parent) {
    if (l == r) return l;
    for (int i = 0; i < r-l+1; ++i) {
        int x;
        if (i&1) x = r-i/2;
        else x = l+i/2;
        if (lg[x] < l && g[x] > r) {
            if (x != l) {
                int y = solve(l,x-1,parent);
                if (y==-1)return -1;
                parent[y] = x;
            }
            if (x != r) {
                int y = solve(x+1,r,parent);
                if (y==-1) return -1;
                parent[y] = x;
            }
            dbg(l,r,x);
            return x;
        }
    }
    return -1;
}

const int SMAX = 10000005;
void run() {
    int n; cin >> n;
    vi v(n); INP(v,n);
    VB is_prime(SMAX+1, true);
    vi lpf(SMAX+1, 0);
    iota(all(lpf), 0);
    sieve(SMAX, is_prime, lpf);
    g.assign(n,n);
    lg.assign(n,-1);
    unordered_map<int, int> m;
    for (int i = n-1; i >= 0; --i) {
        int x = v[i];
        unordered_set<int> pfs;
        while (x != 1) {
            pfs.insert(lpf[x]);
            x/=lpf[x];
        }
        for (int pf : pfs) {
            if (m.count(pf)) g[i] = min(g[i], m[pf]);
            m[pf] = i;
        }
    }
    m.clear();
    for (int i = 0; i < n; ++i) {
        int x = v[i];
        unordered_set<int> pfs;
        while (x != 1) {
            pfs.insert(lpf[x]);
            x/=lpf[x];
        }
        for (int pf : pfs) {
            if (m.count(pf)) lg[i] = max(lg[i], m[pf]);
            m[pf] = i;
        }
    }
    dbg(g);
    dbg(lg);
    vi parent(n,-1);
    if (solve(0,n-1,parent) == -1) {
        print("impossible");
        return;
    }
    for (int i : parent) cout << (i+1) << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    run();
}