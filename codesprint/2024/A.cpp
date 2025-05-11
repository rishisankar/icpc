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

vector<vector<ll>> jmpD;
VLL pos;
ll n,k,D,q;
vector<vi> treeJump(vi& P){
    int N = sz(P);
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
	vector<vi> jmp(d, P);
    jmpD.resize(d,vector<ll>(N));
	rep(i,1,d) rep(j,0,sz(P)) {
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    }
    rep(i,0,N) {
        jmpD[0][i] = (D+D+pos[P[i]]-pos[i])%D;
    }
    rep(i,1,d) rep(j,0,sz(P)) {
        jmpD[i][j] = jmpD[i-1][j] + jmpD[i-1][jmp[i-1][j]];
    }
	return jmp;
}

ll jmp(vector<vi>& tbl, int nod, int steps){
    ll ans = 0;
	rep(i,0,sz(tbl)) {
		if(steps&(1<<i)) {
            ans += jmpD[i][nod];
            nod = tbl[i][nod];
        }
    }
	return ans;
}


void run() {
    cin >> n >> k >> D >> q;
    pos.resize(n);
    VLL type(n);
    INP(pos,n); INP(type,n);
    vector<set<pii>> posByType(k);
    rep(i,0,n) {
        posByType[type[i]].insert({pos[i],i});
    }
    vi nxt(n);
    rep(i,0,n) {
        auto& s = posByType[(type[i] + 1)%k];
        int p = pos[i];
        auto it = s.lower_bound({p,-1});
        if (it == s.end()) {
            nxt[i] = (*(s.begin())).S;
        } else {
            nxt[i] = it->S;
        }
    }
    dbg(nxt);
    dbg(pos);
    vector<vi> tbl = treeJump(nxt);
    dbg(jmpD[0]);
    dbg(tbl[0]);
    rep(Q,0,q) {
        int dq,kq,nq; cin >> dq >> kq >> nq;
        if (nq == 0) {
            print(0);
            continue;
        }

        int sp;

        auto& s = posByType[kq];
        auto it = s.lower_bound({dq,-1});
        if (it == s.end()) {
            sp = (*(s.begin())).S;
        } else {
            sp = it->S;
        }
        ll st = (D+D+pos[sp]-dq)%D;
        dbg(Q, sp, st);
        if (nq>1) {
            ll xtr = jmp(tbl, sp, nq-1);
            dbg(xtr);
            st += xtr;
        }
        print(st);
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