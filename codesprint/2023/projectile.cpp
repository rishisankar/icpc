#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;

inline ld scl(ld x, ll px, ll py) {
    if (px==x) return LDBL_MAX;
    return py / (ld)px / (px-x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pll> v(n);
    rep(i,0,n) cin >> v[i].F >> v[i].S;
    sort(all(v));
    vector<pair<ll,pll>> vv;
    rep(i,0,n) {
        if (i == 0 || v[i] != v[i-1]) vv.pb({v[i].F, {v[i].S,v[i].S}});
        else vv.back().S.S = v[i].S;
    }
    n = sz(vv);
    ld lo = 1, hi = 1000000000000000000.L;
    rep(i,0,85) {
        ld mid = lo + (hi-lo)/2;
        bool bad = true;
        rep(i,0,n-1) {
            if (vv[i+1].F >= mid) break;
            if (scl(mid,vv[i].F,vv[i].S.S) <= scl(mid,vv[i+1].F,vv[i+1].S.F)) {
                bad = false;
                break;
            }
        }
        if (bad) lo = mid; else hi = mid;
    }
    cout << setprecision(30) << lo << '\n';
}