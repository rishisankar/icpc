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

/*

011112 --> 101111  carry 1

112 --> 120 --> 201 --> 011
02 --> 10

basically, change first 0 to a 1, and thing after it becomes a 0

222

c:1
022



0 1 1 8 --> 0 1 5 0 --> 0 3 1 2 --> 1 1 2 2 --> 1 2 0 3


12014222



solve(a, b): give amt sent out on either side

solve each half


1010107 --> 1010115 --> 1011014 --> 1011103 --> 1011111


0010111110


solve(x):
repeatedly:
- take largest 0 position p, -1 if none
- c = cost of moving the 0 to position x-1 (ie. x-1-p)
- m = max moves you can do: s[x]-1
  - if (m > c) {
        move the 0 to position x-1 (swap)
        set to 1
            (so basically, set s[p] = 1 and erase from zeros set)
            s[x] = s[x] - 2 - c, s[x+1] += c+1
    } else {
        s[x] -= m, s[x+1] += m
        swap s[p], s[p+m] + upd zeros set
        done.
    }

after any changes, update zeros set!!

*/

VLL s;
int n;
set<int, greater<int>> zeros;

void solve(int x) {
    while (s[x] >= 2) {
        int p = -1;
        if (!zeros.empty()) p = *(zeros.begin());
        int c = x-1-p;
        int m = s[x] - 1;
        if (m > c) {
            if (p != -1) {
                s[p] = 1;
                zeros.erase(zeros.find(p));
            }
            s[x] = s[x] - 2 - c;
            if (x<n-1) s[x+1] += c+1;
        } else {
            s[x] -= m;
            if (x<n-1) s[x+1] += m;
            if (p != -1) {
                s[p] = 1;
                zeros.erase(zeros.find(p));
            }
            s[p+m] = 0;
            zeros.insert(p+m);
        }
    }
    if (s[x] == 0) zeros.insert(x);
}

void run() {
    string ss; cin >> ss;
    n = sz(ss);
    s.resize(n);
    rep(i,0,n) s[i] = (ss[i] - '0');
    rep(i,0,n) {
        solve(i);
    }
    rep(i,0,n) cout << s[i];
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