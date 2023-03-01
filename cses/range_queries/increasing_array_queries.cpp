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

struct Tree {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

/*
Idea:
1) sort queries in decreasing order by a
2) vector s acts as monotonically increasing stack that you can binary search on
3) traverse r->l, updating stack
4) store solns for each section of stack to efficiently rangesum
*/
void run() {
    int n, q; cin >> n >> q;
    VLL v(n); INP(v,n);
    VLL pf(n); pf[0]=v[0]; rep(i,1,n)pf[i]=pf[i-1]+v[i];
    vector<pair<pii,int>> queries(q);
    rep(i,0,q) {
        int a,b; cin >> a >> b; --a; --b;
        queries[i] = {{a,b},i};
    }
    sort(all(queries), greater<pair<pii,int>>());
    vector<ll> ans(q);
    Tree st(n);
    vector<int> s;
    int curL = n;
    rep(Q,0,q) {
        int a = queries[Q].F.F;
        int b = queries[Q].F.S;
        while (curL > a) {
            --curL;
            while (!s.empty() && v[s.back()] <= v[curL]) {
                st.update(s.size()-1,0);
                s.pop_back();
            }
            int bk = (s.size() == 0 ? n : s.back());
            ll cost = (bk-curL) * v[curL] - (pf[bk-1] - (curL==0?0:pf[curL-1]));
            s.push_back(curL);
            st.update(s.size()-1,cost);
        }
        // answer the query given b
        // find index in s of largest i <= b
        int best = s.size()-1;
        int lo = 0, hi = best;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            if (s[mid] <= b) {
                best = mid;
                hi = mid-1;
            } else lo = mid+1;
        }
        ll res = ((best == s.size()-1) ? 0 : st.query(best+1, s.size()));
        res += (b-s[best])*v[s[best]] - (pf[b]-pf[s[best]]);
        ans[queries[Q].S] = res;
    }
    for (ll x : ans) cout << x << '\n';
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