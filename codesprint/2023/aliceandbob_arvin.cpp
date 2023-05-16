#include <bits/stdc++.h>

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
#define MAXN 200005
#define MODULO 1000000007
typedef long long ll;
typedef long double ld;
using namespace std;


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


// testing tool:
const bool TEST_MODE = true;
const ll inf = 1000000000000000000LL;
const int G = 421 - 2; // # type 1 queries
const int LIE = 13; 
const int numBits = 2000;
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
    // x = inf-1-x;
    if (TEST_MODE) return q2_test(x);
    print(2,x); cout.flush();
    string ans; cin >> ans;
    return ans;
}

bool q1(ll a, ll b) {
    if (a==b) return q2(a) == "EQUAL";
    // swap(a,b); a=inf-1-a; b=inf-1-b;
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




// arvin code:



const ll maxB = ((ll)1e18) - 1;
const ll const_half = (maxB + 1) / 2;
const double lying = ((double)	 1 / 13);
const double truth = ((double) 12 / 13);
void renorm(vector<tuple<ll, ll, double>> &v) {
	double prob = 0;
	for (auto interv : v) {
		ll s = get<0>(interv);
		ll e = get<1>(interv);
		double p = get<2>(interv);
		prob += p * (e - s + 1);
	}
	double fact = (maxB + 1) / prob;
	vector<tuple<ll, ll, double>> res;
	for (auto interv : v) {
		ll s = get<0>(interv);
		ll e = get<1>(interv);
		double prob = get<2>(interv);
		res.push_back( { s, e, prob * fact });
	}
	swap(v, res);
}
void run() {
		vector<tuple<ll, ll, double>> probs;
		//probs sum up to 1e18
		probs.push_back( { 0, maxB, 1 });
		for (ll query = 0; query < 200; query++) {
			ll median = 0;
			ld cumulative_prob = 0;
			for (auto interv : probs) {
				ll s = get<0>(interv);
				ll e = get<1>(interv);
				double prob = get<2>(interv);
				if (cumulative_prob <= const_half
						&& cumulative_prob + (e - s + 1) * prob >= const_half) {
					median = s + floor((const_half - cumulative_prob) / prob);
				}
				cumulative_prob += (e - s + 1) * prob;
			}
			if (query % 2 == 0) {
				median = min(maxB, median + 1);
			}
      bool res = q1(median, maxB);
			double curr_prob = (res) ? lying : truth;

			vector<tuple<ll, ll, double>> new_probs;
			//multiply [median, maxB] by curr_prob
			//multiply [0, median-1] by (1-curr_prob)

			for (auto interv : probs) {
				ll s = get<0>(interv);
				ll e = get<1>(interv);
				double prob = get<2>(interv);
				if (s <= median && median <= e) {
					if (s <= median - 1)
						new_probs.push_back(
								{ s, median - 1, prob * (1 - curr_prob) });
					new_probs.push_back( { median, e, prob * curr_prob });
				} else if (median < s) {
					new_probs.push_back( { s, e, prob * curr_prob });
				} else {
					new_probs.push_back( { s, e, prob * (1 - curr_prob) });
				}
			}
			renorm(new_probs);
			swap(new_probs, probs);
		}
		ld max_prob = 0;
		ll bit_diff = 0;
		for (auto interv : probs) {
			ll s = get<0>(interv);
			ld prob = get<2>(interv);
			if (prob > max_prob) {
				bit_diff = s;
				max_prob = prob;
			}
		}
    string res = q2(bit_diff);
    guess(res);
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
