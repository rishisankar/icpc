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
    string buf, s;
    while(cin >> s) {
        rep(i,0,sz(s)) {
            if (s[i] == '<') buf += ' ';
            buf += s[i];
            if (s[i] == '>') buf += ' ';
        }
        buf += ' ';
    }
    stringstream ss(buf);
    string cur;
    string trash;
    vector<vector<pii>> data(7); // stores {string ind, occurences}
    int day = 0;
    set<pii> store;
    unordered_map<string,int> sidx; // index for each string
    vector<string> rev_sidx;
    vector<int> cts;
    while (ss >> cur) {
        if (cur == "<text>") {
            // text section
            unordered_map<int,int> cgs, cnew;
            // 1) clear stuff from current day
            for (pii p : data[day]) cgs[p.F] = -p.S;
            data[day].clear();
            // 2) read stuff for new day
            while (ss >> s) {
                if (s == "</text>") break;
                if (sz(s) < 4) continue;
                int id;
                if (!sidx.count(s)) {
                    id = sz(sidx);
                    sidx[s] = id;
                    rev_sidx.pb(s);
                    cts.pb(0);
                } else id = sidx[s];
                cnew[id]++;
            }
            for (auto p : cnew) {
                cgs[p.F] += p.S;
                data[day].pb(p);
            }
            day = (day+1)%7;
            // update store based on cgs:
            for (pii p : cgs) {
                // if (cts[p.F] != 0) {
                    auto it = store.find({cts[p.F],p.F});
                    if (it != store.end()) store.erase(it);
                // }
                cts[p.F] += p.S;
                // if (cts[p.F] != 0) {
                    store.insert({cts[p.F],p.F});
                // }
            }
        } else {
            // top section
            int n; ss >> n;
            ss >> trash;
            // answer top n query
            cout << "<top " << n << ">\n";
            auto it = store.rbegin();
            int amt = 0, prev = -1;
            vector<pair<int,string>> sv;
            while (!(it == store.rend())) {
                if (amt >= n && it->F != prev) break;
                amt++;
                sv.pb({it->F, rev_sidx[it->S]});
                prev = it->F;
                advance(it,1);
            }
            sort(all(sv), [&](auto& p1, auto& p2) {
                return (p1.F > p2.F) || (p1.F==p2.F && p1.S < p2.S);
            });
            for (auto& p : sv) {
                print(p.S,p.F);
            }
            print("</top>");
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    rep(tests,0,t) run();
}