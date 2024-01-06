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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;

void run() {
    string s; cin >> s;
    vi start(7);
    vector<int> cts(8), indeck(8);
    rep(i,0,7) {
        if (s[i] == 'A') start[i] = 0;
        else if (s[i] >= '2' && s[i] <= '7') start[i] = (s[i] - '1');
        else start[i] = 7;
    }
    rep(i,0,7) cts[start[i]]++;
    rep(i,0,7) indeck[i] = 4 - cts[i];
    indeck[7] = 24 - cts[7];
    vector<int> ord;
    rep(i,0,7) ord.pb(i);
    int bad = 7;
    rep(i,0,7) {
        if (cts[i] == 4) bad = i;
    }
    ld ans = 0;
    do {
        // first, check if this ord is even possible
        bool valid = 1;
        vector<bool> isFlipped(7);
        vi seq;
        vi cards;
        int x = 0;
        while (x < 7) {
            // can't wait for a card not in deck
            if (indeck[ord[x]] == 0) {
                valid = 0;
                break;
            }
            isFlipped[ord[x]] = 1;
            seq.pb(ord[x]);
            cards.pb(indeck[ord[x]]);
            while (start[ord[x]] != 7 && (!isFlipped[start[ord[x]]])) {
                if (start[ord[x]] != ord[x+1]) {
                    valid = 0;
                    break;
                } else {
                    x++;
                    isFlipped[ord[x]] = 1;
                    cards[sz(cards)-1] += indeck[ord[x]];
                }
            }
            if (!valid) break;
            x++;
        }
        if (!valid) continue;

        int N = sz(seq);
        vi cavail(N+1);
        cavail[0] = indeck[7];
        rep(i,1,N+1) cavail[i] = cavail[i-1] + cards[i-1];

        vector<vector<ld>> dp(N+1, vector<ld>(46));
        dp[0][0] = 1;
        rep(i,0,N+1) {
            rep(j,1,46) {
                dp[i][j] += dp[i][j-1] * (cavail[i] - (j-1));
                if (i != 0) {
                    dp[i][j] += dp[i-1][j-1] * indeck[seq[i-1]];
                }
                dp[i][j] /= (46-j);
            }
        } 
        rep(T, 1, 46) {
            ld z = dp[N-1][T-1]; // arrange everyting except last part of seq in first T-1 things
            z *= indeck[seq[N-1]];
            z /= (46-T);
            ans += T * z;
        }

    } while (next_permutation(all(ord)));
    dbg(start);
    print(ans);
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