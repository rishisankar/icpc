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
const int G = 175 - 2; // # type 1 queries
const int LIE = 13; 
const int numBits = 2000;
const bool TEST_MODE = true;

// testing tool:
bool marioWin;
vector<ull> diffs;
VB marioHigher;
int guessesMade;
bool correct;
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

bool q1_test(ll a, ll b) {
    ++guessesMade; assert(!correct);
    int i1 = (lower_bound(all(diffs),a))-diffs.begin();
    int i2 = (upper_bound(all(diffs),b))-diffs.begin();
    bool isEq = (i1==i2);
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;
    if (distr(eng) % LIE == 4) isEq ^= 1;
    return isEq;
}

string q2_test(ll x) {
    ++guessesMade; assert(!correct);
    auto it = lower_bound(all(diffs), x);
    if (it == diffs.end() || (*it) != x) return "EQUAL";
     if (!marioHigher[(it-diffs.begin())]) return "LUIGI";
    else return "MARIO";
}

void guess_test(string ans) {
    ++guessesMade; correct=false;
    if (guessesMade > G+2) {
        return;
    }
    if ((ans == "MARIO" && marioWin) || (ans == "LUIGI" && !marioWin)) {
        correct = true;
    }
}

string q2(ll x) {
    x = inf-1-x;
    if (TEST_MODE) return q2_test(x);
    print(2,x); cout.flush();
    string ans; cin >> ans;
    return ans;
}

bool q1(ll a, ll b) {
    if (a==b) return q2(a) == "EQUAL";
    swap(a,b); a=inf-1-a; b=inf-1-b;
    if (TEST_MODE) return q1_test(a,b);
    print(1,a,b); cout.flush();
    string ans; cin >> ans;
    return ans == "YES";
}

void guess(string ans) {
    if (TEST_MODE) return guess_test(ans);
    print("!", ans);
    cout.flush();
}

/*
for each guess
- let s = first val s.t. P(first diff bit in [0,SP]) >= 0.5
- possible guesses
    - [0,s] tries to eliminate [s+1,inf]
    - [0, s-1] tries to eliminate [0,s-1]


probability container stores {starting point, probability} (goes til next / inf-1)
operations needed:
- compute probability
- find s
- update based on guess

indexing 0 leftmost, reverse in queries

save(x, eq) {
    query [0,x]
    if equal: first diff bit not in first part
    else: first diff in first part
    bayes rule
    P(i being FDB : eq) = P(eq : i being FDB) * P(i being FDB) / P(eq)
}
*/

struct PC {
    vector<pair<ll,ld>> pc{{0,1.L/inf},{inf,0}};

    // return first val s.t. P(first diff bit in [0,SP]) >= 0.5
    ll getS() {
        ld cump = 0;
        rep(i,0,sz(pc)-1) {
            ld extra = pc[i].S * (pc[i+1].F-pc[i].F);
            if (cump + extra >= 0.5) {
                // split point somewhere here
                // cump + pc[i].S * z >= 0.5
                ll quant = (0.5-cump)/pc[i].S;
                // in case of precision issues...
                while (cump + pc[i].S * quant < 0.5) ++quant;
                while (cump + pc[i].S * (quant-1) >= 0.5) --quant;
                assert(1 <= quant && quant <= pc[i+1].F-pc[i].F);
                return pc[i].F - 1 + quant;
            }
            cump += extra;
        }
        assert(false);
        return -1; // shouldn't get here
    }

    // get probability of first diff bit in range [s,f]
    ld prange(ll s, ll f) {
        if (s>f) return 0;
        ld p = 0;
        rep(i,0,sz(pc)-1) {
            if (s < pc[i+1].F && f >= pc[i].F) {
                ll start = max(pc[i].F, start);
                ll fin = min(pc[i+1].F-1, f);
                p += pc[i].S * (fin-start+1);
            }
        }
        return p;
    }

    // add p to container if not already there
    void addPoint(ll p) {
        rep(i,0,sz(pc)) {
            if (pc[i].F == p) return;
            else if (pc[i].F > p) {
                pc.insert(pc.begin()+i, {p, pc[i-1].S});
                return;
            }
        }
    }

    // update probability after a query [0,x]
    void save(ll x, bool is_eq) {
        // first, add x+1 as a point if doesn't exist yet
        addPoint(x+1);
        // then compute using bayes rule
        // ex: P(i being FDB : query gives eq) = P(query gives eq : i being FDB) * P(i being FDB) / P(query gives eq)
        ld p_lie = 1/(ld)LIE;
        // ld p_diff = prange(0,x);
        // ld Peq = p_lie * p_diff + (1-p_lie) * (1-p_diff); // chance of query coming back as equal
        // rep(i,0,sz(pc)-1) {
        //     if (pc[i].F <= x) {
        //         // first half
        //         if (is_eq) pc[i].S = p_lie * pc[i].S / Peq;
        //         else pc[i].S = (1-p_lie) * pc[i].S / (1-Peq);
        //     } else {
        //         // second half
        //         if (is_eq) pc[i].S = (1-p_lie) * pc[i].S / Peq;
        //         else pc[i].S = p_lie * pc[i].S / (1-Peq);
        //     }
        // }
        rep(i,0,sz(pc)-1) {
            if (pc[i].F <= x) {
                if (is_eq) pc[i].S *= p_lie;
                else pc[i].S *= (1-p_lie);
            } else {
                if (is_eq) pc[i].S *= (1-p_lie);
                else pc[i].S *= p_lie;
            }
        }
        renorm();
    }

    // get bit position with max probability
    ll getMax() {
        int bi = 0; ld bp = pc[0].S;
        rep(i,1,sz(pc)-1) {
            if (pc[i].S > bp) {
                bi = i;
                bp = pc[i].S;
            }
        }
        // dbg(pc[bi].S, pc[bi+1].F-pc[bi].F);
        return pc[bi].F;
    }

    void renorm() {
        ld cump = prange(0,inf-1);
        rep(i,0,sz(pc)-1) pc[i].S /= cump;
    }
};

void run() {
    PC pc;
    rep(_,0,G) {
        ll s = pc.getS();
        ll qp;
        if (s == 0) qp = s;
        else qp = (rand()&1 ? s : s-1);
        pc.save(qp, q1(0, qp));
        // ld p1 = pc.prange(s+1,inf), p2 = pc.prange(0,s-1);
        // pc.save(s,q1(0,s));
        // pc.save(s,q1(0,s-1));
    }
    string ans = q2(pc.getMax());
    if (ans == "EQUAL") ans = ((rand()&1) ? "MARIO" : "LUIGI"); // choose randomly in case we fail
    guess(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (TEST_MODE) {
        srand((unsigned) time(0));
        int sm = 0, i = 0;
        while (true) {
            if (i%1000==0) cout << sm << " / " << i << endl;
            gen();
            run();
            if (!correct) {
                print("error", guessesMade, marioWin);
                cout.flush();
            }
            sm += correct;
            i++;
        }
    } else {
        ll t; cin >> t;
        rep(tests,0,t) run();
    }
}