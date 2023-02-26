#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define REP(i, j) FOR(i, 0, j)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
#define F first
#define S second
#define INP(v, n) for (int i=0; i<n; ++i) { cin >> v[i]; }
#define ceil(x) (ll)ceil(x)
#define floor(x) (ll)floor(x)

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cerr << vec[i] << ' ';
    }
    cerr << '\n';
    cerr << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cerr << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cerr << vec[i][j] << ' ';
        }
        cerr << '\n';
    }
    cerr << "########\n";
}

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
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

const ld pi = 3.1415926535897932384626433832795;
const ll mod = 1000000007;

/*

everything in v1 connected by roads
everything in v2 not connected by roads
no connection between last element in v1, last element in v2

to insert a node n (given lv1, lv2):
  1) if connected by road to v1:
    add n to v1
    if lv2 connected to n, move lv2 to v1
  2) if not connected by road to v1
    a) if not connected by road to lv2
        add n to v2
    b) if connected by road to lv2
        move lv1 to v2
        if connected to new of v1, add n to v1
        else add n to v2

need to make sure we start at 1

*/

int n, m;
vector<unordered_set<int>> adj;

int get1(deque<int>* v) {
    int t = v->front();
    v->pop_front();
    int t2 = v->front();
    v->push_front(t);
    return t2;
}

void run() {
    cin >> n >> m;
    adj.resize(n);
    rep(i,0,m) {
        int a,b; cin >> a >> b;
        --a; --b;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    deque<int> v1d, v2d;
    deque<int>* v1 = &v1d;
    deque<int>* v2 = &v2d;
    // mid = last node in v1
    v1->PB(0);
    rep(i,1,n) {
        if (v2->size() == 0) {
            if (v1->size() >= 2) {
                if (adj[0].count(get1(v1))) {
                    // v1 connected by roads
                    if (adj[v1->back()].count(i)) v1->PB(i);
                    else v2->push_front(i);
                } else {
                    //v1 not connected by roads
                    if (adj[v1->back()].count(i)) v2->push_front(i);
                    else v1->PB(i);
                }
            } else v1->PB(i);
        } else {
            // v2 size > 0 (can assume v1 size >= 2 else would have merged)
            int mid = v1->back();
            if (adj[0].count(get1(v1))) {
                // v1 connected by roads
                if (adj[mid].count(i)) {
                    v1->PB(i);
                    if (adj[i].count(v2->front())) {
                        v1->PB(v2->front());
                        v2->pop_front();
                    }
                }
                else {
                    v1->pop_back();
                    v2->push_front(mid);
                    if (adj[v1->back()].count(i)) v1->PB(i);
                    else v2->push_front(i);
                }
            } else {
                // v1 not connected by roads
                if (!(adj[mid].count(i))) {
                    v1->PB(i);
                    if (!(adj[i].count(v2->front()))) {
                        v1->PB(v2->front());
                        v2->pop_front();
                    }
                } else {
                    v1->pop_back();
                    v2->push_front(mid);
                    if (!(adj[v1->back()].count(i))) v1->PB(i);
                    else v2->push_front(i);   
                }
            }
        }

        // merge if v1 size is 1
        if (v1->size() == 1) {
            assert(v1->front() == 0);
            v1->clear();
            v2->push_front(0);
            swap(v1,v2);
        }
    }

    while (v1->size() > 0) {
        cout << (v1->front()+1) << " ";
        v1->pop_front();
    }
    while (v2->size() > 0) {
        cout << (v2->front()+1) << " ";
        v2->pop_front();
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(15);
    // ll t; cin >> t;
    ll t=1;
    REP(tests,t) run();
}