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
 
void run() {
    int n,m; cin >> n >> m;
    vector<vector<bool>> graph(n, VB(m));
    pii start,end;
    rep(i,0,n) {
        string s; cin >> s;
        rep(j,0,m) {
            graph[i][j] = (s[j] == '#' ? false : true);
            if (s[j] == 'A') start = {i,j};
            if (s[j] == 'B') end = {i,j};
        }
    }
    vector<vector<pii>> par(n, vector<pii>(m, mp(-2,-2)));
    par[start.F][start.S]={-1,-1};
    queue<pii> s;
    s.push(start);
    while (!s.empty()) {
        pii t = s.front(); s.pop();
        for (pii d : dirs) {
            int x = d.F+t.F; int y = d.S+t.S;
            if (x < 0 || y < 0 || x >= n || y >=m || !graph[x][y] || par[x][y].F>=-1) continue;
            s.push({x,y});
            par[x][y] = t;
        }
    }
    if (par[end.F][end.S].F==-2) {
        print("NO");
        return;
    }
    pii cur = end;
    vector<pii> pos;
    while(cur != start) {
        pos.pb(cur);
        cur = par[cur.F][cur.S];
    }
    pos.pb(start);
    reverse(pos.begin(),pos.end());
    print("YES");
    print(pos.size()-1);
    rep(i,0,pos.size()-1) {
        pii dif = {pos[i+1].F-pos[i].F,pos[i+1].S-pos[i].S};
        if (dif == mp(1,0)) cout << "D";
        else if (dif == mp(-1,0)) cout << "U";
        else if (dif == mp(0,1)) cout << "R";
        else cout << "L";
    }
    cout << '\n';
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