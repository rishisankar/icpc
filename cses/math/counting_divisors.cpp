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
Factor numbers from 1-n using prime sieve
O(n log(logn)) sieve preprocessing
O(log n) per query (all queries must be <= MAXN)
Source: https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/
*/
void precompute_spf(vector<int>& spf, int MAXN) {
	MAXN++;
	spf.assign(MAXN, 0);
  spf[1] = 1;
	for (int i=2; i<MAXN; i++) spf[i] = i;
	for (int i=4; i<MAXN; i+=2) spf[i] = 2; // process powers of 2
	for (int i=3; i*i<MAXN; i++) {
		// checking if i is prime
    if (spf[i] == i) {
			// marking SPF for all numbers divisible by i
			for (int j=i*i; j<MAXN; j+=i) {  
				// marking spf[j] if it is not previously marked
				if (spf[j]==j) spf[j] = i;
      }
    }
	}
}
  
// return prime factorization in O(logn)
vector<int> factor(int x, VI& spf) {
  vector<int> ret;
  while (x != 1) {
		ret.push_back(spf[x]);
      x = x / spf[x];
    }
    return ret;
}

void run() {
    int n; cin >> n;
    VI spf; precompute_spf(spf, 1000001);
    rep(i,0,n) {
        int x; cin >> x;
        VI factors = factor(x, spf);
        unordered_map<int,int> pfs;
        for (int i : factors) {
            if (pfs.count(i))pfs[i]++; else pfs[i]=1;
        }
        ll ans = 1;
        for (pii p : pfs) {
            ans*=(p.S+1);
        }
        print(ans);
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