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
12543 (3): n=5. possible: 5,4,3
12354 (4)
- amt increasing: k-1
123654: n=6. possible: 6,5,4


n=4: possible: 4,3,2
k=2:
2 1 4 3
2 4 1 3
3 1 4 2
3 4 1 2

(4,2)   ^
(5,3)   {4, 5, 1, 2, 3}
(6,3)   {6, 4, 5, 1, 2, 3}
(7,3)   {7, 4, 5, 6, 1, 2, 3}
(8,3)   {7, 8, 4, 5, 6, 1, 2, 3}
(9,3)   {7, 8, 9, 4, 5, 6, 1, 2, 3}
(10,4)
(11,4)
(12,4)  {10,11,12,7,8,9,4,5,6,1,2,3}
    or  {9,10,11,12,5,6,7,8,1,2,3,4} ?

Choose period P
# iters: I = 1 + (N-1)/P

Answer: max(I, P)
/*

k <= n/2
*/

void run() {
    int n = 100;
    vector<vector<int>> tbl(n+1, vi(n+1,-1)); // store period P to achieve n,k
    rep(i,1,n+1) {
        rep(P,1,n+1) {
            int I = 1 + (i-1)/P;
            int ans = max(I,P);
            tbl[i][ans] = P;
        }
    }

    int t; cin >> t;
    rep(i,0,t) {
        int a,b; cin >> a >> b;
        if (tbl[a][b] == -1) {
            print("IMPOSSIBLE");
            continue;
        }
        int P = tbl[a][b];
        vi seq(a);
        int I = (a-1)/P;
        int ctr = 1;
        rep(j,0,I) {
            rep(k,0,P) {
                seq[a-P-P*j+k] = ctr++;
            }
        }
        rep(j,0,a) {
            if (ctr > a) break;
            seq[j] = ctr++;
        }
        rep(j,0,a) cout << seq[j] << ' ';
        cout << '\n';
    }

}


// void run() {
//     int n,k; cin >> n >> k;
//     if (k > n/2) {
//         vi ans(n);
//         rep(i,1,k) ans[i-1]=i;
//         rep(i,0,n-k+1) {
//             ans[n-1-i] = k+i;
//         }
//         rep(i,0,n) cout << ans[i] << ' ';
//         cout << '\n';
//         return;
//     }
// }

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