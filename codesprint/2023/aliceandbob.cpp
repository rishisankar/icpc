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
const ll inf = 1000000000000000000LL;

int numQueries;
const int MAXQ = 419;

/*
//testing tool
bool marioWin;
vector<ull> diffs;
VB marioHigher;
int guessesMade;
bool correct;
const int numBits = 200000;
void gen() {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;
    set<ull> locss;
    marioHigher.clear();
    rep(i,0,numBits) {
        ull z = distr(eng)%inf;
        marioHigher.pb(z&1);
        locss.insert(z>>1);
    }
    diffs.clear();
    for (ull u : locss) diffs.pb(u);
    marioHigher.resize(sz(diffs));
    marioWin = marioHigher[sz(marioHigher)-1];
    guessesMade = 0;
    correct = false;
}

string q1(ll a, ll b) {
    ++numQueries;
    ++guessesMade; assert(!correct);
    int i1 = (lower_bound(all(diffs),a))-diffs.begin();
    int i2 = (upper_bound(all(diffs),b))-diffs.begin();
    bool isEq = (i1==i2);
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;
    if (distr(eng) % 13 == 4) isEq ^= 1;
    if (isEq) return "YES";
    else return "NO";
}

string q2(ll x) {
    ++numQueries;
    ++guessesMade; assert(!correct);
    auto it = lower_bound(all(diffs), x);
    if (it == diffs.end() || (*it) != x) return "EQUAL";
     if (!marioHigher[(it-diffs.begin())]) return "LUIGI";
    else return "MARIO";
}

void guess(string ans) {
    dbg(guessesMade);
    ++guessesMade; correct=false;
    if (guessesMade > 421) {
        return;
    }
    if ((ans == "MARIO" && marioWin) || (ans == "LUIGI" && !marioWin)) {
        correct = true;
    }
}
*/

string q1(ll a, ll b) {
    ++numQueries;
    print(1,a,b); cout.flush();
    string ans; cin >> ans;
    return ans;
}

string q2(ll x) {
    ++numQueries;
    print(2,x); cout.flush();
    string ans; cin >> ans;
    return ans;
}

void guess(string ans) {
    print("!", ans);
    cout.flush();
}

bool smallQuery(ll a, ll b) {
    for (ll pos = b; pos >= a; pos--) {
        if (numQueries >= MAXQ) return 0;
        string ans = q2(pos);
        if (ans != "EQUAL") { dbg(ans); return false; }
    }
    return true;
}

const int K = 5;
pair<bool,bool> checkHist(VB& hist) {
    if (sz(hist) < 5) return {0,0};
    if (sz(hist) >= 14) {
        int c0 = 0, c1 = 1;
        for (int i : hist) {
            if (i == 0) ++c0; else ++c1;
        }
        if (c0 > c1) return {1,0}; else return {1,1};
    }
    rep(i,0,K-1) {
        if (hist[sz(hist)-1-i] != hist[sz(hist)-2-i]) return {0,0};
    }
    return {1,hist[sz(hist)-1]};
}

bool query(ll a, ll b) {
    if (b-a+1 <= 7) return smallQuery(a,b);
    VB answers;
    pair<bool,bool> ch = {0,0};
    while (!ch.F) {
        if (numQueries >= MAXQ) return 0;
        string ans = q1(a,b);
        answers.pb(ans == "YES");
        ch = checkHist(answers);
    }
    return ch.S;
}

void run() {
    numQueries = 0;
    ll lo = 0, hi = inf-1;
    while (lo < hi) {
        // dbg(lo,hi);
        ll mid = lo + (hi-lo)/2;
        bool iseq = query(mid+1, hi);
        if (numQueries >= MAXQ) break;
        if (iseq) hi = mid;
        else lo = mid+1;
    }
    dbg("guess");
    string ans = (lo == hi ? q2(lo) : ((rand()&1) ? "YES" : "NO"));
    dbg(ans);
    guess(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand((unsigned) time(0));

    ll t; cin >> t;
    rep(tests,0,t) run();

    // int sm = 0;
    // rep(i,0,250) {
    //     gen();
    //     print("gen"); cout.flush();
    //     run();
    //     print("run"); cout.flush();
    //     if (!correct) {
    //         print("error", guessesMade, marioWin);
    //     }
    //     sm += correct;
    // }
    // print(sm);
}