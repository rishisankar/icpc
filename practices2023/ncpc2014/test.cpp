#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i <(b); i++)
#define trav(a, x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define F first
#define S second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v)
{ os << '{'; string sep; for (const auto &x: v) os << sep << x, sep = ", "; return os << '}';}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p)
{ return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T)
{ cerr << ' ' << H; dbg_out(T...); }

#ifdef TTL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
const int MOD = 1e9+7;


// Return a uniformly distributed random int from min to max, inclusive
// inline
// int randInt(int min, int max)
// {
// 	static std::random_device rd;
// 	static std::default_random_engine generator(rd());
// 	std::uniform_int_distribution<> distro(min, max);
// 	return distro(generator);
// }

void solve() {
    int k, n;
    cin >> k >> n;
    if(n >= 90) {
        cout << "possible" << endl;
        return;
    }
    if (k > n) {
      cout << "impossible\n";
      return;
    }
    vector<pii> nodesByDeg;
    bool adjp[n+1][n+1];
    memset(adjp, 0, sizeof(adjp));
    int d, a;
    rep(i, 1, n+1) {
        cin >> d;
        rep(j, 0, d) {
            cin >> a;
            adjp[i][a] = 1;
        }
        nodesByDeg.pb({d, i});
    }
    sort(all(nodesByDeg));
    vector<bool> pickable(n+1, true);
    for (auto p : nodesByDeg) {
      if (p.F >= 2) break;
      if (!pickable[p.S]) continue;
      pickable[p.S] = false;
      rep(i,1,n+1) {
        if (adjp[p.S][i]) pickable[i] = false;
      }
      --k;
    }
    int np = 1;
    map<int,int> ntoi;
    rep(i,1,n+1) {
      if (pickable[i])ntoi[i] = np++;
    }
    vector<vector<bool>> adj(np, vector<bool>(np));
    rep(i,1,n+1) {
      rep(j,1,n+1) {
        if (!pickable[i] || !pickable[j]) continue;
        adj[ntoi[i]][ntoi[j]] = adj[ntoi[j]][ntoi[i]] = adjp[i][j];
      }
    }
    n = np-1;
    
    if (k <= 0) {
      cout << "possible\n";
      return;
    }
    dbg("r1");
    dbg(adj);
    // rng time
    rep(m_i, 0, 1000000) {
        bool ok = true;
        map<int, int> pick;
        vector<int> nums;
        rep(i, 0, k) {
            // int x = randInt(1, n-i);
            int x = (rand() % (n-i)) + 1;
            if (pick.count(x)) {
              int t = pick[x];
              if(pick.count(n-i)) {
                pick[x] = pick[n-i];
              } else {
                pick[x] = n-i;
              }
              x = t;
            } else {
                pick[x] = (pick.count(n-i) ? pick[n-i] : (n-i));
            }
            for(int &y: nums) {
                if(adj[x][y]) {
                    ok = false;
                    break;
                }
            }
            if(!ok) break;
            nums.pb(x);
        }
        if(ok) {
          // verify
          dbg(nums);
          unordered_set<int> s_nums; 
          rep(t,0,nums.size()) {
            rep(t2,t+1,nums.size()) {
              assert(!adj[nums[t]][nums[t2]]);
            }
          }
            cout << "possible" << endl;
            return;
        }
    }
    cout << "impossible" << endl;
}

int main()
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  solve();
}


