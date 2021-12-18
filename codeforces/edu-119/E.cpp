#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i) 
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
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
template<typename T> inline void print(T obj) { cout << obj << '\n'; }
template<typename T, typename... Args> inline void print(T t, Args... args) { cout << t << " "; print(args...); }
template<typename T> inline void dbg(T obj) { cerr << obj << '\n'; }
template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; dbg(args...); }

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

struct Node {
    Node* next;
    int ind;

    Node(int i) {
        ind = i;
        next = nullptr;
    }
};

void run() {
    // int n; cin >> n ; VLL v(n); INP(v,n);
    int q; cin >> q;
    unordered_map<int, Node*> ar;
    unordered_map<int, Node*> arE;
    int last = 0;
    REP(i, q) {
        int type; cin >> type;
        if (type == 1) {
            int x; cin >> x;
            Node* nn = new Node(last);
            ++last;
            if (ar.count(x)) {
                arE[x]->next = nn;
                arE[x] = nn;
            } else {
                arE[x] = nn;
                ar[x] = nn;
            }
        } else if (type == 2) {
            int x, y;
            cin >> x >> y;
            if (x==y) continue;
            if (ar.count(x)) {
                if (!ar.count(y)) {
                    ar[y] = ar[x];
                    arE[y] = arE[x];
                    ar.erase(x);
                    arE.erase(x);
                } else {
                    Node* ptr = arE[y];
                    arE[y]->next = ar[x];
                    arE[y] = arE[x];
                    ar.erase(x);
                    arE.erase(x);
                }
            }
        }
    }
    vector<int> res(last, 555);
    for (auto pair : ar) {
        Node* cur = pair.second;
        while (cur != nullptr) {
            res[cur->ind] = pair.first;
            cur = cur->next;
        }
    }
    REP(i, last) {
        cout << res[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    cout.precision(10);
    ll t=1;
    REP(tests,t) run();
}