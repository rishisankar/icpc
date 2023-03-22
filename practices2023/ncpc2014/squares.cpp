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

long long GCD(long long x, long long y)
{
    if (y == 0) return x;
    return GCD(y, x%y);
}

pll rf(pll f) {
    if (f.S == 0) return {1,0};
    if (f.F == 0) return {0,1};
    ll g = GCD(llabs(f.F), llabs(f.S));
    f.F /= g;
    f.S /= g;
    if (f.S < 0) {
        f.F *= -1; f.S *= -1;
    }
    return f;
}

pll sf(pll p1, pll p2) {
    pll res = {p2.S*p1.F-p2.F*p1.S, p1.S*p2.S};
    return rf(res);
}
pll mf(pll p1, pll p2) {
    pll res = {p1.F*p2.F, p1.S*p2.S};
    return rf(res);
}

typedef tuple<ll,ll,ll,ll> L;

pll dist(L& l1, L& l2, pll& slope) {
    pll yd = rf({get<1>(l1) - get<1>(l2), 1});
    pll xd = rf({get<0>(l1) - get<0>(l2), 1});
    pll ans = sf(yd,mf(slope, xd));
    ans.F = llabs(ans.F);
    ans.S = llabs(ans.S);
    return ans;
}

pll distH(pll dV, pll slope) {
    swap(slope.F, slope.S);
    pll ans = mf(dV,slope);
    ans.F = llabs(ans.F);
    ans.S = llabs(ans.S);
    return ans;   
}

void run() {
    int n; cin >> n;
    map<pll, vector<L>> m;
    vector<ll> vertLines;
    vector<ll> horizLines;
    rep(i,0,n) {
        ll a,b,c,d;
        cin >> a >> b >> c >> d;
        pll slope = rf({d-b, c-a});
        if (slope.F == 0) {
            horizLines.pb(b);
        } else if (slope.S == 0) {
            vertLines.pb(a);
        } else {
            m[slope].pb({a,b,c,d});
        }
    }
    map<ll,int> vertD, horizD;
    rep(i,0,vertLines.size()) {
        rep(j,i+1,vertLines.size()) {
            ll d = (llabs(vertLines[i]-vertLines[j]));
            vertD[d]++;
        }
    }
    rep(i,0,horizLines.size()) {
        rep(j,i+1,horizLines.size()) {
            ll d = (llabs(horizLines[i]-horizLines[j]));
            horizD[d]++;
        }
    }
    ll ans = 0;
    for (auto p : vertD) {
        if (horizD.count(p.F)) {
            ans += p.S * horizD[p.F];
        }
    }

    map<pll, map<pll,int>> mdV;
    map<pll, map<pll,int>> mdH;
    for (auto p : m) {
        pll slope = p.F;
        rep(i,0,p.S.size()) {
            rep(j,i+1,p.S.size()) {
                pll dV = dist(p.S[i], p.S[j], slope);
                pll dH = distH(dV, slope);
                mdV[slope][dV]++;
                mdH[slope][dH]++;
            }
        }
    }
    for (auto p : mdV) {
        dbg("slope",p.F);
        for (auto p2 : p.S) {
            dbg("dc", p2.F, p2.S);
        }
    }
    for (auto p : mdH) {
        dbg("slope",p.F);
        for (auto p2 : p.S) {
            dbg("dc", p2.F, p2.S);
        }
    }
    ll ans2 = 0;
    for (auto it = mdV.begin(); it != mdV.end(); it++) {
        pll s1 = it->first;
        if (s1.F == 0 || s1.S == 0) continue;
        for (auto it2 = mdH.begin(); it2 != mdH.end(); it2++) {
            // check perp
            pll s2 = it2->F;
            if (s2.F == 0 || s2. S == 0) continue;
            if (s1.F*s2.F + s1.S*s2.S != 0) continue;
            for (auto p : it->second) {
                if (it2->second.count(p.F)) {
                    ans2 += it2->second[p.F] * p.S;
                }
            }
        }
    }
    dbg(ans,ans2);
    print(ans+ans2/2);
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
