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

// return gcd(a,b) and solve for integer x,y: ax+by=gcd(a,b)
// linear diophantine equations ax+by=c have a solution iff c divides gcd(a,b)
ll euclidean(ll a, ll b, ll &x, ll &y) {

    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    ll x1,y1;
    ll gcd_ = euclidean(b%a, a, x1, y1);

    x = y1 - (b/a) * x1;
    y = x1;

    return gcd_;

}

// only exists if gcd(a,m) = 1 !! otherwise return -1
ll modularInverse(ll a, ll m) {
    ll x,y;
    ll g = euclidean(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m; // shift x to positive in case it is negative
}

tuple<ll,ll,ll> matmul(tuple<ll,ll,ll> v1, tuple<ll,ll,ll> v2, ll mod) {
  // (a+bi)(c+di) = (ac-bd)+(ad+bc)i
  ll nd = (get<2>(v1)*get<2>(v2)) %mod;
  ll rl = ((get<0>(v1)*get<0>(v2))%mod) - ((get<1>(v1)*get<1>(v2))%mod);
  rl = ((rl%mod)+mod) % mod;
  ll im = ((get<0>(v1)*get<1>(v2))%mod) + ((get<1>(v1)*get<0>(v2))%mod);
  im = ((im%mod)+mod) % mod;
  return {rl,im,nd};
}

tuple<ll,ll,ll> matmodpow(tuple<ll,ll,ll> base, ll exp, ll mod) {
  tuple<ll,ll,ll> result = {1,0,1};
  while (exp > 0) {
    if (exp & 1) result = matmul(result,base,mod);
    base = matmul(base, base,mod);
    exp >>= 1;
  }
  return result;
}

const ll m = 1e9+7;
void solve()
{
  ll a, b, n;
  cin >> a >> b >> n;
  ++n;
  // initial point: (a^2-b^2)/(a^2+b^2) , 2ab/(a^2+b^2)
  ll a2 = (a*a)%m;
  ll b2 = (b*b)%m;
  ll x = (((a2-b2)%m)+m)%m;
  ll y = (2*a*b)%m;
  ll d = (a2+b2)%m;
  // raise (x/d+y/d i) to the nth power 
  tuple<ll,ll,ll> res = matmodpow({x,y,d},n,m);
  dbg(get<0>(res), get<1>(res), get<2>(res));
  ll inv = modularInverse(get<2>(res), m);
  ll num = -1 * get<0>(res);
  num = ((num%m)+m)%m;
  ll ans = (num * inv) % m;
  cout << ans << "\n";
}

int main()
{
  ios::sync_with_stdio(0); cin.tie(0);
  solve();
}