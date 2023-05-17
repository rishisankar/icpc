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
bool testPhase;

const int G = 175;


//testing tool
bool marioWin;
vector<ull> diffs;
VB marioHigher;
int guessesMade;
bool correct;
const int numBits = 20;
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
void gen0() {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;
    diffs.clear();
    marioHigher.clear();
    diffs.pb(inf-1);
    marioWin = distr(eng)%2;
    marioHigher.pb(marioWin);
    guessesMade = 0;
    correct = false;
}

string q2(ll x) {
    ++numQueries;
    ++guessesMade; assert(!correct);
    auto it = lower_bound(all(diffs), x);
    if (it == diffs.end() || (*it) != x) return "EQUAL";
     if (!marioHigher[(it-diffs.begin())]) return "LUIGI";
    else return "MARIO";
}

string q1(ll a, ll b) {
    if (numQueries>=G-2-testPhase) return "";
    if (a==b) return q2(a) == "EQUAL" ? "YES" : "NO";
    ++numQueries;
    ++guessesMade; assert(!correct);
    int i1 = (lower_bound(all(diffs),a))-diffs.begin();
    int i2 = (upper_bound(all(diffs),b))-diffs.begin();
    bool isEq = (i1==i2);
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;
    if (distr(eng) % 12 == 4) isEq ^= 1;
    if (isEq) return "YES";
    else return "NO";
}

void guess(string ans) {
    ++guessesMade; correct=false;
    if (guessesMade > G) {
        return;
    }
    if ((ans == "MARIO" && marioWin) || (ans == "LUIGI" && !marioWin)) {
        correct = true;
    }
}


/*
string q1(ll a, ll b) {
    if (numQueries>=G-2-testPhase) return "";
    //if (a==b) return q2(a) == "EQUAL";
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
}*/

void run() {
    numQueries = 0;
    ll lo = 0, hi = inf-1;
    stack<pll> ranges;
    while (numQueries < G-2) {
        testPhase = 1;
        if ((hi != inf-1 && q1(hi+1, inf-1) == "NO") || (lo != 0 && q1(lo, hi) == "YES")) {
            lo = ranges.top().F;
            hi = ranges.top().S;
            ranges.pop();
            continue;
        }
        testPhase = 0;
        ranges.push({lo,hi});
        if (lo < hi) {
            ll mid = lo + (hi-lo)/2;
            if (q1(mid+1, hi) == "YES") hi = mid;
            else lo = mid+1;
        } else if (numQueries == G-3) break;
    }
    guess(q2(hi));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ll t; cin >> t;
    // rep(tests,0,t) run();

    srand((unsigned) time(0));
    int sm = 0, i = 0;
    while (true) {
        if (i%1000==0) cout << sm << " / " << i << endl;
        gen0();
        run();
        if (!correct) {
            print("error", guessesMade, marioWin);
            cout.flush();
        }
        sm += correct;
        i++;
    }
}