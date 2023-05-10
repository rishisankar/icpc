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
typedef pair<ll, ll> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

const int MOD = 1000000000 + 7;
const ll N=1000000000000000000;

ll num_queries;

//testing tool
bool marioWin;
vector<ull> diffs;
vector<bool> marioHigher;
int guessesMade;
bool correct;
const int numBits = 2000;
std::random_device rd;
std::mt19937_64 eng(rd());
std::uniform_int_distribution<unsigned long long> distr;
void gen() {
    set<ull> locss;
    marioHigher.clear();
    rep(i,0,numBits) {
        ull z = distr(eng)%N;
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

bool query(ll l, ll r) {
    --num_queries;
    ll a = N-1-r, b = N-1-l;
    ++guessesMade; assert(!correct);
    int i1 = (lower_bound(all(diffs),a))-diffs.begin();
    int i2 = (upper_bound(all(diffs),b))-diffs.begin();
    bool isEq = (i1==i2);
    if (distr(eng) % 12 == 4) isEq ^= 1;
    return isEq;
}

bool ask(ll x) {
    --num_queries;
    x = N-1-x;
    ++guessesMade; assert(!correct);
    auto it = lower_bound(all(diffs), x);
    if (it == diffs.end() || (*it) != x) return false;
    if (!marioHigher[(it-diffs.begin())]) return false;
    else return true;
}

void answer(string ans) {
    ++guessesMade; correct=false;
    if (guessesMade > 421) {
        return;
    }
    if ((ans == "MARIO" && marioWin) || (ans == "LUIGI" && !marioWin)) {
        correct = true;
    }
}


/*
bool query(ll l, ll r)
{
  cout<<"1"<<" "<<N-r-1<<" "<<N-l-1<<endl;
  string s;
  cin>>s;
  return (s=="YES");
}

bool ask(ll x)
{
  cout<<"2"<<" "<<N-x-1<<endl;
  string s;
  cin>>s;
  return (s=="MARIO");
}

void answer(string s)
{
  cout<<"!"<<" "<<s<<endl;
  return;
}
*/

void solve()
{
  ll l=0,r=N-1;
  stack<pii> s;
  num_queries=418;
  while(num_queries>=2)
  {
    dbg(num_queries,l,r);
    // num_queries-=2;
    if(!((l==0 || query(0,l-1)) && !query(l,r)))// backtrack
    {
      if(!s.empty())
      {
        pii x=s.top();
        l=x.F, r=x.S;
        s.pop();
      }
      else
      {
        l=0;
        r=N-1;
      }
    }

    //   num_queries-=1;
      s.push({l,r});
      ll mid=(l+r)/2;
      if(query(l,mid))
      {
        l=min(mid+1,r);
      }
      else
      {
        r=mid;
      }

  }
  answer(ask(l)?"MARIO":"LUIGI");
}


int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
//   ll t;
//   cin>>t;
//   rep(i,0,t)
//     solve();

    srand((unsigned) time(0));
    int sm = 0, i = 0;
    while (true) {
        if (i%1000==0) cout << sm << " / " << i << endl;
        gen();
        solve();
        if (!correct) {
            print("error", i, guessesMade, marioWin);
            cout.flush();
        }
        sm += correct;
        i++;
    }

}