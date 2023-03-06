#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i  < (b); i++)
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{
  os << '{'; string sep; for(const auto &x: v) os << sep << x, sep = ", "; return os << '}'; 
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ")";
}

void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

const int MOD = 1e9+7;
typedef long double ld;

ld w,g,h,r;

// approximation to find max of unimodal function f on some interval
// to switch to min, negate f
// [l,r] = beginning interval
// returns (x, f(x)), where x is the point where f is maximized

// define function f:
ld f(ld x) {
    ld d1 = sqrt(x*x + (g-r)*(g-r));
    ld d2 = sqrt((w-x)*(w-x) + (h-r)*(h-r));
    return -(d1 + d2);
}

pair<ld,ld> ternary_search(ld l, ld r) {
  ld eps = 1e-12; //set the error limit here
  while (r - l > eps) {
    ld m1 = l + (r - l) / 3;
    ld m2 = r - (r - l) / 3;
    ld f1 = f(m1); // evaluates the function at m1
    ld f2 = f(m2); // evaluates the function at m2
    if (f1 < f2) l = m1;
    else r = m2;
  }
  return {l,f(l)}; //return the maximum of f(x) in [l, r]
}

ld sc = 1000000;
void solve()
{
    int n; cin >> n;
    rep(tests,0,n) {
        cin >> w >> g >> h >> r;
        w/=sc;
        g/=sc;
        h/=sc;
        r/=sc;
        ld ans1 = sqrt(w*w+(g-h)*(g-h));
        pair<ld,ld> p2 = ternary_search(0, w);
        cout << setprecision(20) << (ans1*sc) << ' ' << (-sc*p2.second) << "\n";
    }
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}