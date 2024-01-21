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
#define trav(a, x) for(auto& a : x)
VPII dirs{mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};
const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;
// const ll mod = 998244353;
const int MOD = 1000000000 + 7;
int K;

struct trie{
  trie *child[2];
  bool is_end;
  vi leaves;
};

trie *new_node()
{
  trie *temp=new trie;
  temp->child[0]=NULL;
  temp->child[1]=NULL;
  temp->is_end=false;
  return temp;
}

void insert(trie *root,int pos, int x)
{
  trie *temp=root;
  int index;
  for(int i=31;i>=0;i--)
  {
    temp->leaves.pb(pos);
    if(x&(1<<i))
      index=1;
    else
      index=0;
    if(temp->child[index]==NULL)
     temp->child[index]=new_node();

    temp=temp->child[index];
  }
  temp->leaves.pb(pos);
  temp->is_end=true;
}

void step(trie *root, int idx, int x, vi &ans)
{
  trie *temp=root;
  int index;
  for(int i=31;i>=0;i--)
  {
    if((K&(1<<i))) // gotta do some deletes
    {
      if(x&(1<<i)) // delete all left
      {
        if(temp->child[1]!=NULL)
        {
          trav(a,temp->child[1]->leaves)
          ans[a]=min(ans[a],idx);
          temp->child[1]=NULL;
        }
      }
      else // delete all right
      {
        if(temp->child[0]!=NULL)
        {
          trav(a,temp->child[0]->leaves)
          ans[a]=min(ans[a],idx);
          temp->child[0]=NULL;
        }
      }
    }

    int y=x^K;
    if(y&(1<<i))
      index=1;
    else
      index=0;
    if(temp->child[index]==NULL) break;
    temp=temp->child[index];
  }
}

// return vector ans(n)  s.t. ans[i] = min j>i s.t arr[i]^arr[j] < k (or -1 if none exist)
vector<int> go(vector<int>& arr, int n) {
  trie* root= new_node();
  vi ans(n,MOD);
  rep(i,0,n)
  {
    step(root,i,arr[i],ans);
    insert(root,i,arr[i]);
  }

  rep(i,0,n) if(ans[i]==MOD) ans[i]=-1;
  return ans;
}

// return vector ans(n)  s.t. ans[i] = min j>i s.t arr[i]^arr[j] > k (or -1 if none exist)
void solve(vector<int>& arr, int n, ll k) {
    VLL v(n,-1);
    rep(i,0,n) {
        rep(j,i+1,n) {
            if ((arr[i] ^ arr[j]) < k) {
                dbg(i,j,arr[i]^arr[j], arr[i], arr[j], k);
                v[i] = j;
                break;
            }
        }
    }
    dbg("intended", v); 
}

void run() {
    int n; ll k; cin >> n >> k;
    vector<int> v(n); INP(v,n);
    // vector<ll> gr = solve(v,n,k);
    K = k ;
    vector<int> gr = go(v,n);
    // solve(v,n,k);
    unordered_map<ll, int> zz;
    vector<ll> kpr(n, -1);
    for (int i = n-1; i >= 0; --i ) {
        ll tgt = k ^ v[i];
        auto it = zz.find(tgt);
        if (it != zz.end()) {
            kpr[i] = it->second;
        }
        zz[v[i]] = i;
    }
    dbg(gr);
    dbg(kpr);

    //  for each index i, largest range starting at i where all xors are <= k
    vector<int> ind1(n);
    multiset<int> problem_indices;
    problem_indices.insert(n);
    int j = 0;
    if (gr[0] != -1) problem_indices.insert(gr[0]);
    for (int i = 0; i < n; ++i) {
        while (j < *(problem_indices.begin())) {
            ++j;
            if (gr[j] != -1) problem_indices.insert(gr[j]);
        }
        ind1[i] = j-1;
        if (gr[i] != -1) problem_indices.erase(problem_indices.find(gr[i]));
    }
    dbg(ind1);

    // for each index i, first index j where xor of k exists in interval [i,j]
    vi ind2(n); 
    multiset<int> valid_end;
    valid_end.insert(n);
    for (int i = n-1; i >= 0; --i) {
        if (kpr[i] != -1) valid_end.insert(kpr[i]);
        ind2[i] = *(valid_end.begin());
    }
    dbg(ind2);

    ll ans = 0;
    rep(i,0,n) {
        if (ind2[i] == n) break;
        if (ind1[i] >= ind2[i]) {
            ans += (ind1[i] - ind2[i] + 1);
        }
    }

    print(ans);

}
/*
for each index i, largest range starting at i where all xors are <= k
for each index i, first index where xor of k exists

*/

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