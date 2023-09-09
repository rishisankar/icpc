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
typedef pair<ld,ld> pld;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

int n;

const pair<pld,pld> DEF = {{-1,-1},{-1,-1}};
const ld TH = 1e-3;

inline int geti(pll pt, int w, int h) {
    if (pt.F == 0) return 1;
    else if (pt.S == 0) return 4;
    else if (pt.S == h) return 2;
    else if (pt.F == w) return 3;
    assert(false);
    return 0;
}

inline ll gf(multiset<ll>& s) {
    return *(s.begin());
}

inline ll gl(multiset<ll>& s) {
    return *(s.rbegin());
}


pair<pld,pld> solveAdj(int w, int h, vector<pair<pll,pll>>& lines) {
    map<ll, VLL> sweep;
    sweep[h] = VLL();
    multiset<ll> G2, L2, G1, L1;
    G2.insert(0); G1.insert(0); L2.insert(w); L1.insert(h);
    for (auto& line : lines) {
        int i1 = geti(line.F,w,h), i2 = geti(line.S,w,h);
        if (i1 == 3 && i2 == 4) return DEF;
        else if (i1 == 2) {
            G2.insert(line.F.F);
        }
        else { // i1 == 1
            sweep[line.F.S] = VLL();
            if (i2 == 3 || i2 == 4) {
                L1.insert(line.F.S);
            } else {
                sweep[line.F.S].pb(line.S.F);
                L2.insert(line.S.F);
            }
        }
    }

    // perform sweep
    ll prev = 0;
    for (auto& vlm : sweep) {
        ld v1 = (prev + vlm.F)/2.0L;
        // dbg(vlm,v1,prev);
        if (v1 > gl(G1) && v1 < gf(L1)) {
            // valid coord 1
            if (gl(G2) < gf(L2)) {
                return {{0,v1}, {(gl(G2)+gf(L2))/2.0L, h}};
            }
        }
        for (ll x : vlm.S) {
            G2.insert(x);
            L2.erase(L2.find(x));
        }
        prev = vlm.F;
    }

    return DEF;
}

pair<pld,pld> solveOpp(int w, int h, vector<pair<pll,pll>>& lines) {
    map<ll, VLL> sweep;
    sweep[h] = VLL();
    multiset<ll> G3, L3, G1, L1;
    G3.insert(0); G1.insert(0); L3.insert(h); L1.insert(h);
    for (auto& line : lines) {
        int i1 = geti(line.F,w,h), i2 = geti(line.S,w,h);
        if (i1 == 2 && i2 == 4) continue;
        else if (i1 == 2 && i2 == 3) G3.insert(line.S.S);
        else if (i1 == 3 && i2 == 4) L3.insert(line.F.S);
        else { // i1 == 1
            sweep[line.F.S] = VLL();
            if (i2 == 2) {
                G1.insert(line.F.S);
            } else if (i2 == 4) {
                L1.insert(line.F.S);
            } else {
                sweep[line.F.S].pb(line.S.S);
                G3.insert(line.S.S);
            }
        }
    }

    // perform sweep
    ll prev = 0;
    for (auto& vlm : sweep) {
        ld v1 = (prev + vlm.F)/2.0L;
        // dbg(vlm,v1,prev);
        if (v1 > gl(G1) && v1 < gf(L1)) {
            // dbg("c1 valid");
            // valid coord 1
            if (gl(G3) < gf(L3)) {
                // dbg("c2 valid");
                return {{0,v1}, {w, (gl(G3)+gf(L3))/2.0L}};
            }
            // } else {
            //     dbg(gl(G3), gf(L3));
            // }
        }
        for (ll x : vlm.S) {
            L3.insert(x);
            G3.erase(G3.find(x));
        }
        prev = vlm.F;
    }

    return DEF;
}

void cleanup(int w, int h, vector<pair<pll,pll>>& lines) {
    for (auto& line : lines) {
        vector<pll> v {line.F,line.S};
        for (auto x : v) {
            assert(x.F >= 0 && x.F <= w && x.S >= 0 && x.S <= h);
        }
        if (geti(line.F,w,h) > geti(line.S,w,h)) swap(line.F,line.S);
    }
}

void pline(pair<pld,pld> l) {
    print(1);
    print(l.F.F,l.F.S,l.S.F,l.S.S);
    exit(0);
}

pair<pld,pld> solve(int w, int h, vector<pair<pll,pll>>& lines, bool tryopp) {
    cleanup(w,h,lines);
    auto p1 = solveAdj(w,h,lines);
    if (!tryopp || p1 != DEF) return p1;
    return solveOpp(w,h,lines);
}

inline pll rotate90(pll pt) {
    return {pt.S, -pt.F};
}

inline pld rotate90(pld pt) { 
    return {pt.S, -pt.F};
}

vector<pair<pll,pll>> rotateV(vector<pair<pll,pll>>& lines, ll xadd, ll yadd) {
    vector<pair<pll,pll>> copy;
    for (auto line : lines) {
        line.F = rotate90(line.F);
        line.S = rotate90(line.S);
        line.F.F+=xadd; line.S.F+=xadd;
        line.F.S+=yadd; line.S.S+=yadd;
        copy.pb(line);
    }
    return copy;
}

void run() {
    cin >> n;
    ll w,h; cin >> w >> h;
    vector<pair<pll,pll>> lines;
    rep(i,0,n) {
        ll a,b,c,d; cin >> a >> b >> c >> d;
        lines.pb({{a,b},{c,d}});
    }
    auto r1 = solve(w,h,lines,true);
    if (r1 != DEF) {
        pline(r1);
    }

    // rotations...
    vector<pair<pll,pll>> l90 = rotateV(lines,0,w);
    auto r2 = solve(h,w,l90,true);
    if (r2 != DEF) {
        r2.F.S -= w;
        r2.S.S -= w;
        rep(i,0,3) {
            r2.F = rotate90(r2.F);
            r2.S = rotate90(r2.S);
        }
        dbg("r90 solve");
        pline(r2);
    }
    vector<pair<pll,pll>> l180 = rotateV(l90,0,h); // rotateV(rotateV(lines,0,0), w, h);
    auto r3 = solve(w,h,l180,false);
    if (r3 != DEF) {
        dbg(r3);
        r3.F.F -= w;
        r3.S.F -= w;
        r3.F.S -= h;
        r3.S.S -= h;
        rep(i,0,2) {
            r3.F = rotate90(r3.F);
            r3.S = rotate90(r3.S);
        }
        dbg("r180 solve");
        pline(r3);
    }
    vector<pair<pll,pll>> l270 = rotateV(l180,0,w); // rotateV(rotateV(rotateV(lines,0,0),0,0),h,0);
    auto r4 = solve(h,w,l270,false);
    if (r4 != DEF) {
        r4.F.F -= h;
        r4.S.F -= h;
        r4.F = rotate90(r4.F);
        r4.S = rotate90(r4.S);
        dbg("r270 solve");
        pline(r4);
    }


    // finally, give up

    print(2);
    print(0, TH, w, h-TH);
    print(TH, h, w-TH, 0);

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