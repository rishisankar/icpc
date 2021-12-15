#include <bits/stdc++.h>
using namespace std;

#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define FOR(i, j, k) for (int i=j ; i<k ; ++i)
#define rep(i, a, b) for(int i = a; i < (b); ++i)  // for compatibility with kactl
#define FORI(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k) for (int i=j ; i>=k ; --i)
#define RFORI(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j)
#define RREP(i, j) RFOR(i, j, 0)
#define OREP(i, j) FOR(i, 1, j+1)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

template<typename T> inline T maxe(vector<T> &vec) { return *max_element(all(vec)); }
template<typename T> inline T mine(vector<T> &vec) { return *min_element(all(vec)); }

template<typename T> inline void printV(vector<T> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
    cout << "########\n";
}
template<typename T> inline void printVV(vector<vector<T>> &vec) {
    cout << "########\n";
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            cout << vec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "########\n";
}

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef vector<int> vi; // for compatibility with kactl
typedef vector<vector<int>> VVI;
typedef vector<long long> VLL;
typedef vector<vector<long long>> VVLL;
typedef vector<bool> VB;
typedef vector<vector<bool>> VVB;
typedef vector<string> VS;
typedef vector<vector<string>> VVS;
typedef pair<int, int> PII;
typedef pair<int, int> pii; // for compatibility with kactl
typedef vector<pair<int, int>> VPII;
typedef vector<vector<pair<int, int>>> VVPII;

struct matcher {
    string s;
    int m;

    matcher() {}
    matcher(string s_, int m_) : s(s_), m(m_) {}

    bool operator==(const matcher& p) const { 
        int i1 = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i == m) continue;
            if (i1 == p.m) ++i1;
            if (i1 >= p.s.size()) return false;
            if (s[i] != p.s[i1]) return false;
            ++i1;
        }
        if (i1 < p.s.size() - 1 || (i1 == p.s.size()-1 && i1 != p.m) ) return false;
        return true;
    } 
};

matcher M;
ll MH;

const ll x = 12345;
const ll inv = 203'483'193;

class Hash { 
public: 
    size_t operator()(const matcher& match) const { 
        if (&match == &M) {
            return MH;
        }
        ll count = 0;
        ll xs = 1;
        REP(i, match.s.size()) {
            if (i == match.m) continue;
            
            count += xs * (ll) match.s[i];
            count %= MOD;
            xs = (xs * x) % MOD;
        }
        return count;
    } 
}; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    // cout.setf(ios::fixed);
    // cout.precision(10);

    int n; cin >> n;

    unordered_set<matcher, Hash> st;

    VS inp(n);

    REP(i, n) {
        cin >> inp[i];
        matcher m(inp[i], -1);
        st.insert(m);
    }

    int count = 0;
    for(string s : inp) {
        M.s = s;
        M.m = -1;
        Hash tmph;
        matcher tmpm(s, -1);
        ll P = tmph(tmpm);
        //cout << "P: " << s << " " << P << '\n';
        //cout << s << " " << P << '\n';
        ll Q = 0;
        ll xpow = 1;
        for (int i = 0; i < s.size(); ++i) {
            M.m = i;
            if (i > 0) {
                Q += (xpow * (ll) s[i-1]);
                Q %= MOD;
                xpow = (xpow*x)%MOD;
            }
            ll hashtmp = (P - Q + MOD)%MOD;
            ll coeff = (xpow*(ll)s[i]) % MOD;
            hashtmp = (hashtmp - coeff + MOD)%MOD;
            hashtmp = (hashtmp * inv) % MOD;
            MH = (Q + hashtmp)%MOD;
            //cout << s << " " << i << " " << MH << '\n';
            
            if (st.find(M) != st.end()) {
                cout << s << '\n';
                ++count;
                break;
            }
        }
    }

    if (count == 0) {
        cout << "NO TYPOS\n";
    }

}
