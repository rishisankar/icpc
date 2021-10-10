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

struct Command {
    char type; // e (=), c (if), a (assert)
    string assignId;
    bool isUnknown;
    bool isSum;
    string leftId;
    string rightId;
    ll value;

    vector<Command> inners;
};

Command assertionz();
string s;
int pos;
int n;

// always pos should be next char

Command assign() {
    char id = s.at(pos);
    string st = "";
    bool addn = false;
    Command c;
    c.assignId = id;
    c.type = 'e';
    for (pos = pos+2; s.at(pos) != ']'; ++pos) {
        if (s.at(pos == '?')) {
            c.isUnknown = true;
            c.isSum = false;
            return c;
        }
        if ((s.at(pos)) == '+') {
            c.leftId = st;
            addn = true;
            c.isSum = true;
            c.isUnknown = false;
            st = "";
        }
        st += s.at(pos);
    }

    if (!addn) {
        ll val = stoll(s);
        c.isUnknown = c.isSum = false;
        c.value = val;
    } else {
        c.rightId = st;
    }
    pos++;
    return c;
}

Command conditionalz() {
    Command c;
    c.type = 'c';
    c.leftId = s.at(pos);
    pos += 2;
    c.rightId = s.at(pos);
    pos += 2;
    while (true) {
        if (s.at(pos) == '}') {
            pos += 2;
            return c;
        } else if (s.at(pos) == '[') {
            ++pos;
            Command cx = assign();
            c.inners.push_back(cx);
        } else if (s.at(pos) == '<') {
            ++pos;
            Command cx = assertionz();
            c.inners.push_back(cx); 
        }
    }

    return c;
}

Command assertionz() {
    Command c;
    c.type = 'a';
    c.leftId = s.at(pos);
    pos += 2;
    c.rightId = s.at(pos);
    pos += 2;
    return c;
}

bool run() {
    cin >> s;
    pos = 0;
    n = s.size();
    vector<Command> commands;
    if (n == 0) {
        return true;
    }
    while (pos < n) {
        char x = s.at(pos);
        ++pos;
        if (x == '[') {
            Command c = assign();
            commands.PB(c);
        } else if (x == '(') {
            Command c = conditionalz();
            commands.PB(c);
        } else if (x == '<') {
            Command c  = assertionz();
            commands.PB(c);
        }
    }


    for (int i = 0; i < 1024; ++i) {
        ll ct = 0;
        cout << i << "\n";
        cout.flush();
        unordered_map<string, ll> vars;
        for (Command c : commands) {
            if (c.type == 'e') {
                if (c.isUnknown) {
                    vars[c.assignId] = ((i >> ct) & 1);
                    ++ct;
                } else if (c.isSum) {
                    ll lft = 0; ll rght = 0;
                    if (vars.count(c.leftId)) {
                        lft = vars[c.leftId];
                    }
                    if (vars.count(c.rightId)) {
                        rght = vars[c.rightId];
                    }
                    vars[c.assignId] = lft + rght;
                } else {
                    vars[c.assignId] = c.value;
                }
            } else if (c.type == 'a') {
                ll lft = 0; ll rght = 0;
                if (vars.count(c.leftId)) {
                    lft = vars[c.leftId];
                }
                if (vars.count(c.rightId)) {
                    rght = vars[c.rightId];
                }
                if (lft != rght) {
                    return false;
                }
            } else if (c.type == 'c') {
                ll lft = 0; ll rght = 0;
                if (vars.count(c.leftId)) {
                    lft = vars[c.leftId];
                }
                if (vars.count(c.rightId)) {
                    rght = vars[c.rightId];
                }
                if (lft >= rght) {
                    continue;
                }
                for (Command cx : c.inners) {

                    if (cx.type == 'e') {
                        if (cx.isUnknown) {
                            vars[cx.assignId] = ((i >> ct) & 1);
                            ++ct;
                        } else if (cx.isSum) {
                            ll lft = 0; ll rght = 0;
                            if (vars.count(cx.leftId)) {
                                lft = vars[cx.leftId];
                            }
                            if (vars.count(cx.rightId)) {
                                rght = vars[cx.rightId];
                            }
                            vars[cx.assignId] = lft + rght;
                        } else {
                            vars[cx.assignId] = cx.value;
                        }
                    } else if (cx.type == 'a') {
                        ll lft = 0; ll rght = 0;
                        if (vars.count(cx.leftId)) {
                            lft = vars[cx.leftId];
                        }
                        if (vars.count(cx.rightId)) {
                            rght = vars[cx.rightId];
                        }
                        if (lft != rght) {
                            return false;
                        }
                    }

                }
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);
    ll t; cin >> t;
    //ll t=1;
    REP(tests,t) {
        bool res = run();
        if (res) {
            print("ASSERTIONS ALWAYS HOLD");
        } else {
            print("ASSERTIONS INVALID");
        }
    }

}