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

/*

Binary search approach: check an x coord X
- for each point, draw parabola Ax(x-X) that goes through it (note positive X and point.X < X ==> A < 0)
- X is valid if there exist points pi < pj s.t. the parabola through both pi, pj lands before X
- in particular it implies that A(pi) < A(pj)
==> For X to not be valid, we need A(p1) >= A(p2) >= ...
==> For X to be valid, we need A(pi) < A(pi+1) for some i

==> can solve directly for X by computing X for each adjacent pair pi, pi+1 ==> no binary search needed

*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pll> v(n);
    rep(i,0,n) cin >> v[i].F >> v[i].S;
    sort(all(v));
    vector<pair<ll,pll>> vv;
    rep(i,0,n) {
        if (i == 0 || v[i].F != v[i-1].F) vv.pb({v[i].F, {v[i].S,v[i].S}});
        else vv.back().S.S = v[i].S;
    }
    n = sz(vv);
    ld xb = 1000000000000000000.L;
    rep(i,0,n-1) {
        ld xi = vv[i].F, yi = vv[i].S.S, xj = vv[i+1].F, yj = vv[i+1].S.F;
        if (yi*xj-yj*xi != 0) {
          ld X = (yi*xj*xj-yj*xi*xi)/(yi*xj-yj*xi);
          ld A = yi/xi/(xi-X);
          if (X>=1 && A < 0) xb = min(xb,X);
        }
    }
    cout << setprecision(30) << xb << '\n';
}