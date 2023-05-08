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

/*
// testing tool
bool marioWin;
vector<ull> onesM, onesL;
int guessesMade;
bool correct;

void gen() {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;
    set<ull> locss;
    rep(i,0,1000) locss.insert(distr(eng) % inf);
    onesM.clear();
    for (ull u : locss) onesM.pb(u);
    locss.clear();
    rep(i,0,1000) locss.insert(distr(eng) % inf);
    onesL.clear();
    for (ull u : locss) onesL.pb(u);
    int i = 0;
    for (; i < min(sz(onesM), sz(onesL)); ++i) {
        if (onesM[sz(onesM)-1-i] > onesL[sz(onesL)-1-i]) {
            marioWin = true; break;
        } else if (onesM[sz(onesM)-1-i] < onesL[sz(onesL)-1-i]) {
            marioWin = false; break;
        }
    }
    dbg(marioWin);
    dbg(i);
    dbg(onesM[sz(onesM)-1-i], onesL[sz(onesL)-1-i]);
    guessesMade = 0;
    correct = false;
}

string q1(ll a, ll b) {
    ++guessesMade; assert(!correct);
    auto it = upper_bound(all(onesM), b);
    auto it2 = upper_bound(all(onesL), b);
    int i1 = (it-onesM.begin())-1;
    int i2 = (it2-onesL.begin())-1;
    bool isEq = true;
    while (i1 >= 0 && i2 >= 0 && onesM[i1] >= a && onesL[i2] >= a) {
        if (onesM[i1] != onesL[i2]) isEq = false;
        --i1;
        --i2;
    }
    if (i1 != -1 && onesM[i1] >= a) isEq = false;
    if (i2 != -1 && onesL[i2] >= a) isEq = false;
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;
    if (distr(eng) % 13 == 4) isEq ^= 1;
    if (isEq) return "YES";
    else return "NO";
}

string q2(ll x) {
    ++guessesMade; assert(!correct);
    auto it = lower_bound(all(onesM), x);
    auto it2 = lower_bound(all(onesL), x);
    if (it == onesM.end() && it2 == onesL.end()) return "EQUAL";
    dbg(x, *it, *it2);
     if (it == onesM.end() && (*it2) == x) return "LUIGI";
    else if (it2 == onesL.end() && (*it) == x) return "MARIO";
    else return "EQUAL";
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
    print(1,a,b); cout.flush();
    string ans; cin >> ans;
    return ans;
}

string q2(ll x) {
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
        string ans = q2(pos);
        if (ans != "EQUAL") return false;
    }
    return true;
}

const int K = 5;
bool query(ll a, ll b) {
    if (b-a+1 <= 7) return smallQuery(a,b);
    vi answers{-2};
    rep(i,0,K-1) answers.pb(-1);
    while (true) {
        string ans = q1(a,b);
        answers.pb(ans == "YES");
        bool done = true;
        rep(i,0,K-1) {
            if (answers[sz(answers)-1-i] != answers[sz(answers)-2-i]) done=false;
        }
        if (done) break;
    }
    return answers[sz(answers)-1];
}

void run() {
    ll lo = 0, hi = inf;
    while (lo < hi) {
        ll mid = lo + (hi-lo)/2;
        bool iseq = query(mid+1, hi);
        if (iseq) hi = mid;
        else lo = mid+1;
    }
    string ans = q2(lo);
    guess(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t; cin >> t;
    rep(tests,0,t) run();

    // int sm = 0;
    // rep(i,0,250) {
    //     gen();
    //     run();
    //     sm += correct;
    // }
    // print(sm);
}