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

struct D {
    D() : sum(0), pref(0), suff(0), mx(0) {}
    ll sum;
    ll pref;
    ll suff;
    ll mx;  
};

struct Tree {
	typedef D T;
	const T unit;
	T f(T a, T b) { 
        T ans;
        ans.sum = a.sum+b.sum;
        ans.pref = max(a.pref, a.sum+b.pref);
        ans.suff = max(a.suff+b.sum, b.suff);
        ans.mx = max(max(a.mx, b.mx), a.suff + b.pref);
        return ans;
    }
	vector<T> s; int n;
	Tree(int n = 0) : s(2*n, unit), n(n) {}
	void update(int pos, ll val) {
        T x; x.sum = val; x.pref = x.suff = x.mx = max(0LL,val);
		for (s[pos += n] = x; pos /= 2;)
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

vi solve(string s, int n, vi& quers) {
    Tree st(sz(s));
    rep(i,0,sz(s)) {
        if (s[i] == '1') {
            st.update(i, -1000000);
        } else {
            st.update(i,1);
        }
    }
    vi ans(n);
    rep(i,0,n) {
        int q = quers[i];
        if (s[q-1] == '0') {
            s[q-1] = '1';
            st.update(q-1, -1000000);
        } else {
            s[q-1] = '0';
            st.update(q-1,1);
        }
        ans[i] = st.query(0,sz(s)).mx;
    }
    return ans;
}

void run() {
    string s; cin >> s;
    int n; cin >> n;
    vi quers(n); INP(quers,n);
    vi a1 = solve(s,n,quers);
    rep(i,0,sz(s)) {
        if (s[i]=='0') s[i]='1'; else s[i]='0';
    }
    vi a2 = solve(s,n, quers);
    rep(i,0,n) {
        cout << max(a1[i],a2[i]) << ' ';
    }
    cout << '\n';
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