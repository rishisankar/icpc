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

bool onBorder(pii pos, int n, int m) {
    return pos.F == 0 || pos.S == 0 || pos.F == n-1 || pos.S == m-1;
}

void run() {
    int n,m; cin >> n >> m;
    vector<vector<bool>> graph(n, VB(m)); // false for all walls
    vector<VVB> blocked(2, VVB(n,VB(m, false)));
    pii start;
    queue<pii> mq, pq;
    rep(i,0,n) {
        string s; cin >> s;
        rep(j,0,m) {
            graph[i][j] = (s[j] == '#' ? false : true);
            if (s[j] == 'A') start = {i,j};
            if (s[j] == 'M') {
                mq.push({i,j});
                blocked[0][i][j] = true;
            }
        }
    }
    if (onBorder(start,n,m)) { // edge case: already on border
        print("YES");
        print(0);
        return;
    }
    int T = 0;
    pq.push(start);
    VVB vis(n,VB(m,false));
    vis[start.F][start.S] = true;
    vector<vector<pii>> par(n, vector<pii>(m,{-2,-2}));
    par[start.F][start.S] = {-1,-1};
    while (!pq.empty()) {
        // first figure out all places that will be blocked by monsters in the next iter
        int amt = mq.size();
        int TN = (T+1)%2;
        rep(i,0,amt) {
            pii mons = mq.front(); mq.pop();
            for (pii d : dirs) {
                int x = mons.F+d.F;
                int y = mons.S+d.S;
                if (x<0 || y<0 || x>=n || y>=m || !graph[x][y]) continue;
                if (blocked[TN][x][y]) continue;
                blocked[TN][x][y] = true;
                mq.push({x,y});
            }
        }
        // next try bfs for the player
        amt = pq.size();
        rep(i,0,amt) {
            pii pos = pq.front(); pq.pop();
            for (pii d : dirs) {
                int x = pos.F+d.F;
                int y = pos.S+d.S;
                if (x<0 || y<0 || x>=n || y>=m || !graph[x][y]) continue;   
                if (vis[x][y]) continue;
                if (blocked[TN][x][y] || blocked[T][x][y]) continue;
                if (onBorder({x,y},n,m)) {
                    print("YES");
                    vector<pii> path;
                    pii cur = {x,y};
                    par[x][y] = pos;
                    while (cur != start) {
                        path.push_back(cur);
                        cur = par[cur.F][cur.S];
                    }
                    path.pb(start);
                    reverse(all(path));
                    print(path.size()-1);
                    rep(i,0,path.size()-1) {
                        pii dif = {path[i+1].F-path[i].F,path[i+1].S-path[i].S};
                        if (dif == mp(1,0)) cout << "D";
                        else if (dif == mp(-1,0)) cout << "U";
                        else if (dif == mp(0,1)) cout << "R";
                        else cout << "L";
                    }
                    cout << '\n';
                    return;
                }
                vis[x][y] = true;
                pq.push({x,y});
                par[x][y] = pos;
            }
        }
        T=TN;
    }
    print("NO");
    
}

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