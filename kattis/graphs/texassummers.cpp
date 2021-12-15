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
    template<typename T, typename... Args> inline void dbg(T t, Args... args) { cerr << t << " "; print(args...); }

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

    vector<vector<pair<int, ld>>> adj;

    void dijkstra(int s, vector<ld> & d, vector<int> & p) {
        int n = adj.size();
        d.assign(n, 1000000);
        p.assign(n, -1);
        vector<bool> u(n, false);

        d[s] = 0;
        for (int i = 0; i < n; i++) {
            int v = -1;
            for (int j = 0; j < n; j++) {
                if (!u[j] && (v == -1 || d[j] < d[v]))
                    v = j;
            }

            if (d[v] == 1000000)
                break;

            u[v] = true;
            for (auto edge : adj[v]) {
                int to = edge.first;
                ld len = edge.second;

                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                }
            }
        }
    }


    struct pt {
        ll x;
        ll y;
    };

    void run() {
        int n;
        cin >> n;
        vector<pt> pts(n+1);
        for (int i = 1; i <= n; ++i) {
            cin >> pts[i].x >> pts[i].y;
        }
        cin >> pts[0].x >> pts[0].y;

        ll dex, dey;
        cin >> dex >> dey;

        if (n == 0) {
            print("-");
            return;
        }

        adj.resize(n+1);
        for (int i = 0; i < n+1; ++i) {
            for (int j = i+1; j < n+1; ++j) {
                ll dx = pts[i].x - pts[j].x;
                ll dy = pts[i].y - pts[j].y;
                ld dist = sqrt((ld)(dx*dx+dy*dy));
                dist = dist*dist/3;
                adj[i].push_back({j, dist});
                adj[j].push_back({i, dist});
            }
        }
        vector<ld> d;
        vector<int> p;
        dijkstra(0, d, p);

        int par = 0;
        ld best = 1000000;
        for (int i = 0; i <= n; ++i) {
            ll dx = dex - pts[i].x;
            ll dy = dey - pts[i].y;
            ld dist = sqrt((ld)(dx*dx+dy*dy));
            dist = dist*dist/3 + d[i];
            if (dist < best) {
                best = dist;
                par = i;
            }

        }
        int cur = par;
        if (cur == 0) {
            print("-");
        } else {
            vector<int> path;
            while (cur > 0) {
                path.push_back(cur - 1);
                cur = p[cur];
            }

            reverse(all(path));
            if (path.size() == 0) {
                print("-");
            } else {
                for (int i : path) {
                    print(i);
                }
            }
        }

    }

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cin.exceptions(cin.failbit);
        // cout.setf(ios::fixed);
        // cout.precision(10);
        // ll t; cin >> t;
        ll t=1;
        REP(tests,t) run();
    }