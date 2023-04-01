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

void run() {
    int r, c, n; cin >> r >> c >> n;
    vector<string> grid(r);
    rep(i,0,r) {
        cin >> grid[i];
    }
    map<pii,int> idm;
    rep(i,0,r) {
        rep(j,0,c) {
            if (grid[i][j] == '*') idm[{i,j}] = sz(idm);
        }
    }
    VVB hl(r,VB(c)), vl(r, VB(c));
    int k = sz(idm); // # *s
    n = k - n; // amt of connections needed
    UF d(k);
    // sweep rows
    rep(i,0,r) {
        int ps = -1; int pid = -1;
        rep(j,0,c) {
            if (grid[i][j] == '*') {
                int id = idm[{i,j}];
                if (ps != -1) {
                    int dp = d.find(pid);
                    int dc = d.find(id);
                    if (dp != dc) {
                        d.join(pid,id);
                        n--;
                        for (int jp = j-1; jp > ps; --jp) hl[i][jp] = true;
                        if (n == 0) break;
                    }
                }
                ps = j;
                pid = id;
            }
        }
        if (n == 0) break;
    }
    if (n > 0) {
        // sweep cols
        rep(j,0,c) {
            int ps = -1; int pid = -1;
            rep(i,0,r) {
                if (grid[i][j] == '*') {
                    int id = idm[{i,j}];
                    if (ps != -1) {
                        int dp = d.find(pid);
                        int dc = d.find(id);
                        if (dp != dc) {
                            d.join(pid,id);
                            n--;
                            for (int ip = i-1; ip > ps; --ip) vl[ip][j] = true;
                            if (n == 0) break;
                        }
                    }
                    ps = i;
                    pid = id;
                }
            }
            if (n == 0) break;
        }
    }
    dbg(n);
    rep(i,0,r) {
        rep(j,0,c) {
            if (grid[i][j] == '*') cout << '*';
            else if (vl[i][j] && hl[i][j]) cout << '+';
            else if (vl[i][j]) cout << '|';
            else if (hl[i][j]) cout << '-';
            else cout << ' ';
        }
        cout << '\n';
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