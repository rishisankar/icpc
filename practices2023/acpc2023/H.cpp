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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); }
    size_t operator()(uint64_t x) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + FIXED_RANDOM); }
};
template<typename T, typename U> struct safe_map : public std::unordered_map<T,U,custom_hash> {};
template<typename T> struct safe_set : public std::unordered_set<T,custom_hash> {};

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

typedef vector<ld> vd;
const ld eps = 1e-9;

int solveLinear(vector<vd>& A, vd& b, vd& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		ld v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = fabs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv <= eps) {
			rep(j,i,n) if (fabs(b[j]) > eps) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = 1/A[i][i];
		rep(j,i+1,n) {
			ld fac = A[j][i] * bv;
			b[j] -= fac * b[i];
			rep(k,i+1,m) A[j][k] -= fac*A[i][k];
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] /= A[i][i];
		x[col[i]] = b[i];
		rep(j,0,i) b[j] -= A[j][i] * b[i];
	}
	return rank; // (multiple solutions if rank < m)
}

void run() {
    int n; cin >> n;
    int N = (1<<n);
    vector<ld> v(n); INP(v,n);
    vector<vector<vector<ld>>> dp(N, vector<vector<ld>>(n, vector<ld>(n))); // (mask for who's alive, whos turn is it , k) = chance of perosn k winning
    rep(i,0,n) {
        dp[(1<<i)][i][i] = 1;
    }
    vi indices;
    rep(i,0,N) {
        if (__builtin_popcount(i) >= 2) indices.pb(i);
    }
    sort(all(indices), [](int a, int b) {
        return __builtin_popcount(a) < __builtin_popcount(b);
    });
    for (int mask : indices) {
        vector<int> attack(n,-1); // who each alive person will attack
        vector<int> alive; // list of alive ppl
        // for each alive person, populate attack:
        rep(i,0,n) {
            // must be alive
            if (((mask >> i) & 1) == 0) continue;
            alive.pb(i);
            // find best person to attack
            int bestA = 0;
            ld bestChance = -1;
            rep(j,0,n) {
                // who is being attacked
                if (i == j) continue; // cant attack urself
                if (((mask >> j) & 1) == 0) continue; // cant attack someone dead
                int newMask = (mask ^ (1 << j)); // assume person j dies
                // figure out whose turn is next given that j is dead
                int kk;
                for (int k = i+1; k <= i+n; ++k) {
                    kk = k%n;
                    if ((newMask >> kk) & 1) break; // if they're alive under new mask
                }
                ld winChance = dp[newMask][kk][i]; // chance of player i winning given kk's turn
                if (winChance > bestChance + eps) {
                    bestA = j;
                    bestChance = winChance;
                }
            }
            attack[i] = bestA;
        }
        // dbg(mask, attack);

        // compute probability of person i winning across everyone's turn given mask
        rep(i,0,n) {
            if (attack[i] == -1) continue; // if already dead, can't win
            int dim = sz(alive);
            vector<vd> A(dim, vd(dim));
            vd b(dim);
            vd x(dim);
            rep(j,0,dim) {
                int pl = alive[j]; // whos turn is it
                // next turn assuming player attacks successfully: next in alive, unless person attacked is next
                int nxt = (attack[pl] == alive[(j+1)%dim]) ? alive[(j+2)%dim] : alive[(j+1)%dim];
                assert(attack[pl] != -1);
                ld winChanceIfKill = dp[mask ^ (1 << attack[pl])][nxt][i]; // chance of i winning, assuming attack is successful
                b[j] = v[pl] * winChanceIfKill;
                A[j][j] = 1;
                A[j][(j+1)%dim] = v[pl] - 1; // if not successful, go to next person
            }
            int rank = solveLinear(A,b,x);
            rep(j,0,dim) {
                dp[mask][alive[j]][i] = x[j];
            }
        }
        // dbg(mask, "fin");
    }
    for (ld x : dp[N-1][0]) print(x);
    // print(dp[N-1][0]);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    cout.setf(ios::fixed);
    cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}