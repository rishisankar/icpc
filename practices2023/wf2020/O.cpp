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

template<typename T> inline T ceildiv(T a, T b) {return (a+b-1)/b;}

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

ll M = 3600000;

struct H {
	ull x; H(ull x=0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(vector<ll>& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};


void fail() {
    print("Different");
    exit(0);
}
ll ginp() {
    string s; cin >> s;
    ll x = 0;
    int xp = -1;
    for (int i = 0; i < sz(s); ++i) {
        if (s[i] == '.') {
            xp = i;
        }
    }
    if (xp != -1 && xp != sz(s)-1) {
        string rt = s.substr(0, xp);
        string dec = s.substr(xp+1, sz(s) - 1 - xp);
        while (sz(dec) < 4) {
            dec += '0';
        }
        x = stoll(rt) * 10000LL;
        if (s[0] == '-') x -= stoll(dec);
        else x += stoll(dec);
    } else {
        x = stoll(s) * 10000LL;
    }
    if (x < 0) x += M;
    return x;
}

VLL genseq(VLL &v) {
    VLL seq;
    rep(i,0,sz(v)-1) {
        seq.pb(v[i+1] - v[i]);
    }
    seq.pb(v[0] + M - v.back());
    return seq;
}

// return indices in seq2 that first elt of seq1 can be mapped to for sequences to match
vi genmapping(VLL& seq1, VLL& seq2) {
    VLL seq2dup;
    for (ll x : seq2) seq2dup.pb(x);
    for (ll x : seq2) seq2dup.pb(x);
    HashInterval hs(seq2dup);
    HashInterval hs1(seq1);
    H hsh1 = hs1.hashInterval(0, sz(seq1));
    vi ans;
    rep(i,0,sz(seq1)) {
        if (hs.hashInterval(i, i+sz(seq1)) == hsh1) {
            ans.pb(i);
        }
    }
    return ans;
}

void run() {
    int n; cin >> n;
    unordered_map<ll, vector<ll>> inp, inp2;
    rep(i,0,n) {
        ll x = ginp();
        ll y = ginp();
        inp[x].pb(y);
    }
    rep(i,0,n) {
        ll x = ginp();
        ll y = ginp();
        inp2[x].pb(y);
    }

    for (auto& p : inp) sort(all(p.S));
    for (auto& p : inp2) sort(all(p.S));

    for (auto& p : inp) {
        if (sz(inp2[p.F]) != sz(inp[p.F])) fail();
    }
    for (auto& p : inp2) {
        if (sz(inp2[p.F]) != sz(inp[p.F])) fail();
    }

    unordered_set<ll> keys;
    for (auto& p : inp) keys.insert(p.F);

    unordered_set<ll> valid_scl;

    for (ll key : keys) {
        VLL seq1 = genseq(inp[key]);
        VLL seq2 = genseq(inp2[key]);
        dbg(key,inp[key],inp2[key]);
        dbg(key,seq1,seq2);
        vi mappings = genmapping(seq1, seq2);
        if (sz(mappings) == 0) fail();
        dbg(key,mappings);
        unordered_set<ll> valid_scl_new;
        for (int i : mappings) {
            ll sc = inp2[key][i] - inp[key][0];
            sc %= M;
            if (sc < 0) sc += M;
            if (valid_scl.empty() || valid_scl.count(sc)) {
                valid_scl_new.insert(sc);
            }
        }
        if (valid_scl_new.empty()) fail();
        swap(valid_scl, valid_scl_new);
    }
    for (ll x : valid_scl) dbg(x);
    print("Same");
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